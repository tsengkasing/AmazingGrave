#include "Boss_Bullet.h"

Boss_Bullet::Boss_Bullet()
{
	ATK = 100;
}

bool Boss_Bullet::init()
{
	return true;
}

void Boss_Bullet::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

int Boss_Bullet::GetATK()
{
	return ATK;
}

bool Boss_Bullet::IsCollideWithHero(Boss_Hero* hero)
{
	Rect entityRect = hero->getBoundingBox();

	Point Boss_BulletPos = this->getPosition();

	return entityRect.containsPoint(Boss_BulletPos);
}

bool Boss_Bullet::IsCollideWithBoss(Boss* boss)
{
	Rect entityRect = boss->getBoundingBox();

	Point Boss_BulletPos = this->getPosition();

	return entityRect.containsPoint(Boss_BulletPos);
}

void Boss_Bullet::Play(int num ,int state)
{
	Vector<SpriteFrame *>loadVector;
	char name[14];

	for (int i = 1; i <= num; i++)
	{
		sprintf(name, "bullet_%d%d.png", state, i);
		loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	auto plist = Animation::createWithSpriteFrames(loadVector, 1 / 24.0f);

	auto playplist = Animate::create(plist);

	this->getSprite()->runAction(RepeatForever::create(playplist));

	return;
}