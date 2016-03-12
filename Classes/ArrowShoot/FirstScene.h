#ifndef _FirstScene_H_
#define _FirstScene_H_
#include"cocos2d.h"
using namespace cocos2d;

class FirstScene :public Layer{
public:
	static  Scene* CreateScene();
	virtual bool init();
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(FirstScene);
};

#endif