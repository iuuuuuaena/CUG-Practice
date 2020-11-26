import csv


def read_file(file_name):
    with open(file_name, 'r') as f:
        reader = csv.reader(f, delimiter='\t')
        rows = [row for row in reader]
    return rows
