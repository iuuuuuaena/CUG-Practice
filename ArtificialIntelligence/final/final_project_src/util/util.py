import os
from chinese_calendar import is_workday
from dateutil.parser import parse


def trans_time(time_str: str, normalized=False):
    times = time_str.split(":")
    timestamp = int(times[0]) * 60 * 60 + int(times[1]) * 60 + int(times[2])
    if normalized: return timestamp / (24 * 60 * 60)
    return timestamp



def lode_data(root_dir):
    data = []
    for i in range(182):
        chi_dir = root_dir + "/%03d/" % i + "Trajectory"
        g = os.walk(chi_dir)
        one = []
        for path, dir_list, file_list in g:
            for file_name in file_list:
                with open(path + '/' + file_name, 'r') as f:
                    lines = f.readlines()[6:]
                    for line in lines:
                        line = line.strip('\n')
                        one_data = line.split(',')
                        one.append(one_data)
                    # one+=f.readlines()[5:]
        data.append(one)
    return data


def lode_data_with_index(root_dir, index=0):
    chi_dir = root_dir + "/%03d/" % index + "Trajectory"
    g = os.walk(chi_dir)
    one = []
    for path, dir_list, file_list in g:
        for file_name in file_list:
            with open(path + '/' + file_name, 'r') as f:
                lines = f.readlines()[6:]
                for line in lines:
                    line = line.strip('\n')
                    one_data = line.split(',')
                    one.append([[is_workday(parse(one_data[5])),int(one_data[6].split(':')[0])],[float(one_data[0]),float(one_data[1])]])
    return one

