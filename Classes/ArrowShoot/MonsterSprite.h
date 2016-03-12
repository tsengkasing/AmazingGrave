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
	/*���ﱻ���м��ٹ������*/
	void monsterNumberDecrease();
	/*������Ƭ��ͼ����Ϣ���ù���λ��*/
	void setMonstersPosition(TMXObjectGroup* monsterObjectGroup);
	/*��ù���ʣ�����*/
	int getMonsterNumber();
	void update(float dt);
	CREATE_FUNC(MonsterSprite);
public:
	static int step;
private:
	int monsterNumber = 4;
	char name[20];
	LabelTTF* labelMonsterNumLeft;
	/*��Ź��ﾫ�������*/
	Vector<Sprite*>vecMonsterSprite;

};

#endif