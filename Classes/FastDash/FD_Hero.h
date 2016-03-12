#ifndef __FD_HERO_H__
#define __FD_HERO_H__

#include "cocos2d.h"
#include "Entity.h"
#include "FastDash.h"
#include "FD_LabelLayer.h"
USING_NS_CC;

class FD_Hero :public Entity
{
public:
	FD_Hero();
	~FD_Hero();
	virtual bool init();
	CREATE_FUNC(FD_Hero);

	int GetCurrentHP();
	int GetFullHP();
	void SetCurrentHP(int hp);

	void Hurt(int ATK);
	void Move(short x, short y);
	void SkillAnimation();
	void MovingAnimation();
	void HurtingAnimation();
	friend class FastDash;
	friend class FD_LabelLayer;
private:
	int fullHP;
	int currentHP;
	MoveBy* moveAction;
};





#endif