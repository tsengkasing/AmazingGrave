#include "MainSceneFirst.h"
#include "SimpleAudioEngine.h"
#include "GraveMainScene.h"
#include "SimpleAudioEngine.h"
#include "LevelInfo.h"

using CocosDenshion::SimpleAudioEngine;

Scene* MainSceneFirst::createScene()
{
    auto scene = Scene::create();

    auto layer = MainSceneFirst::create();

    scene->addChild(layer);

    return scene;
}

bool MainSceneFirst::init()
{
    if (!Layer::init())
    {
        return false;
    }
    isBGMPlay = true;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/UI/UIMain.plist");

    visibleSize = Director::getInstance()->getVisibleSize();

    backGround = Sprite::create("mainScene1.png");
    wordAmazingGrave = Sprite::create("mainSceneAG.png");
    characterXZJ = Sprite::create("mainSceneZJ.png");

    backGround->setPosition(visibleSize / 2);
    wordAmazingGrave->setPosition(visibleSize / 2);
    characterXZJ->setPosition(visibleSize / 2);
    addChild(backGround);
    addChild(characterXZJ);

    copyRight = Sprite::create("CopyRight.png");
    copyRight->runAction(FadeOut::create(0));
    addChild(copyRight);

    // 给文字加水波抖动特效
    auto wordsGrid = NodeGrid::create();
    wordsGrid->addChild(wordAmazingGrave);
    wordsGrid->setPosition(0, 0);
    wordsGrid->runAction(RepeatForever::create(Waves3D::create(6, Size(40, 10), 5, 2)));
    addChild(wordsGrid);

    characterXZJ->runAction(Sequence::create(FadeOut::create(0), DelayTime::create(1), FadeIn::create(4), nullptr));
    wordAmazingGrave->runAction(Sequence::create(MoveBy::create(0, Vec2(0, -50)),
        FadeOut::create(0), DelayTime::create(2),
        Spawn::create(FadeIn::create(3), MoveBy::create(1.5f, Vec2(0, 50)), nullptr),
        nullptr));

    auto play1 = Sprite::createWithSpriteFrameName("play.png");
    auto play2 = Sprite::createWithSpriteFrameName("play.png");
    auto characters1 = Sprite::createWithSpriteFrameName("characters.png");
    auto characters2 = Sprite::createWithSpriteFrameName("characters.png");
    auto music1 = Sprite::createWithSpriteFrameName("music.png");
    auto music2 = Sprite::createWithSpriteFrameName("music.png");
    auto exit1 = Sprite::create("exit.png");
    auto exit2 = Sprite::create("exit.png");
    auto setting1 = Sprite::createWithSpriteFrameName("settings.png");
    auto setting2 = Sprite::createWithSpriteFrameName("settings.png");
    auto back1 = Sprite::create("UI/back.png");
    auto back2 = Sprite::create("UI/back.png");

    play2->setScale(0.9f);
    characters2->setScale(0.9f);
    music2->setScale(0.9f);
    exit2->setScale(0.9f);
    setting2->setScale(0.9f);

    // 主菜单
    auto play = MenuItemSprite::create(play1, play2, CC_CALLBACK_1(MainSceneFirst::menuPlayCallback, this));
    auto characters = MenuItemSprite::create(characters1, characters2, CC_CALLBACK_1(MainSceneFirst::menuCharactersCallback, this));
    auto music = MenuItemSprite::create(music1, music2, CC_CALLBACK_1(MainSceneFirst::menuMusicCallback, this));
    auto exit = MenuItemSprite::create(exit1, exit2, CC_CALLBACK_1(MainSceneFirst::menuCloseCallback, this));
    auto setting = MenuItemSprite::create(setting1, setting2, CC_CALLBACK_1(MainSceneFirst::menuSettingsCallback, this));
    play->setPosition(visibleSize.width / 2, 640 - 357.5f);
    characters->setPosition(480, 640 - 464.5f);
    exit->setPosition(52.5f, 640 - 50);
    setting->setPosition(909.5, 640 - 54);
    music->setPosition(847.5f, 640 - 573.5f);

    menu = Menu::create(play, characters, music, exit, setting, nullptr);
    menu->setPosition(0, 0);
    menu->setEnabled(false);
    menu->runAction(Sequence::create(FadeOut::create(0), DelayTime::create(4.5f), FadeIn::create(1), 
        CallFuncN::create([=](Node*){
            menu->setEnabled(true);
        }),
        nullptr));
    addChild(menu);

    // 返回菜单
    auto backItem = MenuItemSprite::create(back1, back2, CC_CALLBACK_1(MainSceneFirst::menuBackCallBack, this));
    backItem->setPosition(52.5f, 640 - 50);
    back = Menu::create(backItem, nullptr);
    back->setEnabled(false);
    back->setPosition(0, 0);
    back->runAction(FadeOut::create(0));
    addChild(back);
    huolong = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/hl.png"));
    star = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/xx.png"));
    sensen = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/ss.png"));
    zijian = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/zj.png"));
    huolong->retain();
    sensen->retain();
    zijian->retain();
    star->retain();

    return true;
}

void MainSceneFirst::menuBackCallBack(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");

    back->runAction(FadeOut::create(0.5));
    back->setEnabled(false);
    huolong->stopAllActions();
    sensen->stopAllActions();
    zijian->stopAllActions();
    star->stopAllActions();

    huolong->runAction(FadeOut::create(0.5f));
    sensen->runAction(FadeOut::create(0.5f));
    zijian->runAction(FadeOut::create(0.5f));
    star->runAction(FadeOut::create(0.5f));

    scheduleOnce([=](float){
        menu->runAction(FadeIn::create(0.5));
        characterXZJ->runAction(FadeIn::create(0.5));
        wordAmazingGrave->runAction(FadeIn::create(0.5));
        copyRight->runAction(FadeOut::create(0.5));
        menu->setEnabled(true);
        this->unscheduleUpdate();
        huolong->removeFromParent();
        sensen->removeFromParent();
        zijian->removeFromParent();
        star->removeFromParent();

    }, 0.5, "backToScene");

}

void MainSceneFirst::menuCloseCallback(Ref* pSender)
{
    menu->runAction(FadeOut::create(0.5));
    characterXZJ->runAction(FadeOut::create(0.5));
    wordAmazingGrave->runAction(FadeOut::create(0.5));
    scheduleOnce([=](float){
        auto sure = Label::create("Bye", "fonts/MFYaYuan_Noncommercial-Regular.ttf", 38);
        addChild(sure);
        sure->setPosition(960 / 2, 640 / 2);
        scheduleOnce([=](float){
            Director::getInstance()->end();
        }, 1, "heheda");
    }, 0.5, "exit");
}

void MainSceneFirst::menuPlayCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");
    extern enum _nowScene nowScene;
    nowScene = Idle;
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, GraveMainScene::createScene()));
}

void MainSceneFirst::menuCharactersCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");

    back->runAction(FadeIn::create(0.5));
    back->setEnabled(true);

    menu->stopAllActions();
    characterXZJ->stopAllActions();
    wordAmazingGrave->stopAllActions();

    menu->runAction(FadeOut::create(0.5));
    menu->setEnabled(false);
    characterXZJ->runAction(FadeOut::create(0.5));
    wordAmazingGrave->runAction(FadeOut::create(0.5));
    this->CharactersShow();

}

void MainSceneFirst::CharactersShow()
{
    //huolong = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/hl.png"));
    huolong->setPosition(visibleSize.width / 2, -visibleSize.height * 0.8f);
    addChild(huolong);
    huolong->setScale(0.9);
    //star = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/xx.png"));
    star->setPosition(visibleSize.width / 2, -visibleSize.height * 2.0f);
    addChild(star);
    star->setScale(0.9);
    //sensen = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/ss.png"));
    sensen->setPosition(visibleSize.width / 2, -visibleSize.height * 3.3f);
    addChild(sensen);
    sensen->setScale(0.9);
    //zijian = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Charcters/zj.png"));
    zijian->setPosition(visibleSize.width / 2, -visibleSize.height * 4.6f);
    addChild(zijian);
    zijian->setScale(0.9);

    wordAmazingGrave->setPosition(visibleSize.width / 2, -visibleSize.height * 5.34f);
    wordAmazingGrave->runAction(FadeIn::create(1));

    list = LabelTTF::create("Game Production Team\nNova\nzijian Chen\nzhaolong Zhang\nTsengkasing", "fonts/RTWSYueGoTrial-Regular.ttf", 56);
    list->setPosition(visibleSize.width / 2, -visibleSize.height * 5.8f);
    addChild(list);

    auto fade = Sequence::create(
        FadeOut::create(0), DelayTime::create(0.5f), FadeIn::create(2.0f),
        DelayTime::create(8.0f), FadeOut::create(1.0f), nullptr);

    huolong->runAction(fade);
    star->runAction(Sequence::create(DelayTime::create(7.0f), fade->clone(), nullptr));
    sensen->runAction(Sequence::create(DelayTime::create(14.0f), fade->clone(), nullptr));
    zijian->runAction(Sequence::create(DelayTime::create(20.0f), fade->clone(), nullptr));

    this->scheduleUpdate();

    return;
}

void MainSceneFirst::update(float delta)
{
    if (list->getPositionY() < visibleSize.height * 2.0f)
    {
        huolong->setPositionY(huolong->getPositionY() + 2);
        star->setPositionY(star->getPositionY() + 2);
        sensen->setPositionY(sensen->getPositionY() + 2);
        zijian->setPositionY(zijian->getPositionY() + 2);
        wordAmazingGrave->setPositionY(wordAmazingGrave->getPositionY() + 2);
        list->setPositionY(list->getPositionY() + 2);
    }
    else
    {
        this->unscheduleUpdate();
        this->removeAllChildren();
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainSceneFirst::createScene()));
    }

    return;
}

void MainSceneFirst::menuMusicCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");

    if (isBGMPlay)
    {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        isBGMPlay = false;
    }
    else
    {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        isBGMPlay = true;
    }
}

void MainSceneFirst::menuSettingsCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");
    menu->stopAllActions();
    characterXZJ->stopAllActions();
    wordAmazingGrave->stopAllActions();

    back->runAction(FadeIn::create(0.5));
    back->setEnabled(true);

    menu->runAction(FadeOut::create(0.5));
    characterXZJ->runAction(FadeOut::create(0.5));
    wordAmazingGrave->runAction(FadeOut::create(0.5));
    menu->setEnabled(false);

    scheduleOnce([=](float){
        copyRight->runAction(FadeIn::create(0.5));
        copyRight->setPosition(960 / 2, 640 / 2);
    }, 0.5, "copyright");

}