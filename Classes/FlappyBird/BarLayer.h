#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Bar : public Layer
{
public:
    Bar();
    ~Bar();

    virtual bool init();

    void setBarMove(float dt);

    void startBar();

    void stopBar();

    // 移动结束之后的回调函数
    void barMovedOver(Ref *r);

    void barLevelManage();

    virtual void update(float dt);

    CREATE_FUNC(Bar);
private:
    __Array *barArray;
    Vector<Sprite* > barVector;

    Size visibleSize;

    int counter;
    int score;
    int rand;
    bool flag;
    bool flag2;
    int flag3;
    bool flagGameOver;

    float barInterval;

    Sprite* barSprite;
};