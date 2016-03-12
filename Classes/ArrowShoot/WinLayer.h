#ifndef _WinLayer_H_
#define _WinLayer_H_
#include"cocos2d.h"



using namespace cocos2d;

class WinLayer :public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	void menuAgainCallBack(cocos2d::Ref* pSender);
	//void menuNextCallBack(cocos2d::Ref* pSender);
	void menuMenuCallBack(cocos2d::Ref* pSender);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(WinLayer);
private:
	Sprite* background;

};




#endif