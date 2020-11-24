#include "AStar.h"
//当前游戏的状态 0表示路，1表示起点，2表示障碍，3表示终点
AStar::AStar(int **newmap,int x1,int y1,int x2,int y2) {
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 38; j++) {
			map[i][j] = newmap[i][j];
		}
	}
	//for (int i = 0; i < 28; i++) {
	//	for (int j = 0; j < 38; j++) {
	//		log("%d",map[i][j]);
	//	}
	//}
	AStarNode *m_pNode = new AStarNode(x1, y1, x2, y2);
	OpenList.push_back(m_pNode);
	isEnd = false;
}

bool AStar::FindPath() {
	AStarNode *current, *temp; int i = 0;
	while (isEnd!=true&&!OpenList.empty())
	{
		//log("%d %d",i++,OpenList.size());
		current = this->minNode();
		OpenList.pop_front();
		map[current->y][current->x] = 4;//访问过
		//current->isVisit = true;
		//ClosedList.push_back(current);
		if (current->x > 0) {//左边
			if (map[current->y][current->x - 1] ==0|| map[current->y][current->x - 1] == 3) {
				temp = isContain(current->x - 1, current->y);
				if (temp) {
					if (current->g + 1 < temp->g) {
						temp->g = current->g + 1; temp->f = temp->g + temp->h; temp->parent = current;
					}
				}
				else
				{
					AStarNode *newNode = new AStarNode(current->x - 1, current->y, current->xend, current->yend, current);
					if (newNode->h == 0)this->isEnd = true;
					OpenList.push_back(newNode);
				}
			}
		}
		if (current->x < 37) {//右边
			if (map[current->y][current->x + 1] == 0 || map[current->y][current->x + 1] == 3) {
				temp = isContain(current->x + 1, current->y);
				if (temp) {
					if (current->g + 1 < temp->g) {
						temp->g = current->g + 1; temp->f = temp->g + temp->h; temp->parent = current;
					}
				}
				else
				{
					AStarNode *newNode = new AStarNode(current->x + 1, current->y, current->xend, current->yend, current);
					if (newNode->h == 0)this->isEnd = true;
					OpenList.push_back(newNode);
				}
			}
		}
		if (current->y < 27) {//上边
			if (map[current->y+1][current->x] == 0 || map[current->y + 1][current->x] == 3) {
				temp = isContain(current->x , current->y+1);
				if (temp) {
					if (current->g + 1 < temp->g) {
						temp->g = current->g + 1; temp->f = temp->g + temp->h; temp->parent = current;
					}
				}
				else
				{
					AStarNode *newNode = new AStarNode(current->x, current->y + 1, current->xend, current->yend, current);
					if (newNode->h == 0)this->isEnd = true;
					OpenList.push_back(newNode);
				}
			}
		}
		if (current->y > 0) {//下边
			if (map[current->y - 1][current->x] == 0 || map[current->y - 1][current->x] == 3) {
				temp = isContain(current->x, current->y - 1);
				if (temp) {
					if (current->g + 1 < temp->g) {
						temp->g = current->g + 1; temp->f = temp->g + temp->h; temp->parent = current;
					}
				}
				else
				{
					AStarNode *newNode = new AStarNode(current->x, current->y - 1, current->xend, current->yend, current);
					if (newNode->h == 0)this->isEnd = true;
					OpenList.push_back(newNode);
				}
			}
		}
	}
	return true;
}
AStarNode* AStar::minNode() {
	AStarNode *current = OpenList.front();
	for (auto node:OpenList)
	{
		if (current->f > node->f) {
			current = node;
		}
	}
	return current;
}
AStarNode* AStar::isContain(int x, int y) {
	for (auto node : OpenList) {
		if (node->x == x && node->y == y) {
			return node;
		}
	}
	return NULL;
}

std::stack<Point*> AStar::getPath() {
	if(!OpenList.empty()){
		AStarNode *current = OpenList.back();
		Point *newPoint;
		while (current != NULL)
		{
			newPoint = new Point(current->x, current->y);
			this->Path.push(newPoint);
			current = current->parent;
		}
		return Path;
	}
	Director::getInstance()->replaceScene(MyResult::createScene());
}
AStar::~AStar()
{
	for (auto node : OpenList) {
		delete node;
	}
	while (!Path.empty())
	{
		Path.pop();
	}
}
