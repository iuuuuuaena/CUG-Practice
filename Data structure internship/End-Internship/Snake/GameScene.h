#pragma once
#include"cocos2d.h"
#include"HelloWorldScene.h"
#include"time.h"
#include"stdlib.h"
#include"AStar.h"
#include<fstream>
#include"SimpleAudioEngine.h"
#include"Result.h"

USING_NS_CC;
class MyResult;

enum DIR {
	up=28,down=29,right=27,left=26
};

class SnakeNode :public cocos2d::Sprite{
public:
	static SnakeNode* create(const std::string &fileName) {
		SnakeNode * sprite = new SnakeNode();
		if (sprite&& sprite->initWithFile(fileName))
		{
			sprite->autorelease(); return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	SnakeNode* pre;
	SnakeNode(SnakeNode *ptr = NULL) {
		this->pre = ptr;
	}
};

class GameScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	virtual void myupdate(float dt);
	virtual void automatic(float dt);
	// implement the "static create()" method manually
	void CreatFood();
	//键盘监听
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*event);
	CREATE_FUNC(GameScene);
	void move();
	void EatFood();
	bool ReadWord();
	void searchPath();
	void ResetMap();
	bool EatSelf();//检测吃到自己
	bool IsOut();//检测是否出边框

	static int sceneNum;
protected:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float contentScaleFactor;
	DIR dir;//蛇头的方向
	

	SnakeNode *head;
	cocos2d::Sprite *food;//食物
	cocos2d::Label *des;//单词释义
	cocos2d::Label *ShowWord;//显示的单词
	cocos2d::Label *Score;//分数
	cocos2d::Label *Live;//生命
	cocos2d::Label *SpeedLB;//速度显示
	
	std::stack<Point*> Path;
	std::vector<SnakeNode*> SnakeBody;
	std::list<cocos2d::Sprite*> SnakeFood;//食物

	std::ifstream fin;//文件流
	std::string word;//当前单词
	std::string description;//单词释义
	std::string showstr;//显示的单词
	std::string score_str;
	std::string live_str;

	int n;//蛇的长度
	int current;//当前单词的第几个字母
	int **map;//当前游戏的状态 0表示路，1表示起点，2表示障碍，3表示终点
	int live;//生命数
	int score;//分数
	float speed;//速度
	float autoSpeed;//自动寻路速度
	bool isPlay;//音乐是否在播放
	int SpeedLevel;//0慢，1中，2快

	MyResult *p_Res;//修改游戏结束分数
};

