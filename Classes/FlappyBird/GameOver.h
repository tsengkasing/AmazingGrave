#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public Layer
{
public:
    virtual bool init();

    void playAgain();

    void nextScene();

    void showScore(float dt);

    CREATE_FUNC(GameOverLayer);

    void funcCallBack();

    void backToMenu();

private:
    Sprite* scoreRect;
    Label* scoreLabel;
    unsigned displayScore;
    Size visibleSize;
};