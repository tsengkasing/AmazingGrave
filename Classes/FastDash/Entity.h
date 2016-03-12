#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
USING_NS_CC;


class Entity :public Node
{
public:
	void BindSprite(Sprite* sprite); //绑定精灵
	Sprite* getSprite(); //获取绑定的精灵
private:
	Sprite* pSprite; //精灵
};


#endif