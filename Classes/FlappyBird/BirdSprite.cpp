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

    // �ӻ������ȡС��
    if (Numeric::getInstance()->getScore() <= BIRD2_ARRIVE)
    {
        birdSprite = Sprite::createWithSpriteFrameName("birdxingxing.png");
    }
    else
    {
        birdSprite = Sprite::createWithSpriteFrameName("birdhuolong.png");
    }

    // ��������С��
    auto physicsBirdBody = PhysicsBody::createCircle(birdSprite->getContentSize().width / 2);
    // ������������
    physicsBirdBody->setLinearDamping(0.7f);
    // ������ײ����
    physicsBirdBody->setCategoryBitmask(1);
    physicsBirdBody->setCollisionBitmask(-1);
    physicsBirdBody->setContactTestBitmask(-1);
    birdSprite->setPhysicsBody(physicsBirdBody);
    birdSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.6));
    addChild(birdSprite, 0, "the_bird");

    // ���ü����¼�
    if (Numeric::getInstance()->getScore() < BIRD2_ARRIVE)
    {
        touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(false);
        touchListener->onTouchBegan = [=](Touch * t, Event *e){
            return true;
        };

        touchListener->onTouchEnded = [=](Touch *t, Event *e){
            // ��С��һ�����ٶ�  
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

    // ���￪�˸���ʱ������ֹС��ɳ��߽磬��С��ͷ����ת�Ƕ�����  
    scheduleUpdate();
    return true;
}

void BirdSprite::update(float dt)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ֹ�ɳ��߽�  
    if (birdSprite->getPositionY() > (origin.y + visibleSize.height))
    {
        birdSprite->setPositionY(origin.y + visibleSize.height);
    }
    // ����С��ķ���ͷ���ĽǶȣ�����С��Y�᷽���ٶȾ������ٶ�Խ��Ƕȱ仯Խ��  
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

    // С��һ��ʼ��Ȼ�Ǿ�ֹ״̬~\(�R���Q)/~
    birdSprite->getPhysicsBody()->setGravityEnable(false);
}

void BirdSprite::stateFly()
{
    // һ����ʼ�ɣ������������ܵ���������
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

    // ֹͣ������
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(keyBoardListener);
    }
    Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);

    birdSprite->getPhysicsBody()->setGravityEnable(true);
}