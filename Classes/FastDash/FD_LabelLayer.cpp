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

	auto line = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("SkullBarMain.png"));  //�߿�
	line->setPosition(visibleSize / 2);
	this->addChild(line, 0);

	this->CreateHPLabel();

	this->scheduleUpdate();

	// ������ͣ��������
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
	//����Ѫ��
	hpBarblood->setPercentage((float)hero->GetCurrentHP() / (float)hero->GetFullHP() * 100);

	// �����ͣ���水ť�Ƿ�ɾ��
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

void FD_LabelLayer::CreateHPLabel() //Ѫ����
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	hpBar = Sprite::createWithSpriteFrameName("CharHPBack.png"); //������
	hpBar->setPosition(280, visibleSize.height - 40);
	this->addChild(hpBar, 1);

	hpBarblood = ProgressTimer::create(Sprite::createWithSpriteFrameName("CharHPFront.png")); //Ѫ����
	hpBarblood->setType(ProgressTimer::Type::BAR); //����ģʽ
	hpBarblood->setMidpoint(Point(1, 0.5f)); //��������ʼλ��
	hpBarblood->setBarChangeRate(Point(1,0)); //��ʾ��X��仯
	hpBarblood->setPercentage(100);
	hpBarblood->setPosition(Point(0, 0));
	hpBarblood->setAnchorPoint(Point(0, 0));

	hpBar->addChild(hpBarblood);

	return;
}

void FD_LabelLayer::pauseScene()
{
	//������ͣ�˵�ģ������
	pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	addChild(pauseBackground);

	// ������ͣ������UI
	pauseMainUI = Sprite::create("pause.png");
	pauseMainUI->setPosition(visibleSize / 2);
	addChild(pauseMainUI);

	// ȫ����ͣ��������������
	Director::getInstance()->pause();

	// ESC������Ϸ
	pauseListener = EventListenerKeyboard::create();
	pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && !flagPause)
		{
			resumeScene();
		}
	};

	// ����������Ϸ��ť
	auto resumeSprite = Sprite::create("resume.png");
	auto resumeSprite2 = Sprite::create("resume.png");
	resumeSprite2->setScale(0.98f);
	resume = MenuItemSprite::create(resumeSprite, resumeSprite2, [=](Ref* pSender){
		resumeScene();
	});
	resume->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	// ��������Ϸ��ť
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

	// ���������ֵİ�ť
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