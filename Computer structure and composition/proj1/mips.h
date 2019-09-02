// mips.h
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

#define FALSE 0
#define TRUE 1
#define MAXNUMINSTRS 1024       /* max # instrs in a program 最大指令内存字数量*/
#define MAXNUMDATA 3072         /* max # data words 最大数据内存字数量*/

// 仿真计算机结构体
// 内存，寄存器，pc，调试交互设置
// 注意：本模拟计算机内存只包含两块区域，指令和数据
struct Computer {
	int memory [MAXNUMINSTRS+MAXNUMDATA];
	int registers [32];
	int pc;
	int printingRegisters, printingMemory, interactive, debugging;
};

//class MipsSimulator
//{
//public:
//	MipsSimulator(int printingRegisters=0, int printingMemory=0, int debugging=0, int interactive=1);
//private:
//	Computer mipsComputer;
//};

Computer* newComputer(FILE*, int printingRegisters, int printingMemory, int debugging, int interactive);
void simulate(Computer* p);
void printInfo(Computer* p, int changedReg, int changedMem);
void simulateInstruction(Computer* p, unsigned int instr, int *changedReg, int *changedMem);
char * disassembled(unsigned int, unsigned int);
unsigned int contents(Computer* p, int);

int ImmediatelyConvertToDecimal(int immediate)
{
	int x, y;
	y = (immediate << 16) >> 16;
	x = y >> 15;
	if (x == 1)
		y = -((y - 1) ^ 0xffff);
	return y;
};

string tentohex(int im) {
	char s[50];
	sprintf_s(s, "%x", im);
	return string(s);
};
