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
	/*触摸监听函数*/
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
	/*根据瓦片地图里的信息初始化箭的位置*/
	void setArrowPosition(TMXObjectGroup* arrowObjectGroup);
	/*获取箭头精灵*/
	Sprite* getArrowSprite();
	/*改变箭头精灵指向的箭头*/
	void changeArrowSpriteReferTo();
	/*设置时针频率*/
	void setTimeFrequency();
	void update(float dt);
	/*获得箭头的剩余个数*/
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
	/*箭头精灵*/
	Sprite* arrowSprite;
	
	int spriteNum = 0;
	
	LabelTTF* labelArrowNumLeft;

	int ARROWNUMBER;

	//存储时针频率
	double timeFrequency;
	//存储触摸事件发生时的时间
	double touchBeganTime;
	//存储触摸事件结束时的时间
	double touchEndedTime;
	
	char name[20];
	/*用于存放箭头精灵的容器*/
	Vector<Sprite*> vecArrowSprite;
};


#endif