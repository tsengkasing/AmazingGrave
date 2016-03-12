#include "BirdSprite.h"
#include "Numeric.h"
#include "SimpleAudioEngine.h"

BirdSprite *BirdSprite::createBird()
{
    auto bird = BirdSprite::create();

    return bird;
}

bool BirdSprite::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 从缓存里读取小鸟
    if (Numeric::getInstance()->getScore() <= BIRD2_ARRIVE)
    {
        birdSprite = Sprite::createWithSpriteFrameName("birdxingxing.png");
    }
    else
    {
        birdSprite = Sprite::createWithSpriteFrameName("birdhuolong.png");
    }

    // 设置物理小鸟
    auto physicsBirdBody = PhysicsBody::createCircle(birdSprite->getContentSize().width / 2);
    // 设置线性阻尼
    physicsBirdBody->setLinearDamping(0.7f);
    // 设置碰撞掩码
    physicsBirdBody->setCategoryBitmask(1);
    physicsBirdBody->setCollisionBitmask(-1);
    physicsBirdBody->setContactTestBitmask(-1);
    birdSprite->setPhysicsBody(physicsBirdBody);
    birdSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.6));
    addChild(birdSprite, 0, "the_bird");

    // 设置监听事件
    if (Numeric::getInstance()->getScore() < BIRD2_ARRIVE)
    {
        touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(false);
        touchListener->onTouchBegan = [=](Touch * t, Event *e){
            return true;
        };

        touchListener->onTouchEnded = [=](Touch *t, Event *e){
            // 给小鸟一个初速度  
            birdSprite->getPhysicsBody()->setVelocity(Vec2(0, 340));
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/sfx_wing.mp3");
        };
    }
    else
    {
        keyBoardListener = EventListenerKeyboard::create();
        keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
        };

        keyBoardListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event *e){
            
            if (code == EventKeyboard::KeyCode::KEY_SPACE)
            {
                birdSprite->getPhysicsBody()->setVelocity(Vec2(0, 280));
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/sfx_wing.mp3");
            }
        };
    }

    // 这里开了个定时器，防止小鸟飞出边界，和小鸟头部旋转角度设置  
    scheduleUpdate();
    return true;
}

void BirdSprite::update(float dt)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 防止飞出边界  
    if (birdSprite->getPositionY() > (origin.y + visibleSize.height))
    {
        birdSprite->setPositionY(origin.y + visibleSize.height);
    }
    // 调整小鸟的飞行头部的角度，根据小鸟Y轴方向速度决定，速度越大角度变化越大  
    birdSprite->setRotation(birdSprite->getPhysicsBody()->getVelocity().y*-0.1);
}

void BirdSprite::changeState(ActionState state)
{
    switch (state)
    {
    case ACTION_STATE_IDLE:
        stateIdle();
        break;
    case ACTION_STATE_FLY:
        stateFly();
        break;
    case ACTION_STATE_DIE:
        stateDie();
        break;
    default:
        break;
    }
}

void BirdSprite::stateIdle()
{
    if (Numeric::getInstance()->getScore() < BIRD2_ARRIVE)
    {
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    }
    else
    {
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
    }

    // 小鸟一开始当然是静止状态~\(≧▽≦)/~
    birdSprite->getPhysicsBody()->setGravityEnable(false);
}

void BirdSprite::stateFly()
{
    // 一单开始飞，让他俩。。受到重力作用
    birdSprite->getPhysicsBody()->setGravityEnable(true);
}

void BirdSprite::stateDie()
{
    birdSprite->runAction(Sequence::create(CallFuncN::create([](Node*){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/audio/sfx_hit.mp3");
    }), DelayTime::create(1.0f), CallFuncN::create([](Node*){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/audio/sfx_die.mp3");
    }), nullptr));

    unscheduleUpdate();

    // 停止侦听器
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(keyBoardListener);
    }
    Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);

    birdSprite->getPhysicsBody()->setGravityEnable(true);
}