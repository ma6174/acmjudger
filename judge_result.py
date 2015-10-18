#!/usr/bin/env python
# coding=utf-8

def judge_result(problem_id, solution_id, data_num):
    low_level()
    '''对输出数据进行评测'''
    logging.debug("Judging result")
    correct_result = os.path.join(
        config.data_dir, str(problem_id), 'data%s.out' %
        data_num)
    user_result = os.path.join(
        config.work_dir, str(solution_id), 'out%s.txt' %
        data_num)
    try:
        correct = file(
            correct_result).read(
            ).replace(
                '\r',
                '').rstrip(
                )  # 删除\r,删除行末的空格和换行
        user = file(user_result).read().replace('\r', '').rstrip()
    except:
        return False
    if correct == user:  # 完全相同:AC
        return "Accepted"
    if correct.split() == user.split():  # 除去空格,tab,换行相同:PE
        return "Presentation Error"
    if correct in user:  # 输出多了
        return "Output limit"
    return "Wrong Answer"  # 其他WA


