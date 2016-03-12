#include "LoadScene.h"
#include "SimpleAudioEngine.h"
#include "TextReader.h"
#include "MainSceneFirst.h"
#include "FlappyBird\FirstGameLayer.h"
#include "ArrowShoot\MainScene.h"
#include "FinalWar\FinalWar.h"
#include "FastDash\FastDash.h"
#include "SceneMComplete.h"
#include "LevelSelect.h"

Scene *LoadScene::createScene()
{
    auto scene = Scene::create();

    auto layer = LoadScene::create();

    scene->addChild(layer);

    return scene;
}

bool LoadScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    TextReader::getInstance()->readFromJson();

    Size visibleSize = Director::getInstance()->getVisibleSize();

    // 加载游戏资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/Animation/Load.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/Animation/huolongHuan.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/UI/GameUI.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_blow.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_Hero.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_Monster.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_magic.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_MenuItem.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_hplabel.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Pictures.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AS_Zombie.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_Figure.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_Light.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Red.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Green.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Blue.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hit.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MagicCircle.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet4.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_hplabel.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_MenuItem.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_Figure.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_Monster.plist");
	Director::getInstance()->getTextureCache()->addImage("B_bg1.png");
	Director::getInstance()->getTextureCache()->addImage("B_bg2.png");
	Director::getInstance()->getTextureCache()->addImage("bulletSize.png");
	Director::getInstance()->getTextureCache()->addImage("F_pause.png");
    Director::getInstance()->getTextureCache()->addImage("SkullBarMain.png");
    Director::getInstance()->getTextureCache()->addImage("bg1.png");
    Director::getInstance()->getTextureCache()->addImage("mainBg.png");
    Director::getInstance()->getTextureCache()->addImage("Celling.png");
    Director::getInstance()->getTextureCache()->addImage("Drawings/hl_Origional.png");
    Director::getInstance()->getTextureCache()->addImage("End.png");
    Director::getInstance()->getTextureCache()->addImage("F_pause.png");
    Director::getInstance()->getTextureCache()->addImage("F_gamelayer.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("HPbar.plist");
    Director::getInstance()->getTextureCache()->addImage("Charcters/ss.png");
    Director::getInstance()->getTextureCache()->addImage("Charcters/zj.png");
    Director::getInstance()->getTextureCache()->addImage("Charcters/hl.png");
    Director::getInstance()->getTextureCache()->addImage("Charcters/xx.png");

    // 添加进度提条

    auto loadBarBk = Sprite::create("loadBarBk.png");
    loadBarBk->setPosition(visibleSize.width / 2, 193.7f);
    addChild(loadBarBk, 10);

    auto loadBarOk = ProgressTimer::create(Sprite::create("loadBarOk.png"));
    loadBarOk->setPercentage(1.0f);
    loadBarOk->setPosition(loadBarBk->getPosition());
    loadBarOk->setType(kCCProgressTimerTypeBar);
    loadBarOk->setBarChangeRate(Vec2(1, 0));
    loadBarOk->setMidpoint(Vec2(0, 0));
    addChild(loadBarOk, 10);

    auto loadingCHAR = Sprite::create("Animation/loadingCHAR.png");
    loadingCHAR->setPosition(visibleSize / 2);
    addChild(loadingCHAR, 11);

    auto action = ProgressTo::create(2, 100);
    loadBarOk->runAction(action);

    auto skullBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("SkullBarMain.png"));
    skullBar->setPosition(visibleSize / 2);
    addChild(skullBar, 10);

    Vector<SpriteFrame *>loadVector;
    for (int i = 1; i < 23; i++)
    {
        sprintf(name, "c (%d).png", i);
        loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    }

    auto animation = Animation::createWithSpriteFrames(loadVector, 3.0f / 22);

    auto animate = Animate::create(animation);

    auto repeat = Repeat::create(animate, 1);

    // 加载声音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/BGM.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/sfx_point.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/sfx_wing.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/click.mp3");

    // 加载结束就回调一个函数
    auto callBack = CallFunc::create(CC_CALLBACK_0(LoadScene::LoadingDone, this));

    auto sequence = Sequence::create(repeat, callBack, nullptr);
    auto whiteSprite = LayerColor::create(Color4B(255, 255, 255, 255));
    addChild(whiteSprite);
    // 算是第一个画面了，先加载之
    auto loadingSprite = Sprite::createWithSpriteFrameName("c (1).png");

    loadingSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);

    addChild(loadingSprite);

    loadingSprite->runAction(sequence);

    loadingSprite->setScale(0.6f);

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGM.mp3", true);


    return true;
}

void LoadScene::LoadingDone()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1, /*LevelSelect*/MainSceneFirst/*MainScene*//*FirstGameLayer*//*FinalWar*//*SceneMComplete*//*FastDash*/::createScene()));
}