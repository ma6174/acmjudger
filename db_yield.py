#!/usr/bin/env python
#coding=utf-8

import time
import config
import MySQLdb
import logging
import types
import threading


class threadsafe_iter:
    """Takes an iterator/generator and makes it thread-safe by
    serializing call to the `next` method of given iterator/generator.
    """
    def __init__(self, it):
        self.it = it
        self.lock = threading.Lock()

    def __iter__(self):
        return self

    def next(self):
        with self.lock:
            return self.it.next()
    def send(self,data):
        with self.lock:
            return self.it.send(data)
    def close(self):
        with self.lock:
            return self.it.close()
    def throw(self,data):
        with self.lock:
            return self.it.throw(data)


def threadsafe_generator(f):
    """A decorator that takes a generator function and makes it thread-safe.
    """
    def g(*a, **kw):
        return threadsafe_iter(f(*a, **kw))
    return g

def connect_to_db():
    '''连接数据库,连接失败自动重新连接,防止因数据库重启或中断导致评测程序中断'''
    con = None
    while True:
        try:
            con = MySQLdb.connect(config.db_host,config.db_user,config.db_password,
                                  config.db_name,charset=config.db_charset)
            return con
        except: 
            logging.error('Cannot connect to database,trying again')
            time.sleep(1)

@threadsafe_generator
def run_sql_yield():
    '''执行sql语句,并返回结果'''
    con = connect_to_db()
    cur = con.cursor()
    data = None
    while True:
        sql = (yield data)
        try:
            if type(sql) == types.StringType:
                cur.execute(sql)
            elif type(sql) == types.ListType:
                for i in sql:
                    cur.execute(i)
        except MySQLdb.OperationalError,e:
            logging.error(e)
            cur.close()
            con.close()
            con = connect_to_db()
            cur = con.cursor()
            data = False
            logging.error("yield db error!!!!!!!!!!!!")
            continue
        con.commit()
        data = cur.fetchall()
    cur.close()
    con.close()
