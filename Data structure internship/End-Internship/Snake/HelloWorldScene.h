#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
class GameScene;
class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	GameScene* secondLayer;
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};



#endif // __HELLOWORLD_SCENE_H__
