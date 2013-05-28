#!/usr/bin/env python
# coding=utf-8

def worker():
    '''工作线程，循环扫描队列，获得评判任务并执行'''
    while True:
        if q.empty() is True:  # 队列为空，空闲
            logging.info("%s idle" % (threading.current_thread().name))
        task = q.get()  # 获取任务，如果队列为空则阻塞
        solution_id = task['solution_id']
        problem_id = task['problem_id']
        language = task['pro_lang']
        user_id = task['user_id']
        data_count = get_data_count(task['problem_id'])  # 获取测试数据的个数
        logging.info("judging %s" % solution_id)
        result = run(
            problem_id,
            solution_id,
            language,
            data_count,
            user_id)  # 评判
        logging.info(
            "%s result %s" % (
                result[
            'solution_id'],
                result[
                    'result']))
        dblock.acquire()
        update_result(result)  # 将结果写入数据库
        dblock.release()
        if config.auto_clean:  # 清理work目录
            clean_work_dir(result['solution_id'])
        q.task_done()  # 一个任务完成
