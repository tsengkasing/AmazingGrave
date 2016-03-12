#include "FD_Hero.h"
#include "FastDash.h"
#include "FlowWord.h"

FD_Hero::FD_Hero()
{
	fullHP = 2000;
	currentHP = fullHP;
}

FD_Hero::~FD_Hero()
{
}

bool FD_Hero::init()
{
	return true;
}

int FD_Hero::GetCurrentHP()
{
	return currentHP;
}

int FD_Hero::GetFullHP()
{
	return fullHP;
}

void FD_Hero::SetCurrentHP(int hp)
{
	this->currentHP = hp;
	return;
}

void FD_Hero::Move(short x, short y)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (this->getPositionY() >= visibleSize.height && y > 0)
	{
		return;
	}
	else if (this->getPositionY() <= 0 && y < 0)
	{
		return;
	}

	moveAction = MoveBy::create(0.3f, Vec2(15 * x, y * 15));
	this->runAction(RepeatForever::create(moveAction));

	return;
}

void FD_Hero::SkillAnimation()
{
	Vector<SpriteFrame *>loadVector;
	char name[21];

	for (int i = 1; i <= 11; i++)
	{
		sprintf(name, "F_MagicCircle%d.png", i);
		loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	FiniteTimeAction* skillAnimate = Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 12.0f));

	auto sprite = Sprite::create();
	sprite->setScale(12.0f);
	sprite->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(sprite);

	sprite->runAction(Sequence::create(skillAnimate,
		CallFunc::create([sprite](void){
		sprite->removeFromParentAndCleanup(true);
	}), nullptr));

	return;
}

void FD_Hero::MovingAnimation()
{
	Vector<SpriteFrame *>loadVector;
	char name[26];

	for (int i = 1; i <= 2; i++)
	{
		sprintf(name, "F_LittleStar-walk_%d.png", i);
		loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	Animate* movingAnimate = Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 4.0f));

	this->getSprite()->runAction(RepeatForever::create(movingAnimate));

	return;
}

void FD_Hero::HurtingAnimation()
{
	Vector<SpriteFrame *>loadVector;

	loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("F_LittleStar.png"));
	loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("F_LittleStar-hurt.png"));

	Animate* hurtingAnimate = Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 8.0f));

	this->getSprite()->runAction(hurtingAnimate);

	return;
}

void FD_Hero::Hurt(int ATK)
{
	if (getSprite() == NULL)
	{
		return;
	}

	auto flowword = FlowWord::create();
	this->addChild(flowword);

	if (ATK > 0)
	{
		flowword->ShowWord(false, ATK, 1.8f, 3, Vec2(100, 950), Color3B(0xFF, 0, 0));
		this->HurtingAnimation();
	}
	else
	{
		flowword->ShowWord(true, 100, 1.8f, 3, Vec2(100, 450), Color3B(0, 0xFF, 0));
		this->SkillAnimation();
	}

	currentHP -= ATK;
	if (currentHP < 0)
	{
		currentHP = 0;
	}
	if (currentHP > fullHP)
	{
		currentHP = fullHP;
	}

	return;
}
