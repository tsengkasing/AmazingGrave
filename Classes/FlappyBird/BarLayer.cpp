#include "BarLayer.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"
#include "Numeric.h"
#include <ctime>

Bar::Bar()
{

}

Bar::~Bar()
{

}

bool Bar::init()
{
    if (!Layer::init())
    {
        return false;
    }

    flag = true;
    flag3 = 0;
    counter = 0;
    barInterval = 1.5f;
    flagGameOver = false;

    return true;
}

void Bar::setBarMove(float dt)
{
    score = Numeric::getInstance()->getScore();

    visibleSize = Director::getInstance()->getVisibleSize();
    // 添加上管
    auto upBar = Sprite::createWithSpriteFrameName("upbar2.png");
    upBar->setPosition(Vec2(upBar->getContentSize().width / 2, upBar->getContentSize().height / 2 + 500));
    auto upPhyBody = PhysicsBody::createBox(upBar->getContentSize());
    upPhyBody->setGravityEnable(false);
    upPhyBody->setDynamic(false);
    upPhyBody->setCategoryBitmask(1);
    upPhyBody->setCollisionBitmask(-1);
    upPhyBody->setContactTestBitmask(-1);
    upBar->setPhysicsBody(upPhyBody);

    // 添加下管
    auto downBar = Sprite::createWithSpriteFrameName("downbar2.png");
    // 这里Y轴减去120是为了空出小鸟钻过的空间
    downBar->setPosition(Vec2(downBar->getContentSize().width / 2, downBar->getContentSize().height / 2 - 180));
    auto downPhyBody = PhysicsBody::createBox(downBar->getContentSize());
    downPhyBody->setGravityEnable(false);
    downPhyBody->setDynamic(false);
    downPhyBody->setCategoryBitmask(1);
    downPhyBody->setCollisionBitmask(-1);
    downPhyBody->setContactTestBitmask(-1);
    downBar->setPhysicsBody(downPhyBody);

    // 创建一个粒子
    auto emitter1 = ParticleSystemQuad::create("fire1.plist");
    emitter1->retain();
    auto batch = ParticleBatchNode::createWithTexture(emitter1->getTexture());
    batch->addChild(emitter1);
    emitter1->setPosition(Vec2(downBar->getPositionX(), downBar->getPositionY() + 100));
    emitter1->release();

    auto emitter2 = ParticleSystemQuad::create("fire2.plist");
    emitter2->retain();
    auto batch2 = ParticleBatchNode::createWithTexture(emitter2->getTexture());
    batch2->addChild(emitter2);
    emitter2->setPosition(Vec2(upBar->getPositionX(), upBar->getPositionY() - 100));
    emitter2->release();

    // 用一个Sprite来封装他们，并添加标签
    barSprite = Sprite::create();
    barSprite->addChild(upBar, 0, "up_bar");
    barSprite->addChild(downBar, 0, "down_bar");
    barSprite->addChild(batch, 0, "batch");
    barSprite->addChild(batch2, 0, "batch2");
    barSprite->setAnchorPoint(Vec2(0, 0));
    barSprite->setTag(counter++);

    // 随机一下管子的Y轴补偿，以模拟随机生成管子
    rand = (CCRANDOM_0_1() * 200);
    // 难度管理
    barLevelManage();

    barSprite->setPosition(Vec2(1100, -220 + rand));

    // 创建一个移动的动画
    auto moveLeft = MoveBy::create(6, Vec2(-2000, 0));

    // 创建移动完成后的回调函数
    auto callBack = CallFuncN::create(CC_CALLBACK_1(Bar::barMovedOver, this));

    // 创建一个序列执行他们
    auto sequence = Sequence::create(moveLeft, callBack, nullptr);

    // 由封装好的barSprite来执行序列
    barSprite->runAction(sequence);

    addChild(barSprite);
    flag2 = 1;

    // 把屏幕出现的管道都放在Vector里管理
    barVector.pushBack(barSprite);

    if (flag)
    {
        scheduleUpdate();
        flag = false;
    }
    // 这里结束游戏
    if (score >= LEVEL_4 - 2)
    {
        barSprite->setVisible(false);
        barSprite->getChildByName("up_bar")->getPhysicsBody()->setEnable(false);
        barSprite->getChildByName("down_bar")->getPhysicsBody()->setEnable(false);
    }
    if (score >= LEVEL_4)
    {
        if (!flagGameOver)
        scheduleOnce([=](float){
            flagGameOver = true;
            // 隐藏提示
            Director::getInstance()->getRunningScene()->getChildByName("Layer")->getChildByName("Spark")->getChildByName("space")->runAction(FadeOut::create(1.0f));
            // 隐藏光环
            Director::getInstance()->getRunningScene()->getChildByName("Layer")->getChildByName("Spark")->runAction(FadeOut::create(1.0f));
            Director::getInstance()->getRunningScene()->getChildByName("Layer")->removeChild(Numeric::getInstance());
            Director::getInstance()->getRunningScene()->addChild(GameOverLayer::create());
            Director::getInstance()->getRunningScene()->getChildByName("Layer")->getChildByName("BirdXX")->getChildByName("the_bird")->getPhysicsBody()->setEnable(false);
            Director::getInstance()->getRunningScene()->getChildByName("Layer")->getChildByName("BirdHL")->getChildByName("the_bird")->getPhysicsBody()->setEnable(false);
            Director::getInstance()->getRunningScene()->getChildByName("Layer")->getChildByName("BirdHL")->runAction(EaseIn::create(MoveTo::create(7, Vec2(1000, visibleSize.height / 2 - 300)), 4));
            Director::getInstance()->getRunningScene()->getChildByName("Layer")->getChildByName("BirdXX")->runAction(EaseIn::create(MoveTo::create(5, Vec2(1000, visibleSize.height / 2 - 300)), 4));
        }, 5, "YouWin");
        unscheduleUpdate();
    }

}

void Bar::startBar()
{
    // 每隔1.5秒生成一个柱子
    schedule(schedule_selector(Bar::setBarMove), barInterval);
}

void Bar::barLevelManage()
{
    if (score >= LEVEL_0 && score < LEVEL_1)
    {
        barInterval = 1.4f;
        unschedule(schedule_selector(Bar::setBarMove));
        schedule(schedule_selector(Bar::setBarMove), barInterval);
        rand *= 1.1;
    }

    if (score >= LEVEL_1 && score < LEVEL_2 || score >= LEVEL_3)
    {
        barInterval = 1.2f;
        unschedule(schedule_selector(Bar::setBarMove));
        schedule(schedule_selector(Bar::setBarMove), barInterval);
        rand += 20;
        switch (rand % 4)
        {
        case 0:
            barSprite->runAction(MoveBy::create(5, Vec2(0, 88)));
            break;
        case 1:
            barSprite->runAction(MoveBy::create(5, Vec2(0, -88)));
            break;
        case 2:
            barSprite->runAction(MoveBy::create(5, Vec2(0, 88)));
            break;
        case 3:
            barSprite->runAction(MoveBy::create(5, Vec2(0, -88)));
        default:
            break;
        }
    }

    if (score >= LEVEL_2 && score <= LEVEL_3)
    {
        switch (rand % 4)
        {
        case 0:
            barSprite->runAction(RotateBy::create(3, -5));
            break;
        case 1:
            barSprite->runAction(RotateBy::create(3, -10));
            break;
        case 2:
            barSprite->runAction(RotateBy::create(3, 5));
            break;
        case 3:
            barSprite->runAction(RotateBy::create(3, 10));
        default:
            break;
        }
    }

    if (score >= LEVEL_3)
    {
        barInterval = 0.8f;
        unschedule(schedule_selector(Bar::setBarMove));
        schedule(schedule_selector(Bar::setBarMove), barInterval);
        barSprite->runAction(JumpBy::create(4, Vec2(0, -50), 50, 2));
    }

}

void Bar::stopBar()
{
    // 停止加管子
    unschedule(schedule_selector(Bar::setBarMove));

    // 遍历容器，让管子们停下来
    for (auto &it : barVector)
    {
        it->stopAllActions();

        it->getChildByName("down_bar")->getPhysicsBody()->setEnable(false);
    }
}

// 移动结束之后的回调函数，用来删除移动完毕的管子
void Bar::barMovedOver(Ref *r)
{
    auto item = (Sprite *)r;
    barVector.eraseObject(item);
    removeChild(item);
    flag3--;
}

void Bar::update(float dt)
{
    // 处理第0个管子
    auto bar = barVector.at(flag3);
    if (bar->getPositionX() + bar->getContentSize().width / 2 < (visibleSize.width / 2) && flag2)
    {
        // 为了成功放声音，设置了flag2 。。以免无限放声音
        Numeric::getInstance()->addScore();
        flag2 = false;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/sfx_point.mp3");
        flag3++;
    }
}