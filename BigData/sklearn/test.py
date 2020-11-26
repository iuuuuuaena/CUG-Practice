import csv
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
import numpy as np


def test():
    with open('data/new.csv','w',newline='') as ff:
        writer=csv.writer(ff,delimiter='\t')
        with open('data/data.csv', 'r') as f:
            reader = csv.reader(f, delimiter='\t')
            for row in reader:
                if len(row)!=0:
                    writer.writerow(row)



if __name__ == '__main__':
    # iris = datasets.load_iris()
    # iris_X = iris.data
    # iris_y = iris.target
    test()
