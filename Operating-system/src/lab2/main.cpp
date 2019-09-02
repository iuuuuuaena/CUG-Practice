// practice2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"Bank.h"

int main()
{
	Bank *bank=new Bank();
	while (true)
	{
		cout << "输入q退出,其他开始请求资源" << endl;
		char c;
		cin >> c;
		if (c=='q')
		{
			break;
		}
		bank->reduction();
		bank->request();
	}
	delete bank;
    std::cout << "Hello World!\n"; 
}
/*test
5
3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
3 3 2

1 1 0 2
4 3 3 0
0 0 2 0
3 3 1 1
*/
