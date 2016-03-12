#include "LevelInfo.h"
#include "FD_LabelLayer.h"
#include "SceneMComplete.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;

bool FD_LabelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	flagPause = true;
	flagResume = false;
	flagMusic = true;

	visibleSize = Director::getInstance()->getVisibleSize();

	auto line = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("SkullBarMain.png"));  //边框
	line->setPosition(visibleSize / 2);
	this->addChild(line, 0);

	this->CreateHPLabel();

	this->scheduleUpdate();

	// 创建暂停的侦听器
	pauseListener = EventListenerKeyboard::create();
	pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && flagPause)
		{
			flagPause = !flagPause;
			pauseScene();
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);

	return true;
}

void FD_LabelLayer::update(float delta)
{
	//更新血条
	hpBarblood->setPercentage((float)hero->GetCurrentHP() / (float)hero->GetFullHP() * 100);

	// 检查暂停界面按钮是否删除
	if (flagResume)
	{
		removeChild(menu);
		flagResume = !flagResume;
	}

	return;
}

void FD_LabelLayer::BindHero(FD_Hero* phero)
{
	hero = phero;
	return;
}

void FD_LabelLayer::CreateHPLabel() //血量条
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	hpBar = Sprite::createWithSpriteFrameName("CharHPBack.png"); //背景框
	hpBar->setPosition(280, visibleSize.height - 40);
	this->addChild(hpBar, 1);

	hpBarblood = ProgressTimer::create(Sprite::createWithSpriteFrameName("CharHPFront.png")); //血量条
	hpBarblood->setType(ProgressTimer::Type::BAR); //条形模式
	hpBarblood->setMidpoint(Point(1, 0.5f)); //进度条起始位置
	hpBarblood->setBarChangeRate(Point(1,0)); //表示沿X轴变化
	hpBarblood->setPercentage(100);
	hpBarblood->setPosition(Point(0, 0));
	hpBarblood->setAnchorPoint(Point(0, 0));

	hpBar->addChild(hpBarblood);

	return;
}

void FD_LabelLayer::pauseScene()
{
	//创建暂停菜单模糊背景
	pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	addChild(pauseBackground);

	// 创建暂停界面主UI
	pauseMainUI = Sprite::create("pause.png");
	pauseMainUI->setPosition(visibleSize / 2);
	addChild(pauseMainUI);

	// 全体暂停，侦听器不处理
	Director::getInstance()->pause();

	// ESC返回游戏
	pauseListener = EventListenerKeyboard::create();
	pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && !flagPause)
		{
			resumeScene();
		}
	};

	// 创建返回游戏按钮
	auto resumeSprite = Sprite::create("resume.png");
	auto resumeSprite2 = Sprite::create("resume.png");
	resumeSprite2->setScale(0.98f);
	resume = MenuItemSprite::create(resumeSprite, resumeSprite2, [=](Ref* pSender){
		resumeScene();
	});
	resume->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	// 创建新游戏按钮
	auto newGameSprite = Sprite::create("newgame.png");
	auto newGameSprite2 = Sprite::create("newgame.png");
	newGameSprite2->setScale(0.9f);
	newGame = MenuItemSprite::create(newGameSprite, newGameSprite2, [=](Ref* pSender){
		//extern enum _nowScene nowScene;
		//nowScene = Game1;
		//Director::getInstance()->resume();
		//Director::getInstance()->replaceScene(TransitionFade::create(1, SceneMComplete::createScene(1)));
		//return;
		resumeScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, FastDash::createScene()));
	});
	newGame->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// 创建调音乐的按钮
	auto musicSprite = Sprite::create("music.png");
	auto musicSprite2 = Sprite::create("music.png");
	musicSprite2->setScale(0.9f);
	music = MenuItemSprite::create(musicSprite, musicSprite2, [=](Ref* pSender){
		if (flagMusic)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		flagMusic = !flagMusic;
	});
	music->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);

	menu = Menu::create(resume, music, newGame, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);
	return;
}

void FD_LabelLayer::resumeScene()
{
	flagResume = true;
	removeChild(pauseMainUI);
	removeChild(pauseBackground);
    removeChild(menu);
	flagPause = !flagPause;
	Director::getInstance()->resume();
	Director::getInstance()->getEventDispatcher()->removeEventListener(pauseListener);
	return;
}