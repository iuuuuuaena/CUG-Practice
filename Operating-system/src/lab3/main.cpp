// practice3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"MemoryManage.h"
using namespace std;

int main()
{
	MemoryManage *memoryManage = new MemoryManage;
	memoryManage->print();
	memoryManage->scanf();
}

/*
0
a 12
0
0
b 26
0
0
c 68
0
1
b
0
d 143
0
*/
/*
0
a 10
0
0
b 1
0
0
c 4
0
0
d 1
0
0
e 20
0
0
f 1
0
0
g 18
0
0
h 1
0
0
i 7
0
0
j 1
0
0
k 9
0
0
l 1
0
0
m 12
0
0
n 1
0
0
o 15
0
0
p 1
0
1
a
1
c
1
e
1
g
1
i
1
k
1
m
1
o
*/