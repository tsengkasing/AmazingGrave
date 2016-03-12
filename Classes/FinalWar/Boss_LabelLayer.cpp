#include "Boss_LabelLayer.h"
#include "MainSceneFirst.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;

bool Boss_LabelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	flagPause = true;
	flagResume = false;
	flagMusic = true;

	auto line = Sprite::create("SkullBarMain.png");  //边框
	line->setPosition(visibleSize / 2);
	this->addChild(line, 0);

	this->CreateHPLabel();

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

	this->scheduleUpdate();

	return true;
}

void Boss_LabelLayer::End()
{
    Vector<SpriteFrame *>loadVector;
    char name[12];

    for (int i = 1; i <= 6; i++)
    {
        sprintf(name, "light%d.png", i);
        loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    }

    auto light = Sprite::create();
    light->setPosition(visibleSize / 2);
    this->addChild(light, 13);

    //出现光芒 屏幕变白
    light->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 13.0f)), nullptr));

    //子鉴出现
    auto zijian = Sprite::createWithSpriteFrameName("B_zijian.png");
    zijian->setScale(0.12f);
    zijian->setPosition(gamerlayer->zijian->getPosition());
    this->addChild(zijian, 14);

    //三人
    auto forset = Sprite::createWithSpriteFrameName("B_sensen.png");
    forset->setPosition(visibleSize.width * 0.35f, visibleSize.height / 2);
    forset->setScale(0.24);
    this->addChild(forset, 14);
    auto huolong = Sprite::createWithSpriteFrameName("B_huolong.png");
    huolong->setPosition(visibleSize.width * 0.63f, visibleSize.height / 2);
    huolong->setScale(0.24f);
    this->addChild(huolong, 14);
    auto star = Sprite::createWithSpriteFrameName("B_Star.png");
    star->setPosition(visibleSize.width * 0.25f, visibleSize.height / 2);
    star->setScale(0.41f);
    this->addChild(star, 14);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGM.mp3");
    scheduleOnce([=](float){
        zijian->setTexture("Drawings/zj_Innocent.png");
        zijian->setScale(0.2f);
    }, 4.2f, "Test");

    auto bossAct = Sequence::create(
        DelayTime::create(1.2f), Spawn::create(
        MoveTo::create(2.0f, visibleSize / 2), ScaleTo::create(2.0f, 0.30f), nullptr),
        FadeOut::create(1.0f), FadeIn::create(1.5f),
        MoveTo::create(0.3f, Vec2(visibleSize.width * 0.47f, visibleSize.height / 2)),
        nullptr);

    zijian->runAction(bossAct);

    auto fade = Sequence::create(FadeOut::create(0), DelayTime::create(6.0f), FadeIn::create(1.5f), nullptr);
    forset->runAction(fade);
    huolong->runAction(fade->clone());
    star->runAction(fade->clone());

    auto label = Label::create("Thanks For Playing", "fonts/RTWSYueGoTrial-Regular.ttf", 67);
    label->setColor(Color3B(0, 0, 0));
    label->setPosition(visibleSize.width / 2, visibleSize.height * 0.18f);
    this->addChild(label, 14);

    auto labelAct = Sequence::create(FadeOut::create(0), DelayTime::create(7.0f), FadeIn::create(1.0f), nullptr);
    label->runAction(labelAct);

    scheduleOnce([=](float){
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainSceneFirst::createScene()));
    }, 10.0f, "out");

    return;
}

void Boss_LabelLayer::SetScore(float grade)
{
	this->score = grade;
	return;
}

float Boss_LabelLayer::GetScore()
{
	return score;
}

void Boss_LabelLayer::update(float delta)
{
	hpBarblood_H->setPercentage((float)hero->GetCurrentHP() / (float)hero->GetFullHP() * 100);

	hpBarblood_B->setPercentage((float)boss->GetCurrentHP() / (float)boss->GetFullHP() * 100);

	// 检查暂停界面按钮是否删除
	if (flagResume)
	{
		removeChild(menu);
		flagResume = !flagResume;
	}

	return;
}

void Boss_LabelLayer::BindHero(Boss_Hero* phero)
{
	this->hero = phero;
	return;
}

void Boss_LabelLayer::BindBoss(Boss* pboss)
{
	this->boss = pboss;
	return;
}

void Boss_LabelLayer::initMusic() //设置音乐菜单
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	musicOnLabel = MenuItemImage::create("B_musicOn.png", "B_musicOn.png", CC_CALLBACK_1(Boss_LabelLayer::MusicOn, this));
	musicOnLabel->setVisible(false);
	musicOnLabel->setEnabled(false);
	musicOnLabel->setScale(0.6f);

	musicOffLabel = MenuItemImage::create("B_musicOff.png", "B_musicOff.png", CC_CALLBACK_1(Boss_LabelLayer::MusicOff, this));
	musicOffLabel->setScale(0.6f);

	musicMenu = Menu::create(musicOnLabel, musicOffLabel, NULL);
	musicMenu->alignItemsHorizontallyWithPadding(-100.0f);
	musicMenu->setPosition(visibleSize.width * 0.88f, visibleSize.height * 0.10f);

	this->addChild(musicMenu, 1);

	return;
}

void Boss_LabelLayer::MusicOn(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->resumeBackgroundMusic();
	musicOnLabel->setEnabled(false);
	musicOnLabel->setVisible(false);
	musicOffLabel->setEnabled(true);
	musicOffLabel->setVisible(true);
	return;
}

void Boss_LabelLayer::MusicOff(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->pauseBackgroundMusic();
	musicOnLabel->setEnabled(true);
	musicOnLabel->setVisible(true);
	musicOffLabel->setEnabled(false);
	musicOffLabel->setVisible(false);
	return;
}

void Boss_LabelLayer::CreateHPLabel() //血量条
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//Hero
	hpBar_H = Sprite::createWithSpriteFrameName("CharHPBack.png"); //背景框
	hpBar_H->setPosition(290, visibleSize.height - 46);
	this->addChild(hpBar_H, 1);

	hpBarblood_H = ProgressTimer::create(Sprite::createWithSpriteFrameName("CharHPFront.png")); //血量条
	hpBarblood_H->setType(ProgressTimer::Type::BAR); //条形模式
	hpBarblood_H->setMidpoint(Point(0, 0.5f)); //进度条起始位置
	hpBarblood_H->setBarChangeRate(Point(1,0)); //表示沿X轴变化
	hpBarblood_H->setPercentage(100);
	hpBarblood_H->setPosition(Point(0, 0));
	hpBarblood_H->setAnchorPoint(Point(0, 0));

	hpBar_H->addChild(hpBarblood_H);

	//Boss zijian
	hpBar_B = Sprite::createWithSpriteFrameName("BossHPBack.png"); //背景框
	hpBar_B->setPosition(visibleSize.width / 2, 46);
	this->addChild(hpBar_B, 1);

	hpBarblood_B = ProgressTimer::create(Sprite::createWithSpriteFrameName("BossHPFront.png")); //血量条
	hpBarblood_B->setType(ProgressTimer::Type::BAR); //条形模式
	hpBarblood_B->setMidpoint(Point(0, 0.5f)); //进度条起始位置
	hpBarblood_B->setBarChangeRate(Point(1, 0)); //表示沿X轴变化
	hpBarblood_B->setPercentage(100);
	hpBarblood_B->setPosition(Point(0, 0));
	hpBarblood_B->setAnchorPoint(Point(0, 0));

	hpBar_B->addChild(hpBarblood_B);

	return;
}

void Boss_LabelLayer::pauseScene()
{
	//创建暂停菜单模糊背景
	pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	addChild(pauseBackground);

	// 创建暂停界面主UI
	pauseMainUI = Sprite::create("pause.png");
	pauseMainUI->setPosition(visibleSize / 2);
	addChild(pauseMainUI, 5);

	// 全体暂停，侦听器不处理
	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(gamerlayer);

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
		resumeScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, FinalWar::createScene()));
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
	addChild(menu, 6);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);

	return;
}

void Boss_LabelLayer::resumeScene()
{
	flagResume = true;
	removeChild(pauseMainUI);
	removeChild(pauseBackground);
	removeChild(menu);
	flagPause = !flagPause;
	Director::getInstance()->resume();
	Director::getInstance()->getEventDispatcher()->removeEventListener(pauseListener);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(gamerlayer);
	return;
}