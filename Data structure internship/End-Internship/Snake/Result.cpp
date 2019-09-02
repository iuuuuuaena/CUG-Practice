#include "Result.h"

USING_NS_CC;
int MyResult::ResScore = 0;
Scene* MyResult::createScene()
{
	return MyResult::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MyResultScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MyResult::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Í¼Æ¬
	auto GameOver = Sprite::create("material/img/gameover.png");
	//GameOver->setPosition(Vec2(720, 450));
	GameOver->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 3 - 20));
	this->addChild(GameOver);
	//µÃ·Ö
	std::string str = "Your Score:";
	str += std::to_string(this->ResScore);
	auto ScoreShow = Label::create(str, "fonts/Marker Felt.ttf", 72);
	ScoreShow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 2));
	this->addChild(ScoreShow);
	//²Ëµ¥
	auto back = Label::create("MENU", "fonts/Marker Felt.ttf", 48);
	auto backMN = MenuItemLabel::create(back, CC_CALLBACK_1(MyResult::menuCloseCallback, this));
	backMN->setPosition(Vec2(visibleSize.width / 3 + 100, visibleSize.height / 4  + 20));
	backMN->setTag(1);
	auto exit = Label::create("EXIT", "fonts/Marker Felt.ttf", 48);
	auto exitMN = MenuItemLabel::create(exit, CC_CALLBACK_1(MyResult::menuCloseCallback, this));
	exitMN->setPosition(Vec2(visibleSize.width / 3 * 2 - 100, visibleSize.height / 4  + 20));
	exitMN->setTag(2);
	auto menu = Menu::create(backMN, exitMN, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}


void MyResult::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	switch (((Node *)pSender)->getTag())
	{
	case 1:
		Director::getInstance()->replaceScene(HelloWorld::createScene()); break;
	case 2:
		Director::getInstance()->end(); break;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

