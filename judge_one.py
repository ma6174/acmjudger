#!/usr/bin/env python
# coding=utf-8

def judge_one_mem_time(
        solution_id, problem_id, data_num, time_limit, mem_limit, language):
    low_level()
    '''评测一组数据'''
    input_path = os.path.join(
        config.data_dir, str(problem_id), 'data%s.in' %
        data_num)
    try:
        input_data = file(input_path)
    except:
        return False
    output_path = os.path.join(
        config.work_dir, str(solution_id), 'out%s.txt' %
        data_num)
    temp_out_data = file(output_path, 'w')
    if language == 'java':
        cmd = 'java -cp %s Main' % (
            os.path.join(config.work_dir,
                         str(solution_id)))
        main_exe = shlex.split(cmd)
    elif language == 'python2':
        cmd = 'python2 %s' % (
            os.path.join(config.work_dir,
                         str(solution_id),
                         'main.pyc'))
        main_exe = shlex.split(cmd)
    elif language == 'python3':
        cmd = 'python3 %s' % (
            os.path.join(config.work_dir,
                         str(solution_id),
                         '__pycache__/main.cpython-33.pyc'))
        main_exe = shlex.split(cmd)
    elif language == 'lua':
        cmd = "lua %s" % (
            os.path.join(config.work_dir,
                         str(solution_id),
                         "main"))
        main_exe = shlex.split(cmd)
    elif language == "ruby":
        cmd = "ruby %s" % (
            os.path.join(config.work_dir,
                         str(solution_id),
                         "main.rb"))
        main_exe = shlex.split(cmd)
    elif language == "perl":
        cmd = "perl %s" % (
            os.path.join(config.work_dir,
                         str(solution_id),
                         "main.pl"))
        main_exe = shlex.split(cmd)
    else:
        main_exe = [os.path.join(config.work_dir, str(solution_id), 'main'), ]
    runcfg = {
        'args': main_exe,
        'fd_in': input_data.fileno(),
        'fd_out': temp_out_data.fileno(),
        'timelimit': time_limit,  # in MS
        'memorylimit': mem_limit,  # in KB
    }
    low_level()
    rst = lorun.run(runcfg)
    input_data.close()
    temp_out_data.close()
    logging.debug(rst)
    return rst

