#ifndef __FASTDASH_H__
#define __FASTDASH_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "FD_LabelLayer.h"
#include "FD_Hero.h"
USING_NS_CC;

class FD_Hero;
class FD_LabelLayer;

class FastDash : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FastDash);
public:
	FastDash();

	void update(float delta);
	void AddEffect(); //粒子特效
	void SetViewByHero(); //让视角跟随玩家
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event); //监听键盘按下
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); //监听键盘松开

	void MusicOn(Ref* ref);
	void MusicOff(Ref* ref);
	void initRole();
	void initMusic();
	void Next();
	void Fail();
private:
	FD_LabelLayer* labellayer;

	TMXTiledMap* map; //地图
	Size mapSize;
	FD_Hero* hero; //玩家

	float time; //计时器

	Size visibleSize;
};


#endif