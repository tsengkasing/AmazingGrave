#ifndef __FD_MONSTER_H__
#define __FD_MONSTER_H__

#include "cocos2d.h"
#include "Entity.h"
#include "FD_Hero.h"
USING_NS_CC;

class FD_Hero;

class FD_Monster :public Entity
{
public:
	FD_Monster();
	~FD_Monster();
	CREATE_FUNC(FD_Monster);
	virtual bool init();
public:
	FiniteTimeAction* BlowAnimatation(); //爆炸动画

	void SetATK(int atk); //设置攻击力
	int GetATK(); //获取攻击力
	void Show(); //显示怪物
	void Hide(); //隐藏怪物
	void Hide(float x, float y);//按目标位置隐藏
	void Reset(); //重设怪物
	void Reset(float x, float y); //按目标位置重设
	void SetAlive(bool isAlive); //设置存活
	bool IsAlive(); //判断怪物是否存活
	bool IsCollideWithHero(FD_Hero* hero);//判断是否与英雄碰撞
private:
	int ATK; //攻击力
	bool mIsAlive; //存活状态
};



#endif