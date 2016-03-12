#ifndef _MainStep2Scene_H_
#define _MainStep2Scene_H_



#include"cocos2d.h"
#include<windows.h>
#include"ArrowSpriteLayer.h"
#include"MonsterSprite.h"
#include"MapScene.h"
#include"PauseLayer.h"
#include"WinLayer.h"
#include"FailLayer.h"

#define MAX_SCORES 100

using namespace cocos2d;

class MainScene;
class PauseLayer;
class FailLayer;
class ArrowSpriteLayer;

class MainStep2Scene :public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	void menuExitCallBack(cocos2d::Ref* pSender);
	void Pause();
	void update(float dt);
	void judge(float dt);
	CREATE_FUNC(MainStep2Scene);
public:
	bool flagPressed = false;
	static float Scores;
	float scores = 0;
public:
	ArrowSpriteLayer* arrow;//¼ýÍ·¾«Áé²ã
	MonsterSprite* monster;//¹ÖÎï¾«Áé²ã
	MapScene* map;//ÍßÆ¬µØÍ¼²ã
private:
	int arrowleft = 0;
	
	Sprite* musicon;
	Sprite* myHero;
	Sprite* arch;
	PauseLayer* pauselayer;
	WinLayer* winlayer;
	FailLayer* faillayer;
	ParticleBatchNode* burningbatch;

	Vec2 speed;
	friend class ArrowSpriteLayer;
public:
	Vec2 getSpeed();
};




#endif