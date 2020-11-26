import numpy as np
from util.util import lode_data_with_index
import matplotlib.pyplot as plt


def show():
    data = lode_data_with_index('../Data')
    data = np.array(data)
    print(data.shape)
    plt.scatter(data[:100,0],data[:100,1],)
    plt.show()
    # print(data[:,0])


if __name__ == '__main__':
    show()
