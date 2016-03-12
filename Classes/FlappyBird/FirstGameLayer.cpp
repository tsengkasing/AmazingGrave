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
    // 当然是创建物理世界喽
    auto scene = Scene::createWithPhysics();

    // 设置物理重力加速度
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

    // 一定要初始化分数，不然Again会有Bug
    Numeric::getInstance()->initScoreZero();

    // 设置一些flag的初始值以后有用
    flagPause = false;
    flagResume = false;
    flag = true;
    flagMusic = true;
    initBird2 = false;

    visibleSize = Director::getInstance()->getVisibleSize();

    // 背景图镇游戏。。
    bg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("bg1.png"));
    bg->setPosition(Vec2(0, 0));
    bg->setAnchorPoint(Vec2(0, 0));
    addChild(bg);

    // 创建背景的骷髅边框
    auto skullBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("SkullBarMain.png"));
    skullBar->setPosition(visibleSize / 2);
    addChild(skullBar, 10);

    // 创建帮助界面
    auto help = HelpLayer::create();
    addChild(help);

    // 创建一个星星粒子层
    auto emitter1 = ParticleSystemQuad::create("star1.plist");
    emitter1->retain();
    auto batch = ParticleBatchNode::createWithTexture(emitter1->getTexture());
    batch->addChild(emitter1);
    emitter1->setPosition(visibleSize / 2);
    emitter1->release();
    addChild(batch);

    // 管子层
    auto bar = Bar::create();
    bar->setAnchorPoint(Vec2(0, 0));
    bar->setPosition(0, 0);
    addChild(bar);

    // 地面层
    auto groundLayer = Ground::create();
    groundLayer->setAnchorPoint(Vec2(0, 0));
    groundLayer->setPosition(0, 0);
    addChild(groundLayer);

    // 前面的小鸟一只
    bird = BirdSprite::create();
    bird->setAnchorPoint(Vec2(0, 0));
    bird->setPosition(0, 0);
    addChild(bird, 0, "BirdXX");
    bird->changeState(ACTION_STATE_IDLE);

    // 点击屏幕让小鸟飞---开始游戏侦听器
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

    // 碰撞侦听器
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [=](PhysicsContact &contact){
        // 停止管子移动
        bar->stopBar();

        // 停止小鸟
        bird->changeState(ACTION_STATE_DIE);

        if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
        {
            bird2->getChildByName("the_bird")->stopAllActions();
            bird2->changeState(ACTION_STATE_DIE);
        }

        // 停止地面移动
        groundLayer->StopGround();

        // 游戏结束层
        auto gameover = GameOverLayer::create();
        addChild(gameover, 10);

        removeChild(Numeric::getInstance());

        // 停止背景移动
        bg->stopAllActions();

        unscheduleUpdate();

        // 停止侦听碰撞（会摔得。。很惨。。而且是头朝下。。。同时不能按暂停键）
        Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);
        Director::getInstance()->getEventDispatcher()->removeEventListener(pauseListener);
        flagPause = false;

        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    // 创建暂停的侦听器
    pauseListener = EventListenerKeyboard::create();
    pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
        if (code == EventKeyboard::KeyCode::KEY_ESCAPE && flagPause)
        {
            flagPause = !flagPause;
            pauseScene();
        }
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);

    // 小火龙无敌特效，用一个sprite执行
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

    // 关闭按钮
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

    // 后面的小鸟一只
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE && flag)
    {
        flag = !flag;
        bird2 = BirdSprite::create();
        bird2->setAnchorPoint(Vec2::ZERO);
        bird2->setPositionX(-650);
        addChild(bird2, 0, "BirdHL");
        bird2->getChildByName("the_bird")->getPhysicsBody()->setEnable(false);
        bird2->changeState(ACTION_STATE_IDLE);
        // 无敌闪烁效果
        schedule(schedule_selector(FirstGameLayer::godMode), 1 / 10);

        // 一个跳进场景的动画
        auto jumpTo = JumpBy::create(3, Vec2(400, -20), 40, 5);
        bird2->getChildByName("the_bird")->runAction(jumpTo);

        // 第二个小鸟用空格键控制
        keyListener = EventListenerKeyboard::create();
        keyListener->setEnabled(true);
        keyListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){

            if (code == EventKeyboard::KeyCode::KEY_SPACE)
            {
                // 取消无敌
                unschedule(schedule_selector(FirstGameLayer::godMode));
                if (!bird2->isVisible())
                {
                    bird2->setVisible(true);
                }
                // 隐藏提示
                spark->getChildByName("space")->runAction(FadeOut::create(1.0f));
                // 隐藏光环
                spark->runAction(FadeOut::create(1.0f));
                // 添加物理实体
                bird2->getChildByName("the_bird")->getPhysicsBody()->setEnable(true);
                bird2->changeState(ACTION_STATE_FLY);
                initBird2 = true;

                Director::getInstance()->getEventDispatcher()->removeEventListener(keyListener);
            }
        };

        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    }

    // 设置第二个小鸟一开始无敌特效的位置
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        spark->setPositionX(bird2->getChildByName("the_bird")->getPosition().x - 650);
        spark->setPositionY(bird2->getChildByName("the_bird")->getPosition().y - 20);
    }

    // 检查暂停界面按钮是否删除
    if (flagResume)
    {
        removeChild(menu);
        flagResume = !flagResume;
    }

    // 如果柱子数超过10小鸟2就会自动消失
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
        // 隐藏提示
        spark->getChildByName("space")->runAction(FadeOut::create(1.0f));
        // 隐藏光环
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
    // 创建暂停界面主UI
    pauseMainUI = Sprite::createWithSpriteFrameName("UI/pause.png");
    pauseMainUI->setPosition(visibleSize / 2);
    addChild(pauseMainUI);

    // 处理侦听器、物理世界
    Director::getInstance()->pause();
    // 处理bird1
    velocityXingxing = bird->getChildByName("the_bird")->getPhysicsBody()->getVelocity();
    bird->getChildByName("the_bird")->getPhysicsBody()->setVelocity(Vect(0, 0));
    bird->getChildByName("the_bird")->getPhysicsBody()->setGravityEnable(false);
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(bird);

    // 处理bird2
    if (Numeric::getInstance()->getScore() > BIRD2_ARRIVE)
    {
        velocityHuolong = bird2->getChildByName("the_bird")->getPhysicsBody()->getVelocity();
        bird2->getChildByName("the_bird")->getPhysicsBody()->setVelocity(Vect(0, 0));
        bird2->getChildByName("the_bird")->getPhysicsBody()->setGravityEnable(false);
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(bird2);
    }

    // ESC返回游戏
    pauseListener = EventListenerKeyboard::create();
    pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
        if (code == EventKeyboard::KeyCode::KEY_ESCAPE && !flagPause)
        {
            resumeScene();
        }
    };

    // 创建返回游戏按钮
    auto resumeSprite = Sprite::createWithSpriteFrameName("UI/resume.png");
    auto resumeSprite2 = Sprite::createWithSpriteFrameName("UI/resume.png");
    resumeSprite2->setScale(0.98f);
    resume = MenuItemSprite::create(resumeSprite, resumeSprite2, [=](Ref* pSender){
        resumeScene();
    });
    resume->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

    // 创建新游戏
    auto newGameSprite = Sprite::createWithSpriteFrameName("UI/newgame.png");
    auto newGameSprite2 = Sprite::createWithSpriteFrameName("UI/newgame.png");
    newGameSprite2->setScale(0.9f);
    newGame = MenuItemSprite::create(newGameSprite, newGameSprite2, [=](Ref* pSender){

        resumeScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1, FirstGameLayer::createScene()));
    });
    newGame->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    // 创建调音乐的按钮
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
