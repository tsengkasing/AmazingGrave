#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Ground : public Layer
{
public:
    virtual bool init();

    void MoveGround(float dt);

    void StartGround();

    void StopGround();

    CREATE_FUNC(Ground);
private:
    Sprite *ground1;
    Sprite *ground2;
    Sprite *skulls;
};