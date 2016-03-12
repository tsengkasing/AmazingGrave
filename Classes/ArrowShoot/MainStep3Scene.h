#ifndef _MainStep3Scene_H_
#define _MainStep3Scene_H_

#include"cocos2d.h"
#include"ArrowSpriteLayer.h"
#include"MonsterSprite.h"
#include"MapScene.h"
#include"PauseLayer.h"
#include"WinLayer.h"
#include"FailLayer.h"

using namespace cocos2d;


class PauseLayer;
class FailLayer;
class MainStep2Scene;
class ArrowSpriteLayer;

class MainStep3Scene :public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	void update(float dt);
	void judge(float dt);
	void Pause();
	void setBurning(float dt);
	void deleteBurning(float dt);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(MainStep3Scene);
public:
	bool flagPressed = false;
	bool flagBurning = false;
	float scores = 0;
	static float Scores;
public:
	ArrowSpriteLayer * arrow;//¼ýÍ·¾«Áé²ã
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