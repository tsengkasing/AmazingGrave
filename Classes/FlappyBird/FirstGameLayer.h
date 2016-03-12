#pragma once

#include "cocos2d.h"
#include "BirdSprite.h"

USING_NS_CC;

class FirstGameLayer : public Layer
{
public:
    static Scene *createScene();
    
    virtual bool init();

    void stopGround();

    void pauseScene();

    void resumeScene();

    CREATE_FUNC(FirstGameLayer);

    virtual void update(float dt);

    void godMode(float dt);

    void addCountDown();
private:
    bool flag;
    bool flagPause;
    bool flagResume;
    bool flagMusic;
    bool initBird2;

    unsigned count;

    BirdSprite* bird;
    BirdSprite* bird2;
    Sprite* bg;
    Sprite* spark;
    Sprite* pauseMainUI;

    Vec2 velocityXingxing;
    Vec2 velocityHuolong;

    Size visibleSize;

    __String* str;

    MenuItemSprite* resume;
    MenuItemSprite* music;
    MenuItemSprite* newGame;
    Menu* menu;
    EventListenerKeyboard* pauseListener;
    EventListenerKeyboard* keyListener;
};