#!/usr/bin/env python
# coding=utf-8

def check_dangerous_code(solution_id, language):
    if language in ['python2', 'python3']:
        code = file('/work/%s/main.py' % solution_id).readlines()
        support_modules = [
            're',  # 正则表达式
            'sys',  # sys.stdin
            'string',  # 字符串处理
            'scanf',  # 格式化输入
            'math',  # 数学库
            'cmath',  # 复数数学库
            'decimal',  # 数学库，浮点数
            'numbers',  # 抽象基类
            'fractions',  # 有理数
            'random',  # 随机数
            'itertools',  # 迭代函数
            'functools',
            #Higher order functions and operations on callable objects
            'operator',  # 函数操作
            'readline',  # 读文件
            'json',  # 解析json
            'array',  # 数组
            'sets',  # 集合
            'queue',  # 队列
            'types',  # 判断类型
        ]
        for line in code:
            if line.find('import') >= 0:
                words = line.split()
                tag = 0
                for w in words:
                    if w in support_modules:
                        tag = 1
                        break
                if tag == 0:
                    return False
        return True
    if language in ['gcc', 'g++']:
        try:
            code = file('/work/%s/main.c' % solution_id).read()
        except:
            code = file('/work/%s/main.cpp' % solution_id).read()
        if code.find('system') >= 0:
            return False
        return True
#    if language == 'java':
#        code = file('/work/%s/Main.java'%solution_id).read()
#        if code.find('Runtime.')>=0:
#            return False
#        return True
    if language == 'go':
        code = file('/work/%s/main.go' % solution_id).read()
        danger_package = [
            'os', 'path', 'net', 'sql', 'syslog', 'http', 'mail', 'rpc', 'smtp', 'exec', 'user',
        ]
        for item in danger_package:
            if code.find('"%s"' % item) >= 0:
                return False
        return True

