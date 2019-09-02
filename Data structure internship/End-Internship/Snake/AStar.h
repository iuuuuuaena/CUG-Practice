#pragma once
#include<list>
#include<cmath>
#include"cocos2d.h"
#include"Result.h"
USING_NS_CC;


struct AStarNode
{
	int f;//距离估计值
	int g;//该点到起点的距离
	int h;//该点到终点的估算值
	AStarNode *parent;//前驱点
	int x;
	int y;
	int xend, yend;
	//bool isVisit;
	AStarNode(int _x, int _y, int _xend, int _yend, AStarNode *ptr = NULL) :x(_x), y(_y),xend(_xend),yend(_yend), parent(ptr) {
		if (ptr != NULL) { g = parent->g + 1; }
		else{
			g = 0;
		}
		h = abs(x - xend) + abs(y - yend);
		f = g + h;
		//isVisit = false;
	}
};

class AStar
{
public:
	AStar(int **newmap, int x1, int y1, int x2, int y2);
	bool FindPath();
	~AStar();
	std::stack<Point*> getPath();

private:
	int map[28][38];
	std::list<AStarNode*> OpenList;
	//std::list<AStarNode*> ClosedList;
	bool isEnd;
	AStarNode *minNode();
	AStarNode *isContain(int x, int y);
	std::stack<Point*> Path;
};