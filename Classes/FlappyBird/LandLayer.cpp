#include "LandLayer.h"

bool Ground::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��ӵ���1
    ground1 = Sprite::createWithSpriteFrameName("gr1.png");
    ground1->setPosition(Vec2(ground1->getContentSize().width / 2, ground1->getContentSize().height / 2));
    auto phyBody = PhysicsBody::createBox(ground1->getContentSize());
    ground1->setPhysicsBody(phyBody);
    // �Ϸ�Ҫ���ǰ����Ĳݵأ��ԹԴ��ţ�
    phyBody->setGravityEnable(false);
    phyBody->setDynamic(false);

    ground1->getPhysicsBody()->setCategoryBitmask(1);
    ground1->getPhysicsBody()->setCollisionBitmask(-1);
    ground1->getPhysicsBody()->setContactTestBitmask(-1);
    // Z-Order��ʱҲд��zorder��ָ���Ƕ���֮��Ĳ�ι�ϵ
    addChild(ground1, 2);

    // ��ӵ���2
    ground2 = Sprite::createWithSpriteFrameName("gr2.png");
    ground2->setPosition(Vec2(visibleSize.width / 2 + 200, ground2->getContentSize().height / 2));
    auto phyBody2 = PhysicsBody::createBox(ground2->getContentSize());
    ground2->setPhysicsBody(phyBody2);
    phyBody2->setGravityEnable(false);
    phyBody2->setDynamic(false);
    ground2->getPhysicsBody()->setCategoryBitmask(1);
    ground2->getPhysicsBody()->setCollisionBitmask(-1);
    ground2->getPhysicsBody()->setContactTestBitmask(-1);
    addChild(ground2, 2);

    // ��һЩ����
    skulls = Sprite::createWithSpriteFrameName("skulls.png");
    skulls->setPosition(Vec2(visibleSize.width + skulls->getContentSize().width/2, skulls->getContentSize().height / 2));
    addChild(skulls, 3);

    // ����һ���������Ӳ�
    auto emitter1 = ParticleSystemQuad::create("landbar.plist");
    emitter1->retain();
    auto batch = ParticleBatchNode::createWithTexture(emitter1->getTexture());
    batch->addChild(emitter1);
    emitter1->setPosition(Vec2(visibleSize.width / 2, 0));
    emitter1->release();
    addChild(batch, 4);

    return true;
}

void Ground::StartGround()
{   
    // �õ��涯����
    schedule(schedule_selector(Ground::MoveGround), 1.0f / 60);
}

void Ground::MoveGround(float dt)
{
    ground1->setPositionX(ground1->getPositionX() - 2);
    ground2->setPositionX(ground1->getPositionX() + ground1->getContentSize().width - 2);
    if (ground1->getPositionX() <= 0)
    {
        ground1->setPositionX(ground1->getContentSize().width / 2);
    }

    skulls->setPositionX(skulls->getPositionX() - 2);
    if (skulls->getPositionX() + skulls->getContentSize().width < 0)
    {
        skulls->setPositionX(Director::getInstance()->getVisibleSize().width + skulls->getContentSize().width / 2);
    }
}

void Ground::StopGround()
{
    unschedule(schedule_selector(Ground::MoveGround));
}