#ifndef __Boss_BULLET_H__
#define __Boss_BULLET_H__

#include "Entity.h"
#include "Boss_Hero.h"
#include "Boss.h"

class Boss;
class Boss_Hero;

class Boss_Bullet : public Entity
{
public:
	Boss_Bullet();
	CREATE_FUNC(Boss_Bullet);
	virtual bool init();
public:
	void Play(int num, int state);
	void SetATK(int atk); //设置攻击力
	int GetATK(); //获取攻击力

	bool IsCollideWithHero(Boss_Hero* hero);//判断是否与英雄碰撞
	bool IsCollideWithBoss(Boss* boss);//判断是否与英雄碰撞
private:
	int ATK; //攻击力
};





#endif