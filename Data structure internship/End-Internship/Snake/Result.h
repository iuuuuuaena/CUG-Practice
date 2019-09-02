#pragma once
#include"cocos2d.h"
#include"HelloWorldScene.h"
class GameScene;
class MyResult : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	static int ResScore;
	// implement the "static create()" method manually
	CREATE_FUNC(MyResult);
};