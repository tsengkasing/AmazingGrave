#ifndef _MonsterSprite_H_
#define _MonsterSprite_H_
#define MONSTERS_NUM 4

#include"cocos2d.h"
using namespace cocos2d;

class MonsterSprite :public Layer
{
public:
	static MonsterSprite* createMonster();
	bool init();
	/*怪物被射中减少怪物个数*/
	void monsterNumberDecrease();
	/*根据瓦片地图的信息设置怪物位置*/
	void setMonstersPosition(TMXObjectGroup* monsterObjectGroup);
	/*获得怪物剩余个数*/
	int getMonsterNumber();
	void update(float dt);
	CREATE_FUNC(MonsterSprite);
public:
	static int step;
private:
	int monsterNumber = 4;
	char name[20];
	LabelTTF* labelMonsterNumLeft;
	/*存放怪物精灵的容器*/
	Vector<Sprite*>vecMonsterSprite;

};

#endif