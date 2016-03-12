#ifndef __SCENEMCOMPLETE_H__
#define __SCENEMCOMPLETE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;
USING_NS_CC;

class SceneMComplete : public Layer
{
public:
    static Scene* createScene(int Game);
    virtual bool init();
    CREATE_FUNC(SceneMComplete);
public:
    void ShowKey();
    void Next(Ref* ref);
private:
    Size visibleSize;
    SimpleAudioEngine* musicContro;

    int GameScene;

    Sprite* xx;
    Sprite* ss;
    Sprite* zj;
    Menu* keyMenu;
};





#endif