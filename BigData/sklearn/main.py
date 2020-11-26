from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
import numpy as np
import csv
import matplotlib.pyplot as plt


def read_file(file_name):
    with open(file_name, 'r') as f:
        reader = csv.reader(f, delimiter='\t')
        rows = [row for row in reader]
    return rows


def get_x_y(data):
    for i in range(len(data)):
        data[i] = list(map(int, data[i]))
    data = np.array(data)
    data_x = data[:, :2]
    data_y = data[:, 2]
    return data_x, data_y


def do():
    data = read_file('./data/new.csv')
    data_x, data_y = get_x_y(data)
    x_train, x_test, y_train, y_test = train_test_split(data_x, data_y, test_size=0.3)
    knn = KNeighborsClassifier()
    knn.fit(x_train, y_train)
    print(knn.score(x_test, y_test))
    y_predict = knn.predict(x_test)
    plt.plot(y_test[100:200], label='true data')
    plt.plot(y_predict[100:200], 'r:', label='predict')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    do()
