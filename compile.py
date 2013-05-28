#!/usr/bin/env python
# coding=utf-8

def compile(solution_id, language):
    low_level()
    '''将程序编译成可执行文件'''
    language = language.lower()
    dir_work = os.path.join(config.work_dir, str(solution_id))
    build_cmd = {
        "gcc":
        "gcc main.c -o main -Wall -lm -O2 -std=c99 --static -DONLINE_JUDGE",
        "g++": "g++ main.cpp -O2 -Wall -lm --static -DONLINE_JUDGE -o main",
        "java": "javac Main.java",
        "ruby": "reek main.rb",
        "perl": "perl -c main.pl",
        "pascal": 'fpc main.pas -O2 -Co -Ct -Ci',
        "go": '/opt/golang/bin/go build -ldflags "-s -w"  main.go',
        "lua": 'luac -o main main.lua',
        "python2": 'python2 -m py_compile main.py',
        "python3": 'python3 -m py_compile main.py',
        "haskell": "ghc -o main main.hs",
    }
    if language not in build_cmd.keys():
        return False
    p = subprocess.Popen(
        build_cmd[language],
        shell=True,
        cwd=dir_work,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE)
    out, err = p.communicate()  # 获取编译错误信息
    err_txt_path = os.path.join(config.work_dir, str(solution_id), 'error.txt')
    f = file(err_txt_path, 'w')
    f.write(err)
    f.write(out)
    f.close()
    if p.returncode == 0:  # 返回值为0,编译成功
        return True
    dblock.acquire()
    update_compile_info(solution_id, err + out)  # 编译失败,更新题目的编译错误信息
    dblock.release()
    return False
