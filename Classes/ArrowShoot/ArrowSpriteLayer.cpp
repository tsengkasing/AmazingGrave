#include"ArrowSpriteLayer.h"
#include<cmath>
#include"MonsterSprite.h"

#define pi 3.1415926

int ArrowSpriteLayer::step = 1;

ArrowSpriteLayer* ArrowSpriteLayer::createArrow()
{
	auto arrow = ArrowSpriteLayer::create();

	return arrow;
}

bool ArrowSpriteLayer::init()
{
	if (!Layer::create())
	{
		return false;
	}

	layer1 = nullptr;
	layer2 = nullptr;
	layer3 = nullptr;
	
	switch (this->step)
	{
	case 1: this->ARROWNUMBER = 10; break;
	case 2: this->ARROWNUMBER = 8; break;
	case 3: this->ARROWNUMBER = 7; break;
	default:
		break;
	}

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 1; i <= this->ARROWNUMBER; i++)
	{
		Sprite* ArrowSprite = Sprite::createWithSpriteFrameName("Arrow.png");
		vecArrowSprite.pushBack(ArrowSprite);
	}
	arrowSprite = vecArrowSprite.at(0);
	arrowSprite->setTag(10);
	auto physicsArrowBody = PhysicsBody::createBox(arrowSprite->getContentSize());

	
	physicsArrowBody->setGravityEnable(false);
	/* 设置碰撞掩码*/
	physicsArrowBody->setCategoryBitmask(1); 
	physicsArrowBody->setCollisionBitmask(-1); 
	physicsArrowBody->setContactTestBitmask(-1); 
	physicsArrowBody->setMass(100); 
	
	
	arrowSprite->setPhysicsBody(physicsArrowBody); 
	this->addChild(arrowSprite, 1);

	/*设置触摸监听*/
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(ArrowSpriteLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ArrowSpriteLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ArrowSpriteLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	/*添加计数图标*/
	Sprite* arrowIcon = Sprite::createWithSpriteFrameName("Arrow.png");
	arrowIcon->setPosition(48, visibleSize.height - 25);
	this->addChild(arrowIcon, 1);
	
	this->labelArrowNumLeft = LabelTTF::create("5", "Brush Script MT", 32);
	labelArrowNumLeft->setColor(Color3B(225, 225, 225));
	labelArrowNumLeft->setPosition(100, visibleSize.height - 25);
	this->addChild(labelArrowNumLeft, 1);
	scheduleUpdate();

	return true;
}


bool ArrowSpriteLayer::onTouchBegan(Touch* touch, Event* event)
{
	/*设置时钟频率*/
	this->setTimeFrequency();
	//记录触摸事件发生时的时间
	LARGE_INTEGER startPerformanceCount;
	QueryPerformanceCounter(&startPerformanceCount);
	touchBeganTime = startPerformanceCount.QuadPart;
	/*使箭头装箱鼠标所在位置*/
	Point locationTouch = touch->getLocation();
	Point locationArrowSprite = arrowSprite->getPosition();
	/*计算所需转过的角度*/
	float angel = atan((locationTouch.y - locationArrowSprite.y) / (locationTouch.x - locationArrowSprite.x)) * 180 / pi;
	if (this->isflying == false)
	{
		if (locationTouch.x == locationArrowSprite.x&&locationTouch.y<locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, 90.0);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x == locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -90.0);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -180);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x>locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
		{

		}
		else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y > locationArrowSprite.y)
		{
			RotateTo* rotateTo;
            if (angel>0)
			{
                rotateTo = RotateTo::create(0.1f, -angel);
                arrowSprite->runAction(rotateTo);
            }
            if (angel<0)
			{
                rotateTo = RotateTo::create(0.1f, angel);
                arrowSprite->runAction(rotateTo);
            }
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
        else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
		{
			RotateTo* rotateTo;
            if (angel < 0)
			{
                rotateTo = RotateTo::create(0.1f, -angel);
                arrowSprite->runAction(rotateTo);
            }
            if (angel>0)
			{
                rotateTo = RotateTo::create(0.1f, angel);
                arrowSprite->runAction(rotateTo);
            }
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
        }
		else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -180.0 - angel);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x < locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -180.0 - angel);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
	}
	return true;
}

void ArrowSpriteLayer::onTouchMoved(Touch* touch, Event* event)
{
	/*使箭头转向鼠标所在位置*/
	Point locationTouch = touch->getLocation();
	Point locationArrowSprite = arrowSprite->getPosition();
	/*计算需要转的角度*/
	float angel = atan((locationTouch.y - locationArrowSprite.y) / (locationTouch.x - locationArrowSprite.y)) * 180 / pi;
	if (this->isflying == false)
	{
		if (locationTouch.x == locationArrowSprite.x&&locationTouch.y<locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, 90.0);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x == locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -90.0);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -180);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x>locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
		{

		}
		else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y > locationArrowSprite.y)
		{
            RotateTo* rotateTo;
            if (angel>0){
                rotateTo = RotateTo::create(0.1f, -angel);
                arrowSprite->runAction(rotateTo);
            }
            if (angel<0){
                rotateTo = RotateTo::create(0.1f, angel);
                arrowSprite->runAction(rotateTo);
            }
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
		{
            RotateTo* rotateTo;
            if (angel < 0)
			{
                rotateTo = RotateTo::create(0.1f, -angel);
                arrowSprite->runAction(rotateTo);
            }
            if (angel>0)
			{
                rotateTo = RotateTo::create(0.1f, angel);
                arrowSprite->runAction(rotateTo);
            }
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -180.0 - angel);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
		else if (locationTouch.x < locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
		{
			auto rotateTo = RotateTo::create(0.1f, -180.0 - angel);
			arrowSprite->runAction(rotateTo);
			if (layer1 != nullptr)
			{
				layer1->arch->runAction(rotateTo->clone());
			}
			else if (layer2 != nullptr)
			{
				layer2->arch->runAction(rotateTo->clone());
			}
			else if (layer3 != nullptr)
			{
				layer3->arch->runAction(rotateTo->clone());
			}
		}
	}
}

void ArrowSpriteLayer::onTouchEnded(Touch* touch, Event* event)
{
	
	/*记录触摸事件结束时的时间*/
	LARGE_INTEGER endPerformanceCount;
	QueryPerformanceCounter(&endPerformanceCount);
	touchEndedTime = endPerformanceCount.QuadPart;
	
	/*计算触摸事件发生到结束时的时间间隔*/
	double pressTime;
	pressTime = (touchEndedTime - touchBeganTime) / timeFrequency;
	
	/*设置箭的飞行角度*/
	Point locationTouch = touch->getLocation();
	Point locationArrowSprite = arrowSprite->getPosition();
	float angel= atan((locationTouch.y - locationArrowSprite.y) / (locationTouch.x - locationArrowSprite.y))*180/pi;
	float angel1 = 0;
	if (locationTouch.x == locationArrowSprite.x&&locationTouch.y<locationArrowSprite.y)
	{
		angel1 = -90.0;
	}
	else if (locationTouch.x == locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
	{
		angel1 = 90.0;
	}
	else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
	{
		angel1 = -180;
	}
	else if (locationTouch.x>locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
	{
		angel1 = 0;
	}
	else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y > locationArrowSprite.y)
	{
		angel1 = angel;
	}
	else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
	{
		angel1 = angel;
	}
	else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
	{
		angel1 = 180.0 + angel;
	}
	else if (locationTouch.x < locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
	{
		angel1 = 180.0 + angel;
	}
	angel1 = angel1*pi / 180;
	
	/*判断是否有箭在飞，如果在飞则不作出动作，如果没有则执行动作*/
	/*根据按下的时间长短给予不同的初速度*/
	if (this->isflying == false)
	{
		arrowSprite->getPhysicsBody()->setGravityEnable(true);

		auto moveBy = MoveBy::create(1.0f, Vec2(0, 0));
		RotateBy* rotateBy;
		if (locationTouch.x>locationArrowSprite.x)
		{
			rotateBy = RotateBy::create(0.1f, 10.0);
		}
		else
		{
			rotateBy = RotateBy::create(0.1f, -10.0);
		}
		if (pressTime >= 0.1 && pressTime <= 0.2)
		{
			arrowSprite->getPhysicsBody()->setVelocity(Vec2(300 * cos(angel1), 300 * sin(angel1)));
		}
		else if (pressTime > 0.2 && pressTime <= 0.3)
		{
			arrowSprite->getPhysicsBody()->setVelocity(Vec2(400 * cos(angel1), 400 * sin(angel1)));
		}
		else if (pressTime > 0.3 && pressTime <= 0.4)
		{
			arrowSprite->getPhysicsBody()->setVelocity(Vec2(500 * cos(angel1), 500 * sin(angel1)));
		}
		else if (pressTime > 0.4 && pressTime <= 0.5)
		{
			arrowSprite->getPhysicsBody()->setVelocity(Vec2(600 * cos(angel1), 600 * sin(angel1)));
		}
		else if (pressTime > 0.6 && pressTime <= 0.7)
		{
			arrowSprite->getPhysicsBody()->setVelocity(Vec2(700 * cos(angel1), 700 * sin(angel1)));
		}
		else if (pressTime > 0.7 && pressTime <= 0.8)
		{
			arrowSprite->getPhysicsBody()->setVelocity(Vec2(800 * cos(angel), 800 * sin(angel)));
		}
		else
		{
			arrowSprite->getPhysicsBody()->setVelocity(Vec2(1000 * cos(angel1), 1000 * sin(angel1)));
		}
		auto repeatforever = RepeatForever::create(rotateBy);
		repeatforever->setTag(1);
		arrowSprite->runAction(moveBy);
		arrowSprite->runAction(repeatforever);
		this->isflying = true;
	}
}

void ArrowSpriteLayer::onTouchCancelled(Touch* touch, Event* event)
{
	return;
}

void ArrowSpriteLayer::setTimeFrequency()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	timeFrequency = (double)frequency.QuadPart;
}

Sprite* ArrowSpriteLayer::getArrowSprite()
{
	return arrowSprite;
}

void ArrowSpriteLayer::changeArrowSpriteReferTo()
{

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (spriteNum <= this->ARROWNUMBER)
	{
		spriteNum++;
	}
	if (spriteNum < this->ARROWNUMBER)
	{
		
		arrowSprite = vecArrowSprite.at(spriteNum);
		auto physicsArrowBody = PhysicsBody::createBox(arrowSprite->getContentSize());
		physicsArrowBody->setGravityEnable(false);
		physicsArrowBody->setCategoryBitmask(1);
		physicsArrowBody->setCollisionBitmask(-1);
		physicsArrowBody->setContactTestBitmask(-1);
		arrowSprite->setPhysicsBody(physicsArrowBody);
		arrowSprite->setVisible(true);
		arrowSprite->setTag(10);
		this->addChild(arrowSprite, 1);
		this->isflying = false;
	}
}

void ArrowSpriteLayer::update(float dt)
{
	/*判断箭是否飞出屏幕，如果飞出则换箭（可以飞出屏幕上方再落回）*/
	Point arrowSpritePosition = arrowSprite->getPosition();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (arrowSpritePosition.x > visibleSize.width || arrowSpritePosition.x < 0 || arrowSpritePosition.y<0 )
	{
		if (spriteNum < this->ARROWNUMBER)
		{
			this->arrowSprite->setVisible(false);
			arrowSprite->removeFromPhysicsWorld();
			changeArrowSpriteReferTo();
		}
	}
	
	/*更新计数图标*/
	if (this->ARROWNUMBER - spriteNum >= 0)
	{
		this->labelArrowNumLeft->removeFromParentAndCleanup(true);
		char num[20];
		sprintf(num, "%d", this->ARROWNUMBER - spriteNum);
		this->labelArrowNumLeft = LabelTTF::create(num, "Brush Script MT", 32);
		labelArrowNumLeft->setColor(Color3B(225, 225, 225));
		labelArrowNumLeft->setPosition(100, visibleSize.height - 25);
		this->addChild(labelArrowNumLeft, 1);
	}
}

void ArrowSpriteLayer::setArrowPosition(TMXObjectGroup* arrowObjectGroup)
{
	ValueMap arrowPointMap = arrowObjectGroup->getObject("Heros");
	float arrowX = arrowPointMap.at("x").asFloat();
	float arrowY = arrowPointMap.at("y").asFloat();
	for (int i = 0; i < this->ARROWNUMBER; i++)
	{
		Sprite* spriteArrow = this->vecArrowSprite.at(i);
		spriteArrow->setPosition(arrowX + 25, arrowY + 50);
	}
}

int ArrowSpriteLayer::getArrowSpriteNumber()
{
	log("aasdfsdfsd   %d", spriteNum);
	return this->ARROWNUMBER - this->spriteNum;
}