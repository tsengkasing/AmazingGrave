#ifndef _MapScene_H_
#define _MapScene_H_
#include"cocos2d.h"
using namespace cocos2d;

class MapScene :public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	/*返回瓦片地图*/
	TMXTiledMap* getMap();
	CREATE_FUNC(MapScene);
public:
	static int step;
public:
	/*返回瓦片地图中的对象层*/
	TMXObjectGroup* getObjectGroup();
private:
	TMXObjectGroup* objGroup;
	TMXTiledMap* map;
};



#endif