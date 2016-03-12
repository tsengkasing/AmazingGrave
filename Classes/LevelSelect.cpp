#include "LevelSelect.h"
#include "cocos2d\extensions\GUI\CCScrollView\CCScrollView.h"
USING_NS_CC;
#define ADJUST_SCORLLVIEW_COUNT 4
Scene* LevelSelect::createScene()
{
	Scene* scene = Scene::create();
	auto layer = LevelSelect::create();
	scene->addChild(layer);
	return scene;
}

bool LevelSelect::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->setTouchEnabled(true);
	//this->scheduleUpdate();

	auto background = Sprite::create("MComplete_BG.jpg");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 0);

	Size winSize = Director::getInstance()->getWinSize();
	auto layer = Layer::create();
	level = layer;
	this->addChild(layer);
	auto menu = Menu::create();
	for (int i = 0; i < ADJUST_SCORLLVIEW_COUNT; i++) {
		Sprite* sprite;
		Sprite* Bsprite;
		Sprite* block = Sprite::create("bulletSize.png");
		if (i == 0) {
			sprite = Sprite::create("G1.jpg");
			Bsprite = Sprite::create("Charcters/xx.png");
		}
		else if (i == 1) {
			sprite = Sprite::create("G2.jpg");
			Bsprite = Sprite::create("Charcters/ss.png");
		}
		else if (i == 2) {
			sprite = Sprite::create("G3.jpg");
			Bsprite = Sprite::create("Charcters/hl.png");
		}
		else if (i == 3) {
			sprite = Sprite::create("G4.png");
			Bsprite = Sprite::create("Charcters/zj.png");
		}
		else {
			sprite = Sprite::create("GraveMainScene.png");
			Bsprite = Sprite::create("B_zijian_magic.png");
		}
		//block->setContentSize(sprite->getContentSize());
		sprite->setScale(0.4f);
		Bsprite->setScale(0.7f);
		auto item = MenuItemSprite::create(sprite, Bsprite);
		menu->addChild(item);
		//sprite->setPosition(visibleSize.width / 2 + i*visibleSize.width, visibleSize.height / 2);
		//layer->addChild(sprite);
	}
	layer->addChild(menu);
	menu->alignItemsHorizontallyWithPadding(visibleSize.width);

	auto mouse = EventListenerTouchOneByOne::create();
	mouse->onTouchBegan = [=](Touch* touch, Event* event){
		Point _touch = touch->getLocation();
		if (_touch.x >= (visibleSize.width / 2.0f)) {
			if (layer->getPositionX() + (ADJUST_SCORLLVIEW_COUNT)* visibleSize.width <= (visibleSize.width / 2))
				return true;
			layer->runAction(RepeatForever::create(MoveBy::create(1.0f, Vec2(-500, 0))));
		}
		else {
			if (layer->getPositionX() > 0)
				return true;
			layer->runAction(RepeatForever::create(MoveBy::create(1.0f, Vec2(500, 0))));
		}
		return true;
	};
	mouse->onTouchEnded = [=](Touch* touch, Event* event){
		//Point _touch = touch->getLocation();
		layer->stopAllActions();
		return;
	};

	_eventDispatcher->addEventListenerWithFixedPriority(mouse, 1);

	return true;
}

void LevelSelect::update(float delta)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (level->getPositionX() + (ADJUST_SCORLLVIEW_COUNT - 1)* visibleSize.width <= 0)
		level->setPositionX( - (ADJUST_SCORLLVIEW_COUNT - 1)* visibleSize.width);
	if (level->getPositionX() > 0)
		level->setPositionX(0);
	return;
}