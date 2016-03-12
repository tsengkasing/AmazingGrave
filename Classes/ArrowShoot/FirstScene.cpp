#include"FirstScene.h"
#include"MainScene.h"
#include"MapScene.h"
#include"MainStep3Scene.h"

Scene* FirstScene::CreateScene(){
	auto scene = Scene::create();
	auto layer = FirstScene::create();
	scene->addChild(layer);
	return scene;
}

bool FirstScene::init(){
	if (!Layer::create()){
		return false;
	}
	auto dirs = Director::getInstance();
	Size visibleSize = dirs->getVisibleSize();
	/*Òì²½¼ÓÔØ*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Pictures.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AS_Zombie.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_Figure.plist");

	auto backGround = Sprite::createWithSpriteFrameName("SkullBarMain.png");
	backGround->setPosition(visibleSize / 2);
	this->addChild(backGround);
	
	auto label = Label::create("My Game", "Marker Felt", 36);
	label->setPosition(ccp(visibleSize.width / 2, visibleSize.height -50));
	this->addChild(label,1);

	auto startItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("Play.png"),
		Sprite::createWithSpriteFrameName("Play.png"),
		CC_CALLBACK_1(FirstScene::menuStartCallback, this));
	auto closeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(FirstScene::menuCloseCallback, this));
	
	auto menu = Menu::create(startItem, closeItem, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 1);
	
	return true;
}

void FirstScene::menuStartCallback(Ref* pSender){
	Director::getInstance()->replaceScene(
		TransitionSplitRows::create( 3.0f,MainScene::CreateScene()));
}

void FirstScene::menuCloseCallback(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}