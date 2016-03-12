#include"MonsterSprite.h"
#include"MapScene.h"

int MonsterSprite::step = 1;

float timerand(int i)
{
	float x = i;
	float rand =  0.1*(x-4)*(x-3)+0.2*(x-2)*(x-1);
	return rand;
}




MonsterSprite *MonsterSprite::createMonster()
{
	auto monster = MonsterSprite::create();

	return monster;
}

bool MonsterSprite::init()
{
	if (!Layer::create())
	{
		return false;
	}

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	
	/*将怪物精灵装进容器*/
	for (int i = 1; i <= MONSTERS_NUM; i++)
	{
		sprintf(name, "zombie%d.png", i);
		Sprite* monsterSprite = Sprite::createWithSpriteFrameName(name);
		monsterSprite->setTag(5);

		auto physicsMonsterBody = PhysicsBody::createBox(monsterSprite->getContentSize());
		physicsMonsterBody->setGravityEnable(false);
		
		physicsMonsterBody->setCategoryBitmask(1);
		physicsMonsterBody->setCollisionBitmask(-1);
		physicsMonsterBody->setContactTestBitmask(-1);

		monsterSprite->setPhysicsBody(physicsMonsterBody);
		if (this->step == 2)
		{
			auto moveBy1 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
			auto moveBy2 = MoveBy::create(1.5*timerand(i), Vec2(-128, monsterSprite->getPositionY()));
			auto moveBy3 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
			auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, NULL);
			monsterSprite->runAction(RepeatForever::create(moveSeq));
		}
		if (this->step == 3)
		{
			switch (i)
			{
			case 1:{
					   auto moveBy1 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), 16));
					   auto moveBy2 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), 16));
					   auto moveBy3 = MoveBy::create(0.5, Vec2(monsterSprite->getPositionX(), 32));
					   auto moveBy4 = MoveBy::create(0.5, Vec2(monsterSprite->getPositionX(), -32));
					   auto moveBy5 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), -16));
					   auto moveBy6 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), -16));
					   auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, moveBy4, moveBy5, moveBy6, NULL);
					   monsterSprite->runAction(RepeatForever::create(moveSeq));
			}break;
			case 2:{
					   auto moveBy1 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					   auto moveBy2 = MoveBy::create(1.5*timerand(i), Vec2(-128, monsterSprite->getPositionY()));
					   auto moveBy3 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					   auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, NULL);
					   monsterSprite->runAction(RepeatForever::create(moveSeq));
			}break;
			case 3:{
					   auto moveBy1 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					   auto moveBy2 = MoveBy::create(1.5*timerand(i), Vec2(-128, monsterSprite->getPositionY()));
					   auto moveBy3 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					   auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, NULL);
					   monsterSprite->runAction(RepeatForever::create(moveSeq));
			}break;
			case 4:{
					   auto moveBy1 = MoveBy::create(0.05, Vec2(monsterSprite->getPositionX(), 16));
					   auto moveBy2 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), 16));
					   auto moveBy3 = MoveBy::create(0.2, Vec2(monsterSprite->getPositionX(), 32));
					   auto moveBy4 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), 64));
					   auto moveBy5 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), -64));
					   auto moveBy6 = MoveBy::create(0.5, Vec2(monsterSprite->getPositionX(), -32));
					   auto moveBy7 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), -16));
					   auto moveBy8 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), -16));
					   auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, moveBy4, moveBy5, moveBy6,moveBy7,moveBy8, NULL);
					   monsterSprite->runAction(RepeatForever::create(moveSeq));
			}
			default:
				break;
			}
		}





		monsterSprite->setPosition(visibleSize.width*i / 10, visibleSize.height*i / 10);

		this->addChild(monsterSprite);
		
		this->vecMonsterSprite.pushBack(monsterSprite);
	}
	/*设置怪物计数图标*/
	Sprite* monsterIcon = Sprite::createWithSpriteFrameName("icon.png");
	monsterIcon->setPosition(visibleSize.width - 100, visibleSize.height - 25);
	this->addChild(monsterIcon, 1);

	this->labelMonsterNumLeft = LabelTTF::create("4", "Brush Script MT", 32);
	labelMonsterNumLeft->setColor(Color3B(225, 225, 225));
	labelMonsterNumLeft->setPosition(visibleSize.width - 25, visibleSize.height - 25);
	this->addChild(labelMonsterNumLeft, 1);

	scheduleUpdate();
	return true;
}


void MonsterSprite::monsterNumberDecrease()
{
	 monsterNumber--;
}

void MonsterSprite::setMonstersPosition(TMXObjectGroup* monsterObjectGroup)
{
	char monstername[20];
	for (int i = 0; i < MONSTERS_NUM; i++){
		Sprite* monsterSprite = this->vecMonsterSprite.at(i);
		sprintf(monstername, "Monster%d", i+1);
		ValueMap monsterPointMap = monsterObjectGroup->getObject(monstername);
		float monsterX = monsterPointMap.at("x").asFloat();
		float monsterY = monsterPointMap.at("y").asFloat();
		
		monsterSprite->setPosition(monsterX+25 , monsterY+25 );
	}
}
int MonsterSprite::getMonsterNumber()
{
	return monsterNumber;
}

void MonsterSprite::update(float dt)
{
	/*更新怪物计数图标*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->labelMonsterNumLeft->removeFromParentAndCleanup(true);
	char num[20];
	sprintf(num, "%d", monsterNumber);
	this->labelMonsterNumLeft = LabelTTF::create(num, "Brush Script MT", 32);
	labelMonsterNumLeft->setColor(Color3B(225, 225, 225));
	labelMonsterNumLeft->setPosition(visibleSize.width - 25, visibleSize.height - 25);
	this->addChild(labelMonsterNumLeft, 1);
}