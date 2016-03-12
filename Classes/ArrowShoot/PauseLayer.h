#ifndef _PauseLayer_H_
#define _PauseLayer_H_

#include"cocos2d.h"
#include"MainScene.h"
#include"MainStep2Scene.h"
#include"MainStep3Scene.h"
using namespace cocos2d;

class MainScene;
class MainStep2Scene;
class MainStep3Scene;

class PauseLayer :public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	void menuAgainCallBack(cocos2d::Ref* pSender);
    void menuNextCallBack(cocos2d::Ref* pSender);
	void menuResumeCallBack(cocos2d::Ref* pSender);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(PauseLayer);
public:
	static int step;
private:
	Sprite* background;
    bool flagMusic;

public:
	MainScene* mainPlayLayer = NULL;
	MainStep2Scene* mainStep2Layer = NULL;
	MainStep3Scene* mainStep3Layer = NULL;
	

};


#endif