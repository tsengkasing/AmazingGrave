#include "Numeric.h"

// 单例赋初值NULL
static Numeric* number = NULL;

Numeric* Numeric::getInstance()
{
    // 如果此单例不存在就创造一个
    if (!number)
    {
        number = new Numeric;
        
        // 初始化之
        number->init();
    }
    // 如果已经存在，就直接返回
    return number;
}

bool Numeric::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    score = 0;

    auto str = __String::createWithFormat("%d", score);

    scoreCounterLabel = Label::createWithBMFont("/fonts/score.fnt", str->getCString());
    scoreCounterLabel->setPosition(Vec2(visibleSize.width / 2, 550));
    addChild(scoreCounterLabel);

    return true;
}

void Numeric::initScoreZero()
{
    score = 0;
    auto str = __String::createWithFormat("%d", score);
    scoreCounterLabel->setString(str->getCString());
}

void Numeric::addScore()
{
    score++;
    auto str = __String::createWithFormat("%d", score);
    scoreCounterLabel->setString(str->getCString());
}