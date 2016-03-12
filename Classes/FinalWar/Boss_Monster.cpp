#include "Boss_Monster.h"

Boss_Monster::Boss_Monster()
{
	atk = 50;
	hp = 100;
}

Boss_Monster::~Boss_Monster()
{
}

bool Boss_Monster::init()
{
	return true;
}

void Boss_Monster::SetATK(int atk)
{
	this->atk = atk;
}

int Boss_Monster::GetATK()
{
	return this->atk;
}

void Boss_Monster::SetHP(int HP)
{
	this->hp = HP;
	return;
}

int Boss_Monster::GetHP()
{
	return this->hp;
}

void Boss_Monster::LoseLife(int atk)
{
	this->hp -= atk;
	if (hp < 0)
	{
		hp = 0;
	}

	//ÉËº¦Êä³ö·´À¡
	LabelTTF* hurt = LabelTTF::create(String::createWithFormat("Hit %d", atk)->getCString(), "arial", 36);
	hurt->setColor(Color3B(255, 0, 0));
	hurt->setPosition(this->getPositionX() + 50, this->getPositionY());

	auto act = Sequence::create(Blink::create(0.8f, 1),
		CallFunc::create(([hurt](void){
		hurt->setVisible(false);
		hurt->removeFromParentAndCleanup(true);
	})), nullptr);

	this->getParent()->addChild(hurt);
	hurt->runAction(act);

	return;
}

bool Boss_Monster::IsCollideWithHero(Boss_Hero* phero)
{
	Rect entityRect = phero->getBoundingBox();

	Point Boss_MonsterPos = this->getPosition();

	return entityRect.containsPoint(Boss_MonsterPos);
}