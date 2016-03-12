#ifndef _FailLayer_H_
#define _FailLayer_H_

#include"MainScene.h"
#include"MainStep2Scene.h"
#include"MainStep3Scene.h"
#include"cocos2d.h"
using namespace cocos2d;

class MainScene;
class MainStep2Scene;
class MainStep3Scene;

class FailLayer :public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	void menuAgainCallBack(cocos2d::Ref* pSender);
	void menuMenuCallBack(cocos2d::Ref* pSender);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(FailLayer);
public:
	MainScene* mainPlayLayer = NULL;
	MainStep2Scene* mainStep2Layer = NULL;
	MainStep3Scene* mainStep3Layer = NULL;
private:
	Sprite* background;
};



#endif