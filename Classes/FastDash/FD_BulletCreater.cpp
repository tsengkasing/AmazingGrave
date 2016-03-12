#include "FD_BulletCreater.h"
#define Bullet_ATK 50

FD_BulletCreater::FD_BulletCreater()
{
	monsterNum = 0;
	count = 0;
}

FD_BulletCreater::~FD_BulletCreater()
{
}

bool FD_BulletCreater::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	this->scheduleUpdate(); //开启update函数
	return true;
}

void FD_BulletCreater::update(float delta)
{
	if (monsterArray.empty())
	{
		return;
	}

	count = 0;
	cocos2d::Vector<FD_Monster*>::iterator monster = monsterArray.begin();
	while (monster != monsterArray.end())
	{
		(*monster)->setPositionX((*monster)->getPositionX() -  3 - count % 6);
		
		if (monsterNum > 18)
		{
			if (count % 2 == 0)
			{
			(*monster)->setPositionY((*monster)->getPositionY() + 2 + count % 5);
			}
			else
			{
			(*monster)->setPositionY((*monster)->getPositionY() - 2 - count % 5);
			}
		}
		count++;

		if ((*monster)->getPositionX() < 0)
		{
			(*monster)->removeFromParentAndCleanup(true);
			monster = monsterArray.erase(monster);
			monsterNum--;
		}
		else if ((*monster)->IsCollideWithHero(pHero))
		{
			pHero->Hurt((*monster)->GetATK());
			(*monster)->removeFromParentAndCleanup(true);
			monster = monsterArray.erase(monster);
			monsterNum--;
		}
		else
		{
			monster++;
		}
	}
	return;
}

void FD_BulletCreater::BindHero(FD_Hero* hero)
{
	pHero = hero;
	return;
}

void FD_BulletCreater::BindBoss(FD_Monster* boss)
{
	pBoss = boss;
	return;
}

void FD_BulletCreater::LetGo(int num)
{
	FD_Monster* monster = NULL;

	monsterNum += num;

	for (int i = 0; i < num; i++)
	{
		//创建怪物
		monster = FD_Monster::create();
		monster->BindSprite(Sprite::createWithSpriteFrameName("F_bullet.png"));
		monster->setScale(0.6f);
		monster->SetAlive(true);
		monster->SetATK(Bullet_ATK);
		monster->Reset(pBoss->getPositionX(), pBoss->getPositionY() + 60 * (2 * i + 1 - num));
		this->addChild(monster);

		monsterArray.pushBack(monster);
	}
	return;
}