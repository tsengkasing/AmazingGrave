#include "GameOver.h"
#include "Numeric.h"
#include "FirstGameLayer.h"
#include "SimpleAudioEngine.h"
#include "LevelInfo.h"
#include "LoadScene.h"
#include "SceneMComplete.h"
#include "MainSceneFirst.h"
#include "SimpleAudioEngine.h"

bool GameOverLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();

    // 分数板首先上升，然后执行回调函数
    auto scoreBoard = Sprite::createWithSpriteFrameName("UI/End.png");
    auto moveUp = MoveBy::create(1, Vec2(0, visibleSize.height / 2 + scoreBoard->getContentSize().height / 2));
    scoreBoard->setPosition(Vec2(visibleSize.width / 2, -scoreBoard->getContentSize().height / 2));
    
    // 回调接下来的动作
    auto callBk = CallFuncN::create(CC_CALLBACK_0(GameOverLayer::funcCallBack, this));

    scoreBoard->runAction(Sequence::create(moveUp, callBk, nullptr));

    addChild(scoreBoard);

    return true;
}

void GameOverLayer::playAgain()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1, FirstGameLayer::createScene()));
}

void GameOverLayer::backToMenu()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGM.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(1, MainSceneFirst::createScene()));
}

void GameOverLayer::nextScene()
{
    // v2
    extern enum _nowScene nowScene;
    nowScene = Game2;
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(TransitionFade::create(1, SceneMComplete::createScene(2)));
    return;
    //// v1
    //extern enum _nowScene nowScene;
    //nowScene = Game2;
    //Director::getInstance()->resume();
    //Director::getInstance()->replaceScene(TransitionFade::create(1, SceneMComplete::createScene(1)));
}

void GameOverLayer::showScore(float dt)
{
    // 显示分数咯
    displayScore++;
    // 按照格式一个一个来
    auto str = __String::createWithFormat("%d", displayScore);
    scoreLabel->setString(str->getCString());

    // 如果分数到了就停下！
    if (Numeric::getInstance()->getScore() == displayScore)
    {
        unschedule(schedule_selector(GameOverLayer::showScore));
    }
}

void GameOverLayer::funcCallBack()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/sfx_swooshing.mp3");
    // 有水波特效的文字
    auto nodeGrid = NodeGrid::create();
    // 结束文字
    auto text = Label::createWithTTF("Keep it more balanced", "/fonts/FFADMatro.ttf", 33);
    if (Numeric::getInstance()->getScore() == 30)
    {
        text = Label::createWithTTF("XingXing & HuoLong, You win", "/fonts/BuxtonSketch.ttf", 38);
    }
    text->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
    nodeGrid->addChild(text);
    text->enableShadow();
    nodeGrid->setPosition(0, 0);
    nodeGrid->runAction(RepeatForever::create(Waves3D::create(3, Size(40, 10), 5, 4)));
    nodeGrid->setAnchorPoint(Vec2::ZERO);

    // 在玩一次的按钮
    auto again = Sprite::createWithSpriteFrameName("UI/again.png");
    auto again2 = Sprite::createWithSpriteFrameName("UI/again.png");
    again2->setScale(0.95f);
    auto againMenu = MenuItemSprite::create(again, again2, CC_CALLBACK_0(GameOverLayer::playAgain, this));

    // 进入下一关的按钮
    auto next = Sprite::createWithSpriteFrameName("UI/next.png");
    auto next2 = Sprite::createWithSpriteFrameName("UI/next.png");
    next2->setScale(0.95f);
    auto nextMenu = MenuItemSprite::create(next, next2, CC_CALLBACK_0(GameOverLayer::nextScene, this));

    auto bNu1 = Sprite::create("UI/menu.png");
    auto bNu2 = Sprite::create("UI/menu.png");
    bNu2->setScale(0.95f);
    auto bNu = MenuItemSprite::create(bNu1, bNu2, CC_CALLBACK_0(GameOverLayer::backToMenu, this));

    auto menu = Menu::create(againMenu, nextMenu, bNu, nullptr);
    menu->setPosition(0, 0);
    addChild(menu);
    againMenu->setPosition(Vec2(visibleSize.width / 2 - next->getContentSize().width, visibleSize.height / 2 - next->getContentSize().height / 2));
    nextMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 ));
    bNu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - next->getContentSize().height - 10));

    displayScore = 0;
    auto str = __String::createWithFormat("%d", displayScore);
    scoreLabel = Label::createWithBMFont("/fonts/score.fnt", str->getCString());
    scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    addChild(scoreLabel);

    if (Numeric::getInstance()->getScore() > 0)
    {
        schedule(schedule_selector(GameOverLayer::showScore), 1.0f / Numeric::getInstance()->getScore());
    }

    addChild(nodeGrid);
}
