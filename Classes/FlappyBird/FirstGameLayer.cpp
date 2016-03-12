#include "FirstGameLayer.h"
#include "BarLayer.h"
#include "LandLayer.h"
#include "BirdSprite.h"
#include "SimpleAudioEngine.h"
#include "Help.h"
#include "Numeric.h"
#include "GameOver.h"

Scene *FirstGameLayer::createScene()
{
    // ��Ȼ�Ǵ������������
    auto scene = Scene::createWithPhysics();

    // ���������������ٶ�
    scene->getPhysicsWorld()->setGravity(Vect(0, -980));
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = FirstGameLayer::create();
    
    scene->addChild(layer, 0, "Layer");

    return scene;
}

bool FirstGameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // һ��Ҫ��ʼ����������ȻAgain����Bug
    Numeric::getInstance()->initScoreZero();

    // ����һЩflag�ĳ�ʼֵ�Ժ�����
    flagPause = false;
    flagResume = false;
    flag = true;
    flagMusic = true;
    initBird2 = false;

    visibleSize = Director::getInstance()->getVisibleSize();

    // ����ͼ����Ϸ����
    bg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("bg1.png"));
    bg->setPosition(Vec2(0, 0));
    bg->setAnchorPoint(Vec2(0, 0));
    addChild(bg);

    // �������������ñ߿�
    auto skullBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("SkullBarMain.png"));
    skullBar->setPosition(visibleSize / 2);
    addChild(skullBar, 10);

    // ������������
    auto help = HelpLayer::create();
    addChild(help);

    // ����һ���������Ӳ�
    auto emitter1 = ParticleSystemQuad::create("star1.plist");
    emitter1->retain();
    auto batch = ParticleBatchNode::createWithTexture(emitter1->getTexture());
    batch->addChild(emitter1);
    emitter1->setPosition(visibleSize / 2);
    emitter1->release();
    addChild(batch);

    // ���Ӳ�
    auto bar = Bar::create();
    bar->setAnchorPoint(Vec2(0, 0));
    bar->setPosition(0, 0);
    addChild(bar);

    // �����
    auto groundLayer = Ground::create();
    groundLayer->setAnchorPoint(Vec2(0, 0));
    groundLayer->setPosition(0, 0);
    addChild(groundLayer);

    // ǰ���С��һֻ
    bird = BirdSprite::create();
    bird->setAnchorPoint(Vec2(0, 0));
    bird->setPosition(0, 0);
    addChild(bird, 0, "BirdXX");
    bird->changeState(ACTION_STATE_IDLE);

    // �����Ļ��С���---��ʼ��Ϸ������
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *t, Event *e){
        return true;
    };

    listener->onTouchEnded = [=](Touch * t, Event * e)
    {
        flagPause = true;

        scheduleUpdate();

        groundLayer->StartGround();

        bar->startBar();

        bird->changeState(ACTION_STATE_FLY);

        addChild(Numeric::getInstance());

        Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // ��ײ������
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [=](PhysicsContact &contact){
        // ֹͣ�����ƶ�
        bar->stopBar();

        // ֹͣС��
        bird->changeState(ACTION_STATE_DIE);

        if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
        {
            bird2->getChildByName("the_bird")->stopAllActions();
            bird2->changeState(ACTION_STATE_DIE);
        }

        // ֹͣ�����ƶ�
        groundLayer->StopGround();

        // ��Ϸ������
        auto gameover = GameOverLayer::create();
        addChild(gameover, 10);

        removeChild(Numeric::getInstance());

        // ֹͣ�����ƶ�
        bg->stopAllActions();

        unscheduleUpdate();

        // ֹͣ������ײ����ˤ�á����ܲҡ���������ͷ���¡�����ͬʱ���ܰ���ͣ����
        Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);
        Director::getInstance()->getEventDispatcher()->removeEventListener(pauseListener);
        flagPause = false;

        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    // ������ͣ��������
    pauseListener = EventListenerKeyboard::create();
    pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
        if (code == EventKeyboard::KeyCode::KEY_ESCAPE && flagPause)
        {
            flagPause = !flagPause;
            pauseScene();
        }
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);

    // С�����޵���Ч����һ��spriteִ��
    char name[20];
    Vector<SpriteFrame *>loadVector;
    for (int i = 1; i < 7; i++)
    {
        sprintf(name, "huolong%d.png", i);
        loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    }

    auto animate = Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 24.0f));
    spark = Sprite::create();
    spark->runAction(RepeatForever::create(animate));
    spark->setPositionX(-visibleSize.width);
    addChild(spark, 0, "Spark");

    auto spaceHelp = Sprite::createWithSpriteFrameName("UI/space.png");
    spaceHelp->setPositionX(spaceHelp->getPositionX() + 40);
    spaceHelp->setPositionY(spaceHelp->getPositionY());
    spark->addChild(spaceHelp, 0, "space");

    // �رհ�ť
    auto exitb = Sprite::create("exit.png");
    auto exitb2 = Sprite::create("exit.png");
    exitb2->setScale(0.9f);
    auto exitMenuItem = MenuItemSprite::create(exitb, exitb2, [=](Ref* r){
        exit(EXIT_SUCCESS);
    });
    auto exitMenu = Menu::create(exitMenuItem, nullptr);
    exitMenu->setPosition(51, visibleSize.height - 51);
    addChild(exitMenu);
    return true;
}

void FirstGameLayer::update(float dt)
{
    bg->setPositionX(bg->getPositionX() - 0.6);
    if (bg->getPositionX() < -640)
    {
        bg->setPositionX(0);
    }

    // �����С��һֻ
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE && flag)
    {
        flag = !flag;
        bird2 = BirdSprite::create();
        bird2->setAnchorPoint(Vec2::ZERO);
        bird2->setPositionX(-650);
        addChild(bird2, 0, "BirdHL");
        bird2->getChildByName("the_bird")->getPhysicsBody()->setEnable(false);
        bird2->changeState(ACTION_STATE_IDLE);
        // �޵���˸Ч��
        schedule(schedule_selector(FirstGameLayer::godMode), 1 / 10);

        // һ�����������Ķ���
        auto jumpTo = JumpBy::create(3, Vec2(400, -20), 40, 5);
        bird2->getChildByName("the_bird")->runAction(jumpTo);

        // �ڶ���С���ÿո������
        keyListener = EventListenerKeyboard::create();
        keyListener->setEnabled(true);
        keyListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){

            if (code == EventKeyboard::KeyCode::KEY_SPACE)
            {
                // ȡ���޵�
                unschedule(schedule_selector(FirstGameLayer::godMode));
                if (!bird2->isVisible())
                {
                    bird2->setVisible(true);
                }
                // ������ʾ
                spark->getChildByName("space")->runAction(FadeOut::create(1.0f));
                // ���ع⻷
                spark->runAction(FadeOut::create(1.0f));
                // �������ʵ��
                bird2->getChildByName("the_bird")->getPhysicsBody()->setEnable(true);
                bird2->changeState(ACTION_STATE_FLY);
                initBird2 = true;

                Director::getInstance()->getEventDispatcher()->removeEventListener(keyListener);
            }
        };

        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    }

    // ���õڶ���С��һ��ʼ�޵���Ч��λ��
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        spark->setPositionX(bird2->getChildByName("the_bird")->getPosition().x - 650);
        spark->setPositionY(bird2->getChildByName("the_bird")->getPosition().y - 20);
    }

    // �����ͣ���水ť�Ƿ�ɾ��
    if (flagResume)
    {
        removeChild(menu);
        flagResume = !flagResume;
    }

    // �������������10С��2�ͻ��Զ���ʧ
    if (Numeric::getInstance()->getScore() == 11 && !initBird2)
    {
        flag = false;
        unschedule(schedule_selector(FirstGameLayer::godMode));
        if (!bird2->isVisible())
        {
            bird2->setVisible(true);
        }

        bird2->getChildByName("the_bird")->runAction(FadeOut::create(1));
        Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(bird2);
        // ������ʾ
        spark->getChildByName("space")->runAction(FadeOut::create(1.0f));
        // ���ع⻷
        spark->runAction(FadeOut::create(1.0f));
        Director::getInstance()->getEventDispatcher()->removeEventListener(keyListener);
    }
}

void FirstGameLayer::godMode(float dt)
{
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        bird2->setVisible(!bird2->isVisible());
    }
}

void FirstGameLayer::pauseScene()
{
    // ������ͣ������UI
    pauseMainUI = Sprite::createWithSpriteFrameName("UI/pause.png");
    pauseMainUI->setPosition(visibleSize / 2);
    addChild(pauseMainUI);

    // ��������������������
    Director::getInstance()->pause();
    // ����bird1
    velocityXingxing = bird->getChildByName("the_bird")->getPhysicsBody()->getVelocity();
    bird->getChildByName("the_bird")->getPhysicsBody()->setVelocity(Vect(0, 0));
    bird->getChildByName("the_bird")->getPhysicsBody()->setGravityEnable(false);
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(bird);

    // ����bird2
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        velocityHuolong = bird2->getChildByName("the_bird")->getPhysicsBody()->getVelocity();
        bird2->getChildByName("the_bird")->getPhysicsBody()->setVelocity(Vect(0, 0));
        bird2->getChildByName("the_bird")->getPhysicsBody()->setGravityEnable(false);
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(bird2);
    }

    // ESC������Ϸ
    pauseListener = EventListenerKeyboard::create();
    pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
        if (code == EventKeyboard::KeyCode::KEY_ESCAPE && !flagPause)
        {
            resumeScene();
        }
    };

    // ����������Ϸ��ť
    auto resumeSprite = Sprite::createWithSpriteFrameName("UI/resume.png");
    auto resumeSprite2 = Sprite::createWithSpriteFrameName("UI/resume.png");
    resumeSprite2->setScale(0.98f);
    resume = MenuItemSprite::create(resumeSprite, resumeSprite2, [=](Ref* pSender){
        resumeScene();
    });
    resume->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

    // ��������Ϸ
    auto newGameSprite = Sprite::createWithSpriteFrameName("UI/newgame.png");
    auto newGameSprite2 = Sprite::createWithSpriteFrameName("UI/newgame.png");
    newGameSprite2->setScale(0.9f);
    newGame = MenuItemSprite::create(newGameSprite, newGameSprite2, [=](Ref* pSender){

        resumeScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1, FirstGameLayer::createScene()));
    });
    newGame->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    // ���������ֵİ�ť
    auto musicSprite = Sprite::createWithSpriteFrameName("UI/music.png");
    auto musicSprite2 = Sprite::createWithSpriteFrameName("UI/music.png");
    musicSprite2->setScale(0.9f);
    music = MenuItemSprite::create(musicSprite, musicSprite2, [=](Ref* pSender){
        if (flagMusic)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        else
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
        flagMusic = !flagMusic;
    });
    music->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);

    menu = Menu::create(resume, music, newGame, nullptr);
    menu->setPosition(0, 0);
    addChild(menu);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);
}

void FirstGameLayer::resumeScene()
{
    flagResume = true;
    removeChild(pauseMainUI);
    flagPause = !flagPause;
    Director::getInstance()->resume();
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(bird);

    bird->getChildByName("the_bird")->getPhysicsBody()->setVelocity(velocityXingxing);
    bird->getChildByName("the_bird")->getPhysicsBody()->setGravityEnable(true);

    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(bird2);
        bird2->getChildByName("the_bird")->getPhysicsBody()->setVelocity(velocityHuolong);
        bird2->getChildByName("the_bird")->getPhysicsBody()->setGravityEnable(false);
    }
    Director::getInstance()->getEventDispatcher()->removeEventListener(pauseListener);
}
