#ifndef __FD_MONSTERCREATER_H__
#define __FD_MONSTERCREATER_H__

#include "cocos2d.h"
#include "FD_Monster.h"
#include "FD_Hero.h"
USING_NS_CC;

class FD_MonsterCreater : public Node
{
public:
	FD_MonsterCreater();
	~FD_MonsterCreater();
	virtual bool init();
	CREATE_FUNC(FD_MonsterCreater);

	virtual void update(float delta);
public:
	void SetMonsterPic(const std::string &filename);
	void BindHero(FD_Hero* hero);
	void SetShowTime(float time);
	void LetGo(int num, float scale, int atk);
private:
	std::string pic; //π÷ŒÔÕº∆¨
	float currenttime;
	float showtime;
	FD_Hero* pHero;

	Vector<FD_Monster* > monsterArray;
};



#endif