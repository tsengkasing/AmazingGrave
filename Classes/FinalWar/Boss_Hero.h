#ifndef __Boss_Hero_H__
#define __Boss_Hero_H__

#include "Entity.h"
#include "Boss.h"
#include "Boss_Bullet.h"
#include "Boss_Monster.h"
USING_NS_CC;

class Boss_Monster;

class Boss_Hero :public Entity
{
public:
	Boss_Hero();
	~Boss_Hero();
	virtual bool init();
	CREATE_FUNC(Boss_Hero);

	void BindBoss(Boss* boss);
	int GetCurrentHP();
	int GetFullHP();
	void SetCurrentHP(int hp);
	void SetPower(int atk); //设置英雄攻击力
	void SetMonsterArray(Vector<Boss_Monster* >* Array); //获得小怪数组

	void Attack(float scale);
	void Hurt(int ATK);
	void Move(short x, short y);

	void SetBullet(int num, int state); //设置子弹动画源文件 动画帧数 子弹种类
	void HurtingAnimation(int atk); //受伤动画

	void update(float delta);
private:
	int fullHP;
	int currentHP;
	int power;

	Boss* pBoss;
	MoveBy* moveAction;
	int plistNum;
	int bulletState;
	bool bulletLife; //子弹是否存活

	Vector<Boss_Bullet* > bulletArray; //子弹数组
	Vector<Boss_Monster* >* monsterArray; //小怪数组
};





#endif