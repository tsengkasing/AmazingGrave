#ifndef __FD_LABELLAYER_H__
#define __FD_LABELLAYER_H__

#include "cocos2d.h"
#include "FD_Hero.h" 
USING_NS_CC;

class FD_Hero;

class FD_LabelLayer : public Layer
{
public:
	void pauseScene();
	void resumeScene();
	virtual bool init();
	CREATE_FUNC(FD_LabelLayer);
public:
	void update(float delta);

	void BindHero(FD_Hero* phero);
private:
	Size visibleSize;

	FD_Hero* hero;

	ProgressTimer* hpBarblood;
	Sprite* hpBar;

	void CreateHPLabel();

	//ÔÝÍ£²ã
	bool flagPause;
	bool flagResume;
	bool flagMusic;

	Sprite* pauseMainUI;
	Sprite* pauseBackground;

	MenuItemSprite* resume;
	MenuItemSprite* music;
	MenuItemSprite* newGame;
	Menu* menu;
	EventListenerKeyboard* pauseListener;
};




#endif