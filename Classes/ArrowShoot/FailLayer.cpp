#include"FailLayer.h"
#include"MainScene.h"
#include "SceneMComplete.h"
#include "MainSceneFirst.h"
#include "LevelInfo.h"

Scene* FailLayer::CreateScene()
{
	auto scene = Scene::create();
	auto layer = FailLayer::create();
	scene->addChild(layer);
	return scene;
}

bool FailLayer::init()
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

	auto againButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("UI/again.png"),
		Sprite::createWithSpriteFrameName("UI/again.png"),
		CC_CALLBACK_1(FailLayer::menuAgainCallBack, this));

	auto menuButton = MenuItemSprite::create(
		Sprite::create("UI/menu.png"),
		Sprite::create("UI/menu.png"),
		CC_CALLBACK_1(FailLayer::menuMenuCallBack, this));

    auto nextItem = Sprite::createWithSpriteFrameName("UI/next.png");
    auto nextItemOn = Sprite::createWithSpriteFrameName("UI/next.png");
    nextItemOn->setScale(0.9f);
    auto next = MenuItemSprite::create(nextItem, nextItemOn, [=](Ref* pSender){
        extern enum _nowScene nowScene;
        nowScene = Game3;
        this->removeAllChildren();
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(SceneMComplete::createScene(3));
    });

    auto menu = Menu::create(againButton, menuButton, next, NULL);
	menu->setPosition(0, 0);
    againButton->setPosition(Vec2(visibleSize.width / 2 - nextItem->getContentSize().width, visibleSize.height / 2 - nextItem->getContentSize().height / 2));
    next->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    menuButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - nextItem->getContentSize().height - 10));
    this->addChild(menu, 2);

	return true;
}

void FailLayer::menuAgainCallBack(Ref* pSender)
{
	if (this->mainPlayLayer != NULL)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(1.5f, MainScene::CreateScene()));
	}
	else if (this->mainStep2Layer != NULL)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(1.5f, MainStep2Scene::CreateScene()));
	}
	else if (this->mainStep3Layer != NULL)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(1.5f, MainStep3Scene::CreateScene()));
	}
}

void FailLayer::menuExitCallBack(Ref* pSender)
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

void FailLayer::menuMenuCallBack(Ref* pSender)
{
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainSceneFirst::createScene()));
}
