#!/usr/bin/env python
# coding=utf-8

def put_task_into_queue():
    '''循环扫描数据库,将任务添加到队列'''
    while True:
        q.join()  # 阻塞程序,直到队列里面的任务全部完成
        sql = "#####"
        data = run_sql(sql)
        time.sleep(0.2)  # 延时0.2秒,防止因速度太快不能获取代码
        for i in data:
            solution_id, problem_id, user_id, contest_id, pro_lang = i
            dblock.acquire()
            ret = get_code(solution_id, problem_id, pro_lang)
            dblock.release()
            if ret == False:
                # 防止因速度太快不能获取代码
                time.sleep(0.5)
                dblock.acquire()
                ret = get_code(solution_id, problem_id, pro_lang)
                dblock.release()
            if ret == False:
                dblock.acquire()
                update_solution_status(solution_id, 11)
                dblock.release()
                clean_work_dir(solution_id)
                continue
            task = {
                "solution_id": solution_id,
                "problem_id": problem_id,
                "contest_id": contest_id,
                "user_id": user_id,
                "pro_lang": pro_lang,
            }
            q.put(task)
            dblock.acquire()
            update_solution_status(solution_id)
            dblock.release()
        time.sleep(0.5)
