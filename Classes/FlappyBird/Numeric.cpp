#include "Numeric.h"

// ��������ֵNULL
static Numeric* number = NULL;

Numeric* Numeric::getInstance()
{
    // ����˵��������ھʹ���һ��
    if (!number)
    {
        number = new Numeric;
        
        // ��ʼ��֮
        number->init();
    }
    // ����Ѿ����ڣ���ֱ�ӷ���
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