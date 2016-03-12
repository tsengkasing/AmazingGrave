#ifndef __BOSS_H__
#define __BOSS_H__

#include "Entity.h"
#include "Boss_Hero.h"
#include "Boss_Bullet.h"
USING_NS_CC;

class Boss_Bullet;
class Boss_Hero;

class Boss : public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(Boss);
public:
	Boss();

	void BindHero(Boss_Hero* phero);

	int GetCurrentHP();
	int GetFullHP();
	void SetSkill(const std::string &filename);

	void Hurt(int atk, int bulletState);

	void Attack(int num, float scale, int atk);

	void HurtingAnimation(int atk, int bulletState);

	void Aim(float delta);
	void update(float delta);
private:
	Size visibleSize;
	float time;
	bool flag;

	Boss_Hero* hero;

	std::string monster;
	std::string skill;
	int currentHP;
	int fullHP;

	int count; //×Óµ¯¼ÆÊý
	Vector<Boss_Bullet* > bulletArray;
};





#endif