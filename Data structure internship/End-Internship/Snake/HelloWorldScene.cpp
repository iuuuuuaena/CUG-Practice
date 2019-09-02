#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"GameScene.h"
#include"AppDelegate.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto labelStart = Label::create("Start Game", "fonts/Marker Felt.ttf", 72);
	auto labelAI = Label::create("Automatic Path Finding", "fonts/Marker Felt.ttf", 72);
	auto labelExit = Label::create("ExitGame", "fonts/Marker Felt.ttf", 72);

	auto startItem = MenuItemLabel::create(labelStart, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	startItem->setTag(1);
	startItem->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 4 * 3 - 10));
	auto AIItem = MenuItemLabel::create(labelAI, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	AIItem->setTag(2);
	AIItem->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 4 * 2));
	auto exitItem = MenuItemLabel::create(labelExit, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	exitItem->setTag(3);
	exitItem->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 4 * 1 + 10));
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setTag(4);
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	//   // create menu, it's an autorelease object
	auto menu = Menu::create(startItem, AIItem, exitItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//   /////////////////////////////
	//   // 3. add your codes below...

	//   // add a label shows "Hello World"
	//   // create and initialize a label

	auto label = Label::createWithTTF("Snake", "fonts/Marker Felt.ttf", 96);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
	//auto sprite1 = Sprite::create("yqh.png");
	//sprite1->setPosition(Vec2(0, 0));
	//sprite1->setAnchorPoint(Vec2(0, 0));
	//this->addChild(sprite1);
	//this->removeAllChildrenWithCleanup(true);
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	switch (((Node*)pSender)->getTag())
	{
	case 1:
		//log("go to game");
		secondLayer->sceneNum = 0;
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;
		/*case  2:
			CCLOG("go to help");
			Director::getInstance()->replaceScene(GameAI::createScene());*/
		break;
	case 2:
		secondLayer->sceneNum = 1;
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case 3:
		Director::getInstance()->end();
	case 4:
		Director::getInstance()->end();
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
/*********************************************************************************************************/

