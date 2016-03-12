#include"PauseLayer.h"
#include"MainScene.h"
#include "LevelInfo.h"
#include "SceneMComplete.h"

int PauseLayer::step = 1;

Scene* PauseLayer::CreateScene()
{
	auto scene = Scene::create();
	auto layer = PauseLayer::create();
	scene->addChild(layer);
	return scene;
}

bool PauseLayer::init()
{
	if (!Layer::create())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::createWithSpriteFrameName("pausebackground.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 1);

	auto pauseSprite = Sprite::createWithSpriteFrameName("pause.png");
	pauseSprite->setPosition(visibleSize / 2);
	this->addChild(pauseSprite, 1);

	auto againButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("UI/again.png"),
		Sprite::createWithSpriteFrameName("UI/again.png"),
		CC_CALLBACK_1(PauseLayer::menuAgainCallBack, this));

    auto nextButton = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("UI/next.png"),
        Sprite::createWithSpriteFrameName("UI/next.png"),
        CC_CALLBACK_1(PauseLayer::menuNextCallBack, this));
	
	auto resumeButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("UI/resume.png"),
		Sprite::createWithSpriteFrameName("UI/resume.png"),
		CC_CALLBACK_1(PauseLayer::menuResumeCallBack, this));
	
	auto exitButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(PauseLayer::menuExitCallBack, this));

    // 创建调音乐的按钮
    auto musicSprite = Sprite::create("music.png");
    auto musicSprite2 = Sprite::create("music.png");
    musicSprite2->setScale(0.9f);
    auto music = MenuItemSprite::create(musicSprite, musicSprite2, [=](Ref* pSender){
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
	
    auto menu = Menu::create(resumeButton, nextButton, againButton, music, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
	menu->alignItemsVertically();
	this->addChild(menu, 1);

	return true;
}

void PauseLayer::menuNextCallBack(Ref* pSender)
{
    extern enum _nowScene nowScene;
    nowScene = Game3;
    this->removeAllChildren();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(SceneMComplete::createScene(3));
}

void PauseLayer::menuResumeCallBack(Ref* pSender)
{
	if (this->mainPlayLayer != NULL)
	{
		this->mainPlayLayer->flagPressed = false;
		if (this->mainPlayLayer->arrow->isflying == true)
		{
			this->mainPlayLayer->arrow->getArrowSprite()->getPhysicsBody()->setVelocity(this->mainPlayLayer->getSpeed());
			this->mainPlayLayer->arrow->getArrowSprite()->getPhysicsBody()->setGravityEnable(true);
		}
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();

	}
	else if (this->mainStep2Layer != NULL)
	{
		this->mainStep2Layer->flagPressed = false;
		if (this->mainStep2Layer->arrow->isflying == true)
		{
			this->mainStep2Layer->arrow->getArrowSprite()->getPhysicsBody()->setVelocity(this->mainStep2Layer->getSpeed());
			this->mainStep2Layer->arrow->getArrowSprite()->getPhysicsBody()->setGravityEnable(true);
		}
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
	}
	else if (this->mainStep3Layer != NULL)
	{
		this->mainStep3Layer->flagPressed = false;
		if (this->mainStep3Layer->arrow->isflying == true)
		{
			this->mainStep3Layer->arrow->getArrowSprite()->getPhysicsBody()->setVelocity(this->mainStep3Layer->getSpeed());
			this->mainStep3Layer->arrow->getArrowSprite()->getPhysicsBody()->setGravityEnable(true);		
		}
        this->removeFromParentAndCleanup(true);
        Director::getInstance()->resume();
	}
}

void PauseLayer::menuAgainCallBack(Ref* pSender)
{

    //Director::getInstance()->popScene();
    //return;
	if (this->mainPlayLayer != NULL)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();

		Director::getInstance()->replaceScene(MainScene::CreateScene());

	}
	else if (this->mainStep2Layer != NULL)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();

		Director::getInstance()->replaceScene(MainStep2Scene::CreateScene());
	}
	else if (this->mainStep3Layer != NULL)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();

		Director::getInstance()->replaceScene(MainStep3Scene::CreateScene());
	
	}
}

void PauseLayer::menuExitCallBack(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
    //extern enum _nowScene nowScene;
    //nowScene = Game3;

    //Director::getInstance()->resume();
    //Director::getInstance()->replaceScene(SceneMComplete::createScene(3));
    //return;
    //Director::getInstance()->end();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}