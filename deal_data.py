#!/usr/bin/env python
# coding=utf-8

def clean_work_dir(solution_id):
    '''清理word目录，删除临时文件'''
    dir_name = os.path.join(config.work_dir, str(solution_id))
    shutil.rmtree(dir_name)



def get_data_count(problem_id):
    '''获得测试数据的个数信息'''
    full_path = os.path.join(config.data_dir, str(problem_id))
    try:
        files = os.listdir(full_path)
    except OSError as e:
        logging.error(e)
        return 0
    count = 0
    for item in files:
        if item.endswith(".in") and item.startswith("data"):
            count += 1
    return count
