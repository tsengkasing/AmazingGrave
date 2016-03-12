#ifndef __FD_BULLETCREATER_H__
#define __FD_BULLETCREATER_H__

#include "cocos2d.h"
#include "FD_Monster.h"
#include "FD_Hero.h"
USING_NS_CC;

class MonsterCreater;
class FD_Hero;
class FD_Monster;

class FD_BulletCreater : public Node
{
public:
	FD_BulletCreater();
	~FD_BulletCreater();
	virtual bool init();
	CREATE_FUNC(FD_BulletCreater);

	virtual void update(float delta);
public:
	void LetGo(int num);
	void BindHero(FD_Hero* hero);
	void BindBoss(FD_Monster* boss);
private:
	Size visibleSize;
	FD_Hero* pHero;
	FD_Monster* pBoss;

	int count; //怪物计数
	int monsterNum; //怪物数量
	Vector<FD_Monster* > monsterArray;
};



#endif