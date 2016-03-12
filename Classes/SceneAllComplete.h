#ifndef _SceneAllComplete_H_
#define _SceneAllComplete_H_
#include"cocos2d.h"
using namespace cocos2d;

class SceneAllComplete :public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	//void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	//void onTouchCancelled(Touch* touch, Event* event);
	void fadeIn();
	void setTouch(float dt);
	void transform();
	CREATE_FUNC(SceneAllComplete);
private:
	Sprite* background;
	Sprite* gate;
	NodeGrid* nodegrid;
	bool touchable=false;
	int tuchnum = 0;
};




#endif