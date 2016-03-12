#ifndef __LABELLAYER_H__
#define __LABELLAYER_H__

#include "cocos2d.h"
#include "Boss_Hero.h" 
#include "FinalWar.h"
#include "Boss.h"
USING_NS_CC;

class Boss_Hero;
class FinalWar;

class Boss_LabelLayer : public Layer
{
public:
	virtual bool init();
	void pauseScene();
	void resumeScene();
	CREATE_FUNC(Boss_LabelLayer);
public:
	FinalWar* gamerlayer;

	void End();
	void SetScore(float grade);
	float GetScore();

	void update(float delta);

	void MusicOn(Ref* ref);
	void MusicOff(Ref* ref);
	void initMusic();

	void BindHero(Boss_Hero* phero);
	void BindBoss(Boss* pboss);
private:
	Size visibleSize;

	MenuItemImage* musicOnLabel;
	MenuItemImage* musicOffLabel;
	Menu* musicMenu;

	Boss_Hero* hero;
	Boss* boss;

	float score; //·ÖÊý

	//ÑªÁ¿
	ProgressTimer* hpBarblood_H;
	Sprite* hpBar_H;

	ProgressTimer* hpBarblood_B;
	Sprite* hpBar_B;

	void CreateHPLabel();

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