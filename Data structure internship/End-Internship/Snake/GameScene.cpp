#include "GameScene.h"
#include"SimpleAudioEngine.h"

USING_NS_CC;

int GameScene::sceneNum = 0;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	this->contentScaleFactor = Director::getInstance()->getContentScaleFactor();
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	//背景音乐预加载与播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("material/img/music.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("material/img/music.wav", true);
	this->isPlay = true;
	//读取文件
	fin.open("material/img/四级词汇.txt");
	//fin >> word >> description;
	this->ReadWord();
	//log("%s\n%s", word.c_str(), description.c_str());
	//log("%d", strlen(word.c_str()));
	//log("visibleSize%f  %f", visibleSize.width, visibleSize.height);
	//log("origin%f  %f", origin.x, origin.y);
	//log("contentScaleFactor%f", contentScaleFactor);
	//菜单初始化
	auto back = Label::create("MENU", "fonts/Marker Felt.ttf", 36);
	auto backMN = MenuItemLabel::create(back, CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	backMN->setPosition(Vec2(135, 50));//主菜单
	backMN->setTag(1);
	auto turnOn = MenuItemImage::create("material/img/turnOn.png", "material/img/turnOn.png");
	auto turnOff = MenuItemImage::create("material/img/turnOff.png", "material/img/turnOff.png");
	auto MusicBtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScene::menuCloseCallback,this), turnOn, turnOff, NULL);
	MusicBtn->setTag(2);
	MusicBtn->setPosition(Vec2(135, 100));
	//auto backMN = MenuItemFont::create("Menu", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	SpeedLB = Label::create("Speed:Medium", "fonts/Marker Felt.ttf", 36);
	auto SpeedMN = MenuItemLabel::create(SpeedLB, CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	SpeedMN->setPosition(Vec2(135, 200));
	SpeedMN->setTag(3);
	auto menu = Menu::create(backMN,MusicBtn,SpeedMN, NULL);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);
	this->n = 1;
	this->dir = right;
	this->speed = 0.2;
	this->autoSpeed = 0.1;
	this->current = 0;
	this->SpeedLevel = 1;
	srand((unsigned int)time(NULL));
	//this->head = new SnakeNode();
	//this->head->SpriteNode = Sprite::create("SnakeNode.png");
	//游戏状态初始化
	map = new int*[28];
	for (int i = 0; i < 28; i++) {
		map[i] = new int[38];
		for (int j = 0; j < 38; j++) {
			map[i][j] = 0;
		}
	}
	//蛇与食物初始化
	head = SnakeNode::create("SnakeNode.png");
	head->setAnchorPoint(Vec2(0, 0));
	head->setPosition(Vec2(840,450));
	map[14][19] = 1;
	SnakeBody.push_back(head);
	this->addChild(head);
	//单词释义
	des = Label::create(description, "楷体", 16);
	des->setPosition(Vec2(135,600));
	this->addChild(des);
	//得分初始化
	this->score = 0;
	this->score_str = "Score:" + std::to_string(score);
	Score = Label::create(score_str, "fonts/Marker Felt.ttf", 36);
	Score->setPosition(Vec2(135, 800));
	this->addChild(Score);
	//生命初始化
	this->live = 1;
	this->live_str = "Live:" + std::to_string(live);
	this->Live = Label::create(live_str, "fonts/Marker Felt.ttf", 36);
	Live->setPosition(Vec2(135, 750));
	this->addChild(Live);
	//food = Sprite::create("material/food/Apple.png");
	//food->setAnchorPoint(Vec2(0, 0));
	//this->CreatFood();
	//this->addChild(food);
	word = "I";
	for (auto i = 0; i < word.size(); i++) {
		showstr.append("*");
		std::string path = "material/food/apple";
		//log("%c", word[i+3]);
		path = path + (char)tolower(word[i]);
		path.append(".png");
		//log("%s", path.c_str());
		food = cocos2d::Sprite::create(path.c_str());
		if (food != NULL) {
			food->setAnchorPoint(Vec2(0, 0));
			this->CreatFood();
			this->SnakeFood.push_back(food);
			this->addChild(food);
		}
	}
	//map[int(SnakeFood.front()->getPosition().y / 30 - 1)][int(SnakeFood.front()->getPosition().x / 30 - 9)] = 3;
	ShowWord = Label::create(showstr, "fonts/Marker Felt.ttf", 48);
	ShowWord->setPosition(Vec2(135, 650));
	this->addChild(ShowWord);

	//注册键盘监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	if (sceneNum == 0) {
		this->schedule(schedule_selector(GameScene::myupdate), speed);
	}
	else {
		this->schedule(schedule_selector(GameScene::automatic), this->autoSpeed);
	}
	return true;
}

void GameScene::menuCloseCallback(Ref * pSender)
{
	switch (((Node *) pSender)->getTag()) 
	{
	case 1:
		Director::getInstance()->replaceScene(HelloWorld::createScene()); break;
	case 2:
		if (isPlay) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			isPlay = false;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			isPlay = true;
		}break;
	case 3:
		this->SpeedLevel = (SpeedLevel + 1) % 3; //log("%d", SpeedLevel);
		if (this->sceneNum == 0) {
			this->unschedule(schedule_selector(GameScene::myupdate));
			switch (SpeedLevel)
			{
			case 0:this->speed = 0.3; break;
			case 1:this->speed = 0.2; break;
			case 2:this->speed = 0.1; break;
			}
			this->schedule(schedule_selector(GameScene::myupdate), speed);
		}
		else
		{
			this->unschedule(schedule_selector(GameScene::automatic));
			switch (SpeedLevel)
			{
			case 0:this->autoSpeed = 0.2; break;
			case 1:this->autoSpeed = 0.1; break;
			case 2:this->autoSpeed = 0.05; break;
			}
			this->schedule(schedule_selector(GameScene::automatic), autoSpeed);
		}
		switch (SpeedLevel)
		{
		case 0:this->SpeedLB->setString("Speed:Slow"); break;
		case 1:this->SpeedLB->setString("Speed:Medium"); break;
		case 2:this->SpeedLB->setString("Speed:Fast"); break;
		}
	}
	
}

void GameScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)//画线
{
	int dis = 30/*/ contentScaleFactor*/;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	glLineWidth(2);
	ccDrawColor4F(230, 210, 231, 1);
	ccDrawLine(Vec2(270 , 30 ), Vec2(270 , visibleSize.height - dis ));
	ccDrawLine(Vec2(270 , 30 ), Vec2(visibleSize.width - dis, 30 ));
	ccDrawLine(Vec2(visibleSize.width - dis , 30 ), Vec2(visibleSize.width - dis , visibleSize.height - dis ));
	ccDrawLine(Vec2(270 , visibleSize.height - dis ), Vec2(visibleSize.width - dis , visibleSize.height - dis ));
	//ccDrawLine(Vec2(270/ contentScaleFactor+origin.x,30/ contentScaleFactor+origin.y), Vec2(270/ contentScaleFactor + origin.x,visibleSize.height-dis + origin.y));
	//ccDrawLine(Vec2(270/ contentScaleFactor + origin.x,30/ contentScaleFactor + origin.y), Vec2(visibleSize.width-dis + origin.x,30/ contentScaleFactor + origin.y));
	//ccDrawLine(Vec2(visibleSize.width-dis + origin.x,30/ contentScaleFactor + origin.y), Vec2(visibleSize.width-dis + origin.x,visibleSize.height-dis + origin.y));
	//ccDrawLine(Vec2(270/ contentScaleFactor + origin.x,visibleSize.height-dis + origin.y), Vec2(visibleSize.width-dis + origin.x,visibleSize.height-dis + origin.y));
}

void GameScene::myupdate(float dt)
{
	this->move();
}

void GameScene::CreatFood()//创建食物
{
	//int y = ((rand() % (28)) + 1) * 30;
	//int x = (rand() % (46 - 9 + 1) + 9) * 30;
	int y = ((rand() % (26)) + 2) * 30;
	int x = (rand() % (44 - 9 + 1) + 10) * 30;
	food->setPosition(Vec2(x, y));
	//log("%d %d", y - 1, x - 9);
	//map[y/30-1][x/30-9] = 2;
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)//键盘监听
{
	//log("Key with keycode %d pressed", keyCode);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (dir != DIR::right) { this->dir = DIR::left; }break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (dir != DIR::left) { this->dir = DIR::right; }break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (dir != DIR::down) { this->dir = DIR::up; }break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (dir != DIR::up) { this->dir = DIR::down; }break;
	default:
		break;
	}
}

void GameScene::move()//控制移动
{
	
	SnakeNode *temp = head; this->EatFood();
	//map[int(SnakeBody[n - 1]->getPosition().y / 30 - 1)][int(SnakeBody[n - 1]->getPosition().x / 30 - 9)] = 0;
	for (int i = n - 1; i > 0; i--) {
		SnakeBody[i]->setPosition(SnakeBody[i - 1]->getPosition());
	}
	//if (n > 1) {
	//	map[int(SnakeBody[1]->getPosition().y / 30 - 1)][int(SnakeBody[1]->getPosition().x / 30 - 9)] = 0;
	//	map[int(SnakeFood.front()->getPosition().y / 30 - 1)][int(SnakeFood.front()->getPosition().x / 30 - 9)] = 3;
	//}
	switch (dir)
	{
	case DIR::up:
		this->head->setPosition(Vec2(temp->getPositionX(), temp->getPositionY() + temp->getContentSize().height));
		break;
	case DIR::down:
		this->head->setPosition(Vec2(temp->getPositionX(), temp->getPositionY() - temp->getContentSize().height));
		break;
	case DIR::right:
		this->head->setPosition(Vec2(temp->getPositionX() + temp->getContentSize().width, temp->getPositionY())); 
		break;
	case DIR::left:
		this->head->setPosition(Vec2(temp->getPositionX() - temp->getContentSize().width, temp->getPositionY()));
		break;
	default:
		break;
	}
	//if (this->IsOut()) {
	//	log("IsOut");
	//}
	//if (this->EatSelf()) {
	//	log("EatSelf");
	//}
	if (this->IsOut()||this->EatSelf())
	{
		this->n = 1;
		int i = SnakeBody.size();
		while (i>1)
		{
			this->removeChild(SnakeBody.at(i-1));
			SnakeBody.pop_back();
			i--;
		}
		head->setPosition(Vec2(840,450));
		while (!Path.empty())
		{
			Path.pop();
		}
		live--;
		if (live == 0) {
			p_Res->ResScore = this->score;
			Director::getInstance()->replaceScene(MyResult::createScene());
		}
	}
	//map[int(head->getPosition().y / 30 - 1)][int(head->getPosition().x / 30 - 9)] = 1;
}

void GameScene::EatFood()//判断是否迟到食物
{
	if (head->getPosition() != SnakeFood.front()->getPosition()) {
		return;
	}
	SnakeNode* newSnakeNode = SnakeNode::create("SnakeNode.png");
	newSnakeNode->setAnchorPoint(Vec2(0, 0));
	newSnakeNode->setPosition(food->getPosition());
	this->addChild(newSnakeNode);
	SnakeBody.push_back(newSnakeNode);

	this->removeChild(SnakeFood.front());
	
	//修改显示的单词
	this->showstr[current] = word[current];
	current++;
	//log("%s", showstr.c_str());
	this->ShowWord->setString(showstr);
	SnakeFood.pop_front();

	//修改显示分数
	this->score = this->score + 100;
	//判断是否修改生命数
	if (!(score %1000)) {
		live++;
		this->live_str = "Live:" + std::to_string(live);
		this->Live->setString(live_str);
	}
	this->score_str.clear();
	this->score_str = "Score:" + std::to_string(score);
	this->Score->setString(score_str);

	if (SnakeFood.empty()) {
		current = 0; showstr.clear();
		this->ReadWord();// log("%d", word.size());
		for (auto i = 0; i < word.size() ; i++) {
			showstr.append("*");
			std::string path = "material/food/apple";
			//log("%c", word[i + 3]);
			path = path + (char)tolower(word.at(i));
			path.append(".png");
			//log("%s", path.c_str());
			food = cocos2d::Sprite::create(path.c_str());
			if (food != NULL) {
				food->setAnchorPoint(Vec2(0, 0));
				this->CreatFood();
				this->SnakeFood.push_back(food);
				this->addChild(food);
			}
		}
		this->ShowWord->setString(showstr);
		des->setString(description);
	}
	this->n++;
	//this->move();
}

bool GameScene::ReadWord() {//读取单词
	std::string s="";
	std::getline(fin, s);
	auto i = 0;
	word.clear(); description.clear();
	//while (s[i]!=' ')
	//{
	//	i++;
	//}i++;
	while (s[i]!=' ')
	{
		word = word + s[i]; i++;
	}
	while (i<s.size())
	{
		if (s[i] == ' ') {
			description.append("\n");
		}
		else
		{
			description = description + s[i]; 
		}
		i++;
	}
	return true;
}
void GameScene::searchPath()
{
	this->move();
	this->ResetMap();
	AStar *newAStar = new AStar(map, int(head->getPosition().x / 30 - 9), int(head->getPosition().y / 30 - 1), int(SnakeFood.front()->getPosition().x / 30 - 9), int(SnakeFood.front()->getPosition().y / 30 - 1));
	newAStar->FindPath();
	while (!Path.empty())
	{
		Path.pop();
	}
	this->Path = newAStar->getPath();
	delete newAStar;
}

void GameScene::automatic(float dt)
{
	if (Path.size() <= 1) { this->searchPath(); }
	Point *start = Path.top();
	Path.pop();
	Point *to = Path.top();
	int x = to->x - start->x;
	int y = to->y - start->y;
	if (x == 0 && y == 1) { dir = DIR::up; }
	if (x == 0 && y == -1) { dir = DIR::down; }
	if (x == -1 && y == 0) { dir = DIR::left; }
	if (x == 1 && y == 0) { dir = DIR::right; }
	this->move();
}

void GameScene::ResetMap() {//遍历当前图
	//当前游戏的状态 0表示路，1表示起点，2表示障碍，3表示终点
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 38; j++) {
			map[i][j] = 0;
		}
	}
	for (auto node : SnakeBody) {
		map[int(node->getPosition().y / 30 - 1)][int(node->getPosition().x / 30 - 9)] = 2;
	}
	for (auto node : SnakeFood) {
		map[int(node->getPosition().y / 30 - 1)][int(node->getPosition().x / 30 - 9)] = 2;
	}
	map[int(SnakeFood.front()->getPosition().y / 30 - 1)][int(SnakeFood.front()->getPosition().x / 30 - 9)] = 3;
	map[int(head->getPosition().y / 30 - 1)][int(head->getPosition().x / 30 - 9)] = 1;
}

bool GameScene::EatSelf() {
	for (int i = 1; i < SnakeBody.size(); i++) {
		if (head->getPosition() == SnakeBody.at(i)->getPosition()) {
			return true;
		}
	}
	for (auto node : SnakeFood) {
		if (head->getPosition() == node->getPosition()&&head->getPosition()!=SnakeFood.front()->getPosition()) {
			return true;
		}
	}
	return false;
}

bool GameScene::IsOut() {
	float x = head->getPosition().x;
	float y = head->getPosition().y;
	if (x < 270 || x>1410 || y < 30 || y>870) {
		return true;
	}
	else
	{
		return false;
	}
}