#ifndef __SCENEINTRO_H__
#define __SCENEINTRO_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneIntro :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SceneIntro);
public:
	void update(float delta);
	void Next(Ref* ref);
private:
	Size visibleSize;
	Sprite* curtain; //Ä»²¼1
	Sprite* curtainFollow; //Ä»²¼2
};




#endif