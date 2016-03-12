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
	FiniteTimeAction* BlowAnimatation(); //��ը����

	void SetATK(int atk); //���ù�����
	int GetATK(); //��ȡ������
	void Show(); //��ʾ����
	void Hide(); //���ع���
	void Hide(float x, float y);//��Ŀ��λ������
	void Reset(); //�������
	void Reset(float x, float y); //��Ŀ��λ������
	void SetAlive(bool isAlive); //���ô��
	bool IsAlive(); //�жϹ����Ƿ���
	bool IsCollideWithHero(FD_Hero* hero);//�ж��Ƿ���Ӣ����ײ
private:
	int ATK; //������
	bool mIsAlive; //���״̬
};



#endif