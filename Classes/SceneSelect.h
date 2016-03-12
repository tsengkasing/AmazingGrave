#ifndef _SceneSelect_H_
#define _SceneSelect_H_
#include"cocos2d.h"
using namespace cocos2d;

class SceneSelect :public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	void menuSelectOneCallBack(cocos2d::Ref* pSender);
	void menuSelectTwoCallBack(cocos2d::Ref* pSender);
	void menuSelectThreeCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(SceneSelect);
};




#endif 