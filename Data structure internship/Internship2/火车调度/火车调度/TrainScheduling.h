#pragma once
#include "LinkedQueue.h"
class TrainScheduling
{
public:
	TrainScheduling(int train[], int len, int rail);
	~TrainScheduling();
	bool Scheduling();

private:
	LinkedQueue<int> *p_rail;//铁轨序列
	int *p_train;//火车列
	int len;//火车个数
	int rail;//铁轨个数
};

TrainScheduling::TrainScheduling(int train[],int len, int rail)
{
	this->len = len;
	this->rail = rail;
	p_rail = new LinkedQueue<int>[this->rail];
	p_train = new int[this->len];
	for (int i = 0; i < this->len; i++)
	{
		this->p_train[i] = train[i];
	}
}

TrainScheduling::~TrainScheduling()
{
	delete[] p_rail;
	delete[] p_train;
}

bool TrainScheduling::Scheduling()
{
	int out = 1;//当前应该出列的车
	int i = len - 1;//进入的车
	int NonEmptyRail=0;//记录非空铁轨数量
	while (out<=len)
	{
		//cout << "Non" << NonEmptyRail << endl;
		//cout << i << p_train[i] << out << NonEmptyRail << rail << endl;
		if (i >= 0 && p_train[i] == out&&NonEmptyRail<rail) {
			cout << out << "从" <<  rail << "轨道出来"<<endl;
			i--; out++;
			continue;
		}
		else{
			int temp = 0;//记录是否在铁轨里找到所需火车
			for (int j = 0; j < rail; j++) {
				if (!p_rail[j].isEmpty()) {
					if (p_rail[j].getFront() == out) {
						cout << out << "从" << j+1 << "轨道出来" <<endl;
						p_rail[j].Dequeue();
						if (p_rail[j].isEmpty()) { NonEmptyRail--; }
						out++;
						temp++;
					}
				}
				if (temp > 0)break;
			}
			if (temp > 0)continue;
			else
			{
				int max = 0;
				int t_rail = -1;
				for (int j = 0; j < rail; j++) {
					if (!p_rail[j].isEmpty()) {
						//cout << p_rail[j].getRear() << p_train[i] << p_rail[j].getRear() << max << endl;
						if (p_rail[j].getRear() < p_train[i]&&p_rail[j].getRear() > max) {
							//cout << "进入非空队列" << endl;
							t_rail = j;
							max = p_rail[j].getRear();
						}
					}
				}
				if (max != 0) {
					p_rail[t_rail].EnQueue(p_train[i]);
					cout << p_train[i] << "进入" << t_rail+1 << "轨道" << endl;
					i--;
					continue;
				}
				else if(NonEmptyRail<rail)
				{
					for (int j = 0; j < rail; j++) {
						if (p_rail[j].isEmpty()) {
							p_rail[j].EnQueue(p_train[i]);
							cout << p_train[i] << "进入" << j+1 << "轨道" << endl;
							i--;
							NonEmptyRail++;
							break;
						}
					}
				}
				else
				{
					cout << "失败" << endl;
					return false;
				}
			}
		}
	}
	cout << "成功" << endl;
	return true;
}
