#include"WinLayer.h"
#include"MainScene.h"
#include "SceneMComplete.h"
#include "MainSceneFirst.h"
#include "LevelInfo.h"

Scene* WinLayer::CreateScene()
{
	auto scene = Scene::create();
	auto layer = WinLayer::create();
	scene->addChild(layer);
	return scene;
}

bool WinLayer::init()
{
	if (!Layer::create())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::createWithSpriteFrameName("pausebackground.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 0);

	Sprite* endSprite = Sprite::createWithSpriteFrameName("UI/End.png");
	endSprite->setPosition(visibleSize / 2);
	this->addChild(endSprite, 1);

	//auto nextButton = MenuItemSprite::create(
	//	Sprite::createWithSpriteFrameName("UI/next.png"),
	//	Sprite::createWithSpriteFrameName("UI/next.png"),
	//	CC_CALLBACK_1(WinLayer::menuNextCallBack, this));

    auto nextItem = Sprite::createWithSpriteFrameName("UI/next.png");
    auto nextItemOn = Sprite::createWithSpriteFrameName("UI/next.png");
    nextItemOn->setScale(0.9f);
    auto next = MenuItemSprite::create(nextItem, nextItemOn, [=](Ref* pSender){
        unschedule(schedule_selector(MainScene::judge));
        extern enum _nowScene nowScene;
        nowScene = Game3;
        this->removeAllChildren();
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(SceneMComplete::createScene(3));
    });

	auto againButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("UI/again.png"),
		Sprite::createWithSpriteFrameName("UI/again.png"),
		CC_CALLBACK_1(WinLayer::menuAgainCallBack, this));

	auto menuButton = MenuItemSprite::create(
		Sprite::create("UI/menu.png"),
		Sprite::create("UI/menu.png"),
		CC_CALLBACK_1(WinLayer::menuMenuCallBack, this));

	auto exitButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("UI/exit.png"),
		Sprite::createWithSpriteFrameName("UI/exit.png"),
		CC_CALLBACK_1(WinLayer::menuExitCallBack, this));
    auto menu = Menu::create(next, menuButton, againButton, NULL);
	menu->setPosition(0,0);
    againButton->setPosition(Vec2(visibleSize.width / 2 - nextItem->getContentSize().width, visibleSize.height / 2 - nextItem->getContentSize().height / 2));
    next->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    menuButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - nextItem->getContentSize().height - 10));
	this->addChild(menu, 2);

	return true;
}

void WinLayer::menuAgainCallBack(Ref* pSender)
{
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(MainScene::CreateScene());
}

void WinLayer::menuExitCallBack(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void WinLayer::menuMenuCallBack(Ref* pSender)
{
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainSceneFirst::createScene()));
}
