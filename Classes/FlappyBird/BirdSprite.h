#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum ActionState
{
    // ��ֹ״̬ 0
    ACTION_STATE_IDLE,
    // ����״̬ 1
    ACTION_STATE_FLY,
    // ����״̬ 2
    ACTION_STATE_DIE
};

class BirdSprite : public Layer
{
public:
    static BirdSprite * createBird();

    // ״̬ת������  
    void changeState(ActionState);

    // ת���ɿ���״̬  
    void stateIdle();

    // ת���ɷ���״̬  
    void stateFly();

    // ת��������״̬
    void stateDie();

    virtual bool init();

    void update(float dt);

    CREATE_FUNC(BirdSprite);
private:
    // С����  
    Sprite *birdSprite;
    // ��ǰ״̬  
    ActionState birdState;
    // ��������  
    EventListenerTouchOneByOne *touchListener;
    // ����������
    EventListenerKeyboard *keyBoardListener;
};