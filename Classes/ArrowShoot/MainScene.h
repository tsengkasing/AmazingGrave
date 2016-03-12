#ifndef _MainScene_H_
#define _MainScene_H_
#define TILE_SIZE 32
#define MAX_SCORES 100

#include"cocos2d.h"
#include<windows.h>
#include"ArrowSpriteLayer.h"
#include"MonsterSprite.h"
#include"MapScene.h"
#include"PauseLayer.h"
#include"WinLayer.h"
#include"FailLayer.h"

using namespace cocos2d;

class PauseLayer;
class MainStep2Scene;
class FailLayer;
class ArrowSpriteLayer;

class MainScene :public Layer
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
	CREATE_FUNC(MainScene);
public:
	bool flagPressed = false;
	bool flagBurning = false;
	float scores = 0;
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