import os
import csv
import random


def do():
    root_dir = './data/2019'
    files = os.listdir(root_dir)
    count = 0

    with open('data/data.csv', 'w', newline='') as f:
        writer = csv.writer(f, delimiter='\t')
        for file in files:
            if not os.path.isdir(file):
                print("处理:" + file + "\tcount:" + str(count))
                with open(root_dir + '/' + file, 'r') as f:
                    reader = csv.reader(f, delimiter='\t')
                    for row in reader:
                        if random.random() < 0.00005:
                            year_month = row[2]
                            year = year_month[:4]
                            month = year_month[4:]
                            quad = row[29]
                            writer.writerow([year, month, quad])
                            count += 1


if __name__ == '__main__':
    do()
