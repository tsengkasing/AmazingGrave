#include "FastDash.h"
#include "FD_BossScene.h"
#include "FD_MonsterCreater.h"
#include "MainSceneFirst.h"
#include "FlowWord.h"
#include "LevelInfo.h"
#include "SceneMComplete.h"

using CocosDenshion::SimpleAudioEngine;

FastDash::FastDash()
{
	time = 0.0f;
	hero = FD_Hero::create();
}

Scene* FastDash::createScene()
{
	Scene* scene = Scene::create();
	FastDash* layer = FastDash::create();
	layer->labellayer = FD_LabelLayer::create();
	scene->addChild(layer);
	scene->addChild(layer->labellayer);

	layer->labellayer->BindHero(layer->hero); //分数层绑定英雄 获取英雄信息。

	return scene;
}

bool FastDash::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Director::getInstance()->resume(); //如果处于暂停状态，则恢复
	
	map = TMXTiledMap::create("F_GamerLayerBG.tmx");
	Size mapTiledNum = map->getMapSize(); //瓦片地图瓦片个数
	Size tiledSize = map->getTileSize(); //瓦片地图每一片大小
	mapSize = Size::Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height); //瓦片地图大小
	this->addChild(map, -1);

	auto instruction = FlowWord::create(); //游戏提示
	auto follow = Follow::create(this);
	instruction->runAction(follow);
	this->addChild(instruction);
	instruction->ShowText("Use W/S or \n Up/Down to move !", 10.0f, 1, Point(20, 20), Color3B(192, 192, 192));
	
	this->initRole(); //初始化角色

	this->AddEffect(); //投放粒子特效

	this->scheduleUpdate(); //开启update函数
	
	this->setKeyboardEnabled(true); //开启键盘监听
	auto controller = EventListenerKeyboard::create();
	controller->onKeyPressed = CC_CALLBACK_2(FastDash::onKeyPressed, this);
	controller->onKeyReleased = CC_CALLBACK_2(FastDash::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controller, this);

	return true;
}


void FastDash::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event) // 监听键盘按下
{
	switch (keycode)
	{
	case (EventKeyboard::KeyCode::KEY_W) :
		hero->Move(0, 5); break;
	case (EventKeyboard::KeyCode::KEY_S) :
		hero->Move(0, -5); break;
	case (EventKeyboard::KeyCode::KEY_UP_ARROW) :
		hero->Move(0, 5); break;
	case (EventKeyboard::KeyCode::KEY_DOWN_ARROW) :
		hero->Move(0, -5); break;
	default:
		return;
	}
	return;
}

void FastDash::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event) //监听键盘松开
{
	switch (keycode)
	{
	case (EventKeyboard::KeyCode::KEY_W) :
		hero->stopAllActions(); break;
	case (EventKeyboard::KeyCode::KEY_S) :
		hero->stopAllActions(); break;
	case (EventKeyboard::KeyCode::KEY_UP_ARROW) :
		hero->stopAllActions(); break;
	case (EventKeyboard::KeyCode::KEY_DOWN_ARROW) :
		hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_P) :
        hero->setPosition(mapSize.width - 100, mapSize.height / 2);
        break;
	default:
		return;
	}
	return;
}

void FastDash::update(float delta) //每一帧更新函数
{
	time += 0.0043f;
	log("%.4f", time);
	//限制英雄活动范围
	if (hero->getPositionY() >= mapSize.height - 150)
	{
		hero->setPositionY(mapSize.height - 150);
	}
	else if (hero->getPositionY() <= 0)
	{
		hero->setPositionY(0);
	}

	//进入Boss场景
	if (hero->getPositionX() >= mapSize.width - 60)
	{
		this->Next();
		return;
	}

	//失败
	if (hero->GetCurrentHP() <= 0)
	{
		this->Fail();
		return;
	}

	auto regularMove = MoveBy::create(0.01f, Vec2(2.2f + 1.2 * time, 0)); //游戏常规速度
	hero->runAction(regularMove);

	//镜头跟随英雄
	this->SetViewByHero();

	return;
}

void FastDash::SetViewByHero()
{
	Point heroPos = hero->getPosition();
	float x = MAX(heroPos.x + 290, visibleSize.width / 2);
	float y = MAX(heroPos.y + 290, visibleSize.height / 2);

	x = MIN(x, mapSize.width - visibleSize.width / 2);
	y = MIN(y, mapSize.height - visibleSize.height / 2);

	Point destPos = Point(x, y);

	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = ccpSub(centerPos, destPos);

	this->setPosition(viewPos);

	return;
}

void FastDash::initRole() //初始化角色
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	hero->BindSprite(Sprite::createWithSpriteFrameName("F_LittleStar.png")); //初始化英雄
	hero->setPosition(visibleSize.width * 0.1f, visibleSize.height / 2 - 50);
	hero->setScale(0.1f);
	hero->MovingAnimation();
	this->addChild(hero, 2);

	auto f1MonsterContro = FD_MonsterCreater::create();
	f1MonsterContro->SetMonsterPic("F_BagSprite.png"); //袋子精
	f1MonsterContro->SetShowTime(0.0f);
	f1MonsterContro->LetGo(10, 0.32f, 100);
	f1MonsterContro->BindHero(hero);
	this->addChild(f1MonsterContro, 3);

	auto f2MonsterContro = FD_MonsterCreater::create();
	f2MonsterContro->SetShowTime(10.0f);
	f2MonsterContro->SetMonsterPic("F_Banana.png"); //香蕉怪
	f2MonsterContro->LetGo(10, 0.19f, 100);
	f2MonsterContro->BindHero(hero);
	this->addChild(f2MonsterContro, 3);

	auto s1MonsterContro = FD_MonsterCreater::create();
	s1MonsterContro->SetShowTime(50.0f);
	s1MonsterContro->SetMonsterPic("F_Donggua.png"); //冬瓜怪
	s1MonsterContro->LetGo(10, 0.32f, 150);
	s1MonsterContro->BindHero(hero);
	this->addChild(s1MonsterContro, 3);

	auto s2MonsterContro = FD_MonsterCreater::create();
	s2MonsterContro->SetMonsterPic("F_ThunderBall.png"); //怪物闪电球
	s1MonsterContro->SetShowTime(60.0f);
	s2MonsterContro->LetGo(10, 0.18f, 150);
	s2MonsterContro->BindHero(hero);
	this->addChild(s2MonsterContro, 3);

	auto tMonsterContro = FD_MonsterCreater::create(); //怪物蝙蝠
	tMonsterContro->SetShowTime(150.0f);
	tMonsterContro->SetMonsterPic("F_Bat.png");
	tMonsterContro->BindHero(hero);
	tMonsterContro->LetGo(8, 0.32f, 200);
	this->addChild(tMonsterContro, 3);

	auto MedicContro = FD_MonsterCreater::create(); //药箱
	MedicContro->SetMonsterPic("F_midic.png");
	MedicContro->SetShowTime(60.0f);
	MedicContro->LetGo(3, 0.4f, -100);
	MedicContro->BindHero(hero);
	this->addChild(MedicContro, 3);

	return;
}

void FastDash::AddEffect() //粒子特效
{
	// 创建粒子
	ParticleSystemQuad* emitter[12];
	ParticleBatchNode* batch[12];
	
	for (int i = 0; i < 12; i++)
	{
		if (i % 2 == 0)
		{
			emitter[i] = ParticleSystemQuad::create("F_lizi01.plist");
		}
		else
		{
			emitter[i] = ParticleSystemQuad::create("F_lizi02.plist");
		}
		emitter[i]->retain();
		batch[i] = ParticleBatchNode::createWithTexture(emitter[i]->getTexture());
		batch[i]->addChild(emitter[i]);
		emitter[i]->setPosition(mapSize.width * CCRANDOM_0_1(), mapSize.height * CCRANDOM_0_1());
		emitter[i]->release();
		this->addChild(batch[i], 0);
	}

	return;
}

void FastDash::Next()
{
	auto reScene = FD_BossScene::createScene(hero->GetCurrentHP());
	this->removeAllChildren();
	Director::getInstance()->replaceScene(reScene);
	return;
}

void FastDash::Fail()
{
	Director::getInstance()->pause();

	//创建模糊背景
	auto pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	this->addChild(pauseBackground, 9);

	auto background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("End.png"));
	background->setPosition(hero->getPositionX() + 300, visibleSize.height / 2);
	this->addChild(background, 10);

	auto again = Sprite::createWithSpriteFrameName("UI/again.png");
	auto againOn = Sprite::createWithSpriteFrameName("UI/again.png");
    againOn->setScale(0.9f);

	auto restart = MenuItemSprite::create(again, againOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
		Director::getInstance()->replaceScene(TransitionFade::create(1, FastDash::createScene()));
	});

    auto nextItem = Sprite::createWithSpriteFrameName("UI/next.png");
    auto nextItemOn = Sprite::createWithSpriteFrameName("UI/next.png");
    nextItemOn->setScale(0.9f);

    auto nextScene = MenuItemSprite::create(nextItem, nextItemOn, [=](Ref* pSender){
        extern enum _nowScene nowScene;
        nowScene = Game1;
        this->removeFromParent();
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(TransitionFade::create(1, SceneMComplete::createScene(1)));
    });

	auto backMenu = Sprite::create("UI/menu.png");
	auto backMenuOn = Sprite::create("UI/menu.png");
    backMenuOn->setScale(0.9f);

	auto back = MenuItemSprite::create(backMenu, backMenuOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainSceneFirst::createScene()));
	});

    auto menu = Menu::create(nextScene, restart, back, nullptr);
	menu->setPosition(0, 0);
    restart->setPosition(Vec2(hero->getPositionX() + 300 - nextItem->getContentSize().width, visibleSize.height / 2 - nextItem->getContentSize().height / 2));
    nextScene->setPosition(Vec2(hero->getPositionX() + 300, visibleSize.height / 2));
    back->setPosition(Vec2(hero->getPositionX() + 300, visibleSize.height / 2 - nextItem->getContentSize().height - 10));

	this->addChild(menu, 10);

	int score = time / 11.0813f * 60;
	auto scoreLabel = LabelTTF::create("0000", "angryblue", 34);
	scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
	scoreLabel->setPosition(hero->getPositionX() + 300, visibleSize.height * 0.64);
	this->addChild(scoreLabel, 11);

	return;
}