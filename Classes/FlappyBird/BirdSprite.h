#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum ActionState
{
    // 静止状态 0
    ACTION_STATE_IDLE,
    // 飞行状态 1
    ACTION_STATE_FLY,
    // 死亡状态 2
    ACTION_STATE_DIE
};

class BirdSprite : public Layer
{
public:
    static BirdSprite * createBird();

    // 状态转换函数  
    void changeState(ActionState);

    // 转换成空闲状态  
    void stateIdle();

    // 转换成飞行状态  
    void stateFly();

    // 转换成死亡状态
    void stateDie();

    virtual bool init();

    void update(float dt);

    CREATE_FUNC(BirdSprite);
private:
    // 小鸟精灵  
    Sprite *birdSprite;
    // 当前状态  
    ActionState birdState;
    // 侦听对象  
    EventListenerTouchOneByOne *touchListener;
    // 键盘侦听吧
    EventListenerKeyboard *keyBoardListener;
};