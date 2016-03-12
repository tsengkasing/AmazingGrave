#ifndef __FD_BOSSSCENE_H__
#define __FD_BOSSSCENE_H__

#include "cocos2d.h"
#include "FD_LabelLayer.h"
#include "FD_Monster.h"
#include "FD_Hero.h"
#include "FD_BulletCreater.h"
USING_NS_CC;

class FD_Hero;
class FD_Monster;
class FD_BulletCreater;
class FD_LabelLayer;

class FD_BossScene : public Layer
{
public:
	FD_BossScene();

	static Scene* createScene(int hp);
	virtual bool init();
	CREATE_FUNC(FD_BossScene);
public:
	void update(float delta);

	void Win(float delta);
	void Fail();
	void End();
	void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
private:
	bool bomb;
	FD_Hero* Bomb;

	bool leftright;
	bool updown;
	FD_Hero* hero;
	FD_Monster* boss;
	FD_BulletCreater* bullet;
	float time;
	void Attack(float delta);

	Size visibleSize;
	FD_LabelLayer* labellayer;
};





#endif