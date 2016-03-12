#ifndef _MapScene_H_
#define _MapScene_H_
#include"cocos2d.h"
using namespace cocos2d;

class MapScene :public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	/*������Ƭ��ͼ*/
	TMXTiledMap* getMap();
	CREATE_FUNC(MapScene);
public:
	static int step;
public:
	/*������Ƭ��ͼ�еĶ����*/
	TMXObjectGroup* getObjectGroup();
private:
	TMXObjectGroup* objGroup;
	TMXTiledMap* map;
};



#endif