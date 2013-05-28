#!/usr/bin/env python
# coding=utf-8
"""
为了服务器安全，隐藏部分sql语句。
程序执行需要相关数据库和测试数据。
"""
import os
import sys
import shutil
import subprocess
import codecs
import logging
import shlex
import time
import config
import lorun
import threading
import MySQLdb
from db import run_sql
from Queue import Queue


def low_level():
    try:
        os.setuid(int(os.popen("id -u %s" % "nobody").read()))
    except:
        pass
try:
    # 降低程序运行权限，防止恶意代码
    os.setuid(int(os.popen("id -u %s" % "nobody").read()))
except:
    logging.error("please run this program as root!")
    sys.exit(-1)
# 初始化队列
q = Queue(config.queue_size)
# 创建数据库锁，保证一个时间只能一个程序都写数据库
dblock = threading.Lock()


def start_work_thread():
    '''开启工作线程'''
    for i in range(config.count_thread):
        t = threading.Thread(target=worker)
        t.deamon = True
        t.start()


def start_get_task():
    '''开启获取任务线程'''
    t = threading.Thread(target=put_task_into_queue, name="get_task")
    t.deamon = True
    t.start()


def check_thread():
    low_level()
    '''检测评测程序是否存在,小于config规定数目则启动新的'''
    while True:
        try:
            if threading.active_count() < config.count_thread + 2:
                logging.info("start new thread")
                t = threading.Thread(target=worker)
                t.deamon = True
                t.start()
            time.sleep(1)
        except:
            pass


def start_protect():
    '''开启守护进程'''
    low_level()
    t = threading.Thread(target=check_thread, name="check_thread")
    t.deamon = True
    t.start()


def main():
    low_level()
    logging.basicConfig(level=logging.INFO,
                        format='%(asctime)s --- %(message)s',)
    start_get_task()
    start_work_thread()
    start_protect()

if __name__ == '__main__':
    main()
