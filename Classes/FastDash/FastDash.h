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
	void AddEffect(); //������Ч
	void SetViewByHero(); //���ӽǸ������
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event); //�������̰���
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); //���������ɿ�

	void MusicOn(Ref* ref);
	void MusicOff(Ref* ref);
	void initRole();
	void initMusic();
	void Next();
	void Fail();
private:
	FD_LabelLayer* labellayer;

	TMXTiledMap* map; //��ͼ
	Size mapSize;
	FD_Hero* hero; //���

	float time; //��ʱ��

	Size visibleSize;
};


#endif