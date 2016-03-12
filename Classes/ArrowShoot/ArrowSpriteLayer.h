#ifndef _ArrowSpriteLayer_H_
#define _ArrowSpriteLayer_H_

#define ARROWS_NUM 10


#include"cocos2d.h"
#include "MainScene.h"
#include "MainStep2Scene.h"
#include "MainStep3Scene.h"

using namespace cocos2d;

class MainScene;
class MainStep2Scene;
class MainStep3Scene;

class ArrowSpriteLayer :public Layer
{
public:
	static ArrowSpriteLayer* createArrow();
	bool init();
	/*������������*/
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
	/*������Ƭ��ͼ�����Ϣ��ʼ������λ��*/
	void setArrowPosition(TMXObjectGroup* arrowObjectGroup);
	/*��ȡ��ͷ����*/
	Sprite* getArrowSprite();
	/*�ı��ͷ����ָ��ļ�ͷ*/
	void changeArrowSpriteReferTo();
	/*����ʱ��Ƶ��*/
	void setTimeFrequency();
	void update(float dt);
	/*��ü�ͷ��ʣ�����*/
	int getArrowSpriteNumber();
	CREATE_FUNC(ArrowSpriteLayer);
public:
	bool isflying = false;
	float scores = 0;
	static  int step ;

	MainScene* layer1;
	MainStep2Scene* layer2;
	MainStep3Scene* layer3;
private:
	/*��ͷ����*/
	Sprite* arrowSprite;
	
	int spriteNum = 0;
	
	LabelTTF* labelArrowNumLeft;

	int ARROWNUMBER;

	//�洢ʱ��Ƶ��
	double timeFrequency;
	//�洢�����¼�����ʱ��ʱ��
	double touchBeganTime;
	//�洢�����¼�����ʱ��ʱ��
	double touchEndedTime;
	
	char name[20];
	/*���ڴ�ż�ͷ���������*/
	Vector<Sprite*> vecArrowSprite;
};


#endif