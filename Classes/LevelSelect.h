#ifndef __LEVELSELECT_H__
#define __LEVELSELECT_H__

#include "cocos2d.h"
USING_NS_CC;

class LevelSelect : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelSelect);
public:
	void update(float delta);
private:
	Layer* level;
};




#endif