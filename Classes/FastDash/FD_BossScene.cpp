#include "LevelInfo.h"
#include "FD_BossScene.h"
#include "FlowWord.h"
#include "SceneMComplete.h"
#include "SimpleAudioEngine.h"
#include <cmath>
#include "MainSceneFirst.h"
using CocosDenshion::SimpleAudioEngine;

#define pi 3.1415926

FD_BossScene::FD_BossScene()
{
    hero = FD_Hero::create();
    boss = FD_Monster::create();
    time = 0.0f;
    updown = true;
    leftright = true;
    bomb = false;
}

Scene* FD_BossScene::createScene(int hp)
{
    Scene* scene = Scene::create();
    FD_BossScene* layer = FD_BossScene::create();
    layer->labellayer = FD_LabelLayer::create();
    layer->hero->SetCurrentHP(hp);
    scene->addChild(layer);
    scene->addChild(layer->labellayer);
    layer->labellayer->BindHero(layer->hero); //分数层绑定英雄 获取英雄信息。
    return scene;
}

bool FD_BossScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_gamelayer.png"));
    background->setPosition(visibleSize / 2);
    this->addChild(background, -1);

    hero->BindSprite(Sprite::createWithSpriteFrameName("F_LittleStar.png"));
    hero->setPosition(visibleSize.width * 0.1f, visibleSize.height / 2 - 50);
    hero->setScale(0.06f);
    hero->MovingAnimation();
    this->addChild(hero, 1);

    boss->BindSprite(Sprite::createWithSpriteFrameName("F_Boss.png"));
    boss->setScale(0.9f);
    boss->setPosition(visibleSize.width * 0.76, visibleSize.height / 2 - 60);
    this->addChild(boss, 1);

    auto flowword = FlowWord::create();
    this->addChild(flowword);
    flowword->ShowText("Attention", 2.0f, 3, visibleSize / 2, Color3B(0xFF, 0, 0));

    auto instruction = FlowWord::create(); //游戏提示
    auto follow = Follow::create(this);
    instruction->runAction(follow);
    this->addChild(instruction);
    instruction->ShowText("Use W/A/S/D or \n Up/Down/Left/Right \n  to move !",
        10.0f, 1, Point(20, 20), Color3B(192, 192, 192));

    bullet = FD_BulletCreater::create();
    bullet->BindHero(hero);
    bullet->BindBoss(boss);
    this->addChild(bullet, 2);

    Bomb = FD_Hero::create();
    Bomb->BindSprite(Sprite::createWithSpriteFrameName("F_skill.png"));
    Bomb->setScale(0.3f);
    Bomb->setPosition(hero->getPosition());
    this->addChild(Bomb, 3);
    Bomb->setVisible(false);

    this->setKeyboardEnabled(true);
    auto controller = EventListenerKeyboard::create();
    controller->onKeyPressed = CC_CALLBACK_2(FD_BossScene::onKeyPressed, this);
    controller->onKeyReleased = CC_CALLBACK_2(FD_BossScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(controller, this);

    this->schedule(schedule_selector(FD_BossScene::Attack), 1.2f);
    this->scheduleUpdate();

    return true;
}

void FD_BossScene::update(float delta)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    time += 0.01f;

    if (hero->GetCurrentHP() <= 0 && !bomb)
    {
        this->Fail();
        return;
    }

    if (time > 10.0f) //设置Boss左右移动
    {
        if (leftright == true)
        {
            if (boss->getPositionX() <= visibleSize.width * 0.88f)
            {
                boss->setPositionX(boss->getPositionX() + 3);
            }
            else
            {
                leftright = false;
            }
        }
        else
        {
            if (boss->getPositionX() >= visibleSize.width * 0.66f)
            {
                boss->setPositionX(boss->getPositionX() - 3);
            }
            else
            {
                leftright = true;
            }
        }
    }

    if (updown == true) //设置Boss上下移动
    {
        if (boss->getPositionY() <= visibleSize.height - 200)
        {
            boss->setPositionY(boss->getPositionY() + 3 + (int)time % 10);
        }
        else
        {
            updown = false;
        }
    }
    else
    {
        if (boss->getPositionY() >= 0)
        {
            boss->setPositionY(boss->getPositionY() - 3 - (int)time % 10);
        }
        else
        {
            updown = true;
        }
    }

    //限制英雄活动范围
    if (hero->getPositionY() >= visibleSize.height - 60)
    {
        hero->setPositionY(visibleSize.height - 60);
    }
    else if (hero->getPositionY() <= 0)
    {
        hero->setPositionY(0);
    }
    if (hero->getPositionX() >= visibleSize.width * 0.60f)
    {
        hero->setPositionX(visibleSize.width * 0.60f);
    }
    else if (hero->getPositionX() <= 0)
    {
        hero->setPositionX(0);
    }

    //坚持到结束后给予炸弹
    if (time >= 22.0f)
    {
        bomb = true;
        Bomb->setVisible(true);
        Bomb->setPosition(hero->getPosition());
        Bomb->setRotation(-atan(
            (boss->getPositionY() - hero->getPositionY())  //求旋转角度
            / (boss->getPositionX() - hero->getPositionX())
            ) * 180 / pi);
        labellayer->unscheduleUpdate();
        auto flowword = FlowWord::create();
        this->addChild(flowword);
        flowword->ShowText("Press B !!", 0.1f, 1, visibleSize / 2, Color3B(0xFF, 0, 0));
    }

    return;
}

void FD_BossScene::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    switch (keycode)
    {
    case (EventKeyboard::KeyCode::KEY_W) :
        hero->Move(0, 5); break;
    case (EventKeyboard::KeyCode::KEY_S) :
        hero->Move(0, -5); break;
    case (EventKeyboard::KeyCode::KEY_A) :
        hero->Move(-4, 0); break;
    case (EventKeyboard::KeyCode::KEY_D) :
        hero->Move(4, 0); break;
    case (EventKeyboard::KeyCode::KEY_UP_ARROW) :
        hero->Move(0, 5);  break;
    case (EventKeyboard::KeyCode::KEY_DOWN_ARROW) :
        hero->Move(0, -5);  break;
    case (EventKeyboard::KeyCode::KEY_LEFT_ARROW) :
        hero->Move(-4, 0);  break;
    case (EventKeyboard::KeyCode::KEY_RIGHT_ARROW) :
        hero->Move(4, 0);  break;
    case (EventKeyboard::KeyCode::KEY_B) : //扔炸弹
        if (bomb == true)
        {
            this->unscheduleUpdate();
            hero->SkillAnimation();
            auto callfunc = CallFunc::create(this, callfunc_selector(FD_BossScene::End));
            auto act = Sequence::create(MoveTo::create(1.0f, Vec2(boss->getPositionX() + 480, boss->getPositionY())),
                callfunc, TargetedAction::create(boss->getSprite(), boss->BlowAnimatation()), nullptr);
            Bomb->getSprite()->runAction(act);
            scheduleOnce(schedule_selector(FD_BossScene::Win), 3.0f);
        }break;
    default:
        return;
    }
    return;
}

void FD_BossScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    switch (keycode)
    {
    case (EventKeyboard::KeyCode::KEY_W) :
        hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_S) :
        hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_UP_ARROW) :
        hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_DOWN_ARROW) :
        hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_A) :
        hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_D) :
        hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_LEFT_ARROW) :
        hero->stopAllActions(); break;
    case (EventKeyboard::KeyCode::KEY_RIGHT_ARROW) :
        hero->stopAllActions(); break;
    default:
        return;
    }
    return;
}

void FD_BossScene::Attack(float delta)
{
    bullet->LetGo(8);
    return;
}

void FD_BossScene::End() //炸弹打中Boss后消失
{
    Bomb->setVisible(false);
    return;
}

void FD_BossScene::Win(float delta)
{
    Director::getInstance()->pause();

    //创建模糊背景
    auto pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
    pauseBackground->setPosition(visibleSize / 2);
    this->addChild(pauseBackground, 9);

    auto background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("End.png"));
    background->setPosition(visibleSize / 2);
    this->addChild(background, 10);

    auto nextItem = Sprite::createWithSpriteFrameName("UI/next.png");
    auto nextItemOn = Sprite::createWithSpriteFrameName("UI/next.png");
    nextItemOn->setScale(0.9f);
    auto next = MenuItemSprite::create(nextItem, nextItemOn, [=](Ref* pSender){
        extern enum _nowScene nowScene;
        nowScene = Game1;
        this->removeAllChildren();
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(SceneMComplete::createScene(1));
    });

    auto againItem = Sprite::createWithSpriteFrameName("UI/again.png");
    auto againItemOn = Sprite::createWithSpriteFrameName("UI/again.png");
    againItemOn->setScale(0.9f);
    auto restart = MenuItemSprite::create(againItem, againItemOn, [=](Ref* pSender){
        Director::getInstance()->resume();
        this->removeFromParent();
        Director::getInstance()->replaceScene(TransitionFade::create(1, FastDash::createScene()));
    });

    auto backItem = Sprite::create("UI/menu.png");
    auto backItemOn = Sprite::create("UI/menuOn.png");
    auto back = MenuItemSprite::create(backItem, backItemOn, [=](Ref* pSender){
        Director::getInstance()->resume();
        this->removeFromParent();
        Director::getInstance()->replaceScene(TransitionMoveInB::create(1, MainSceneFirst::createScene()));
    });

    auto menu = Menu::create(next, restart, back, nullptr);
    menu->setPosition(0, 0);
    restart->setPosition(Vec2(visibleSize.width / 2 - nextItem->getContentSize().width, visibleSize.height / 2 - nextItem->getContentSize().height / 2));
    next->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - nextItem->getContentSize().height - 10));

    this->addChild(menu, 11);

    int score = ((float)hero->GetCurrentHP() / (float)hero->GetFullHP() * 20) + 80;
    auto scoreLabel = LabelTTF::create(String::createWithFormat("%d", score)->getCString(), "angryblue", 34);
    scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.63f);
    this->addChild(scoreLabel, 11);

    return;
}

void FD_BossScene::Fail()
{
    Director::getInstance()->pause();

    //创建模糊背景
    auto pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
    pauseBackground->setPosition(visibleSize / 2);
    this->addChild(pauseBackground, 9);

    auto background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("End.png"));
    background->setPosition(visibleSize / 2);
    this->addChild(background, 10);

    auto again = Sprite::createWithSpriteFrameName("UI/again.png");
    auto againOn = Sprite::createWithSpriteFrameName("UI/again.png");
    againOn->setScale(0.9f);
    auto restart = MenuItemSprite::create(again, againOn, [=](Ref* pSender){
        Director::getInstance()->resume();
        this->removeFromParent();
        Director::getInstance()->replaceScene(TransitionFade::create(1, FastDash::createScene()));
    });

    auto nextItem = Sprite::createWithSpriteFrameName("UI/next.png");
    auto nextItemOn = Sprite::createWithSpriteFrameName("UI/next.png");
    nextItemOn->setScale(0.9f);
    auto next = MenuItemSprite::create(nextItem, nextItemOn, [=](Ref* pSender){
        extern enum _nowScene nowScene;
        nowScene = Game1;
        this->removeFromParent();
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(TransitionFade::create(1, SceneMComplete::createScene(1)));
    });

    auto backMenu = Sprite::create("UI/menu.png");
    auto backMenuOn = Sprite::create("UI/menu.png");
    backMenuOn->setScale(0.9f);
    auto back = MenuItemSprite::create(backMenu, backMenuOn, [=](Ref* pSender){
        Director::getInstance()->resume();
        this->removeFromParent();
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGM.mp3");
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainSceneFirst::createScene()));
    });

    auto menu = Menu::create(restart, back, next, nullptr);
    menu->setPosition(0, 0);
    restart->setPosition(Vec2(visibleSize.width / 2 - nextItem->getContentSize().width, visibleSize.height / 2 - nextItem->getContentSize().height / 2));
    next->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - nextItem->getContentSize().height - 10));

    this->addChild(menu, 10);

    int score = (time / 22.0f * 20) + 60;
    auto scoreLabel = LabelTTF::create(String::createWithFormat("%d", score)->getCString(), "angryblue", 34);
    scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.63);
    this->addChild(scoreLabel, 11);

    return;
}