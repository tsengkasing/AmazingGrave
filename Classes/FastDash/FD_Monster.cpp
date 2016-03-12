#include "FD_Monster.h"

FD_Monster::FD_Monster()
{
	ATK = 100;
	mIsAlive = false;
}

FD_Monster::~FD_Monster()
{
}

bool FD_Monster::init()
{
	return true;
}

FiniteTimeAction* FD_Monster::BlowAnimatation()
{
	Vector<SpriteFrame *>loadVector;
	char name[15];

	for (int i = 1; i <= 7; i++)
	{
		sprintf(name, "F_Light%d.png", i);
		loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	FiniteTimeAction* Blow = Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 12.0f));

	return Blow;
}

void FD_Monster::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

int FD_Monster::GetATK()
{
	return this->ATK;
}

void FD_Monster::Show()
{
	if (getSprite() != NULL)
	{
		this->setVisible(true);
		mIsAlive = true;
	}
	return;
}

void FD_Monster::Hide()
{
	if (getSprite() != NULL)
	{
		this->setVisible(false);
		this->Reset();
		mIsAlive = false;
	}
	return;
}

void FD_Monster::Reset()
{
	if (getSprite() != NULL)
	{
		setPosition(Point(800 + CCRANDOM_0_1() * 21000, CCRANDOM_0_1() * 600));
	}
	return;
}

void FD_Monster::Reset(float x, float y)
{
	this->setPosition(x, y);
	return;
}

void FD_Monster::SetAlive(bool isAlive)
{
	this->mIsAlive = isAlive;
	return;
}

bool FD_Monster::IsAlive()
{
	return mIsAlive;
}

bool FD_Monster::IsCollideWithHero(FD_Hero* hero)
{
	Rect entityRect = hero->getBoundingBox();

	Point monsterPos = this->getPosition();

	return entityRect.containsPoint(monsterPos);
}