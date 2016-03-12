#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GraveMainScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GraveMainScene);

    // 小火龙摔下来的动画
    void huoLongFallAction(float dt);

    void createBlankCelling();

    virtual void update(float);

private:
    Sprite* backGround;
    Sprite* huoLongFall;
    Sprite* huoLongFallOver;
    Sprite* xxOutOfGrave;
    Sprite* ssOutOfGrave;
    Sprite* zjOutOfGraveInnocent;
    Sprite* zjOutOfGraveEvilNoWing;
    Sprite* zjOutOfGraveEvilWithWing;
    Sprite* zjGravebox;
    Sprite* xxGravebox;
    Sprite* ssGravebox;
    Sprite* light;
    Sprite* celling;
    LayerColor* black;

    EventListenerTouchOneByOne* zjListener;
    EventListenerTouchOneByOne* ssListener;
    EventListenerTouchOneByOne* xxListener;

    float scale;
    bool zjVisible;

    bool flagss;
    bool flagxx;
    bool flagzj;
    bool flagGame3;
    bool flagFinalGame;
    bool flagSSGame;

    Size visibleSize;
};