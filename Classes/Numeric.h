#pragma once

#include "cocos2d.h"

USING_NS_CC;

const int BIRD2_ARRIVE = 4;

const int LEVEL_MIN = 0;
const int LEVEL_0 = 6;
const int LEVEL_1 = 10;
const int LEVEL_2 = 16;
const int LEVEL_3 = 22;
const int LEVEL_4 = 30;

class Numeric : public Layer
{
public:
    static Numeric* getInstance();

    void addScore();

    void initScoreZero();

    virtual bool init();

    unsigned int getScore(){ return score; }
private:
    unsigned fails;

    Label* scoreCounterLabel;
    unsigned int score;
};
