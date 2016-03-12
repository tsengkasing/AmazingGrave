#include "SceneMComplete.h"
#include "SimpleAudioEngine.h"

Scene* SceneMComplete::createScene(int Game)
{
    Scene* scene = Scene::create();
    auto layer = SceneMComplete::create();
    scene->addChild(layer);
    layer->GameScene = Game;
    layer->ShowKey();
    return scene;
}

bool SceneMComplete::init()
{
    if (!Layer::init())
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGM.mp3", true);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hit.plist");
    visibleSize = Director::getInstance()->getVisibleSize();

    musicContro = SimpleAudioEngine::getInstance(); //获取实例用于播放音效
    musicContro->preloadEffect("7.mp3"); //预加载音效
    musicContro->preloadEffect("8.mp3"); //预加载音效

    xx = Sprite::create("xxG.png");
    xx->setPosition(visibleSize / 2);
    xx->setVisible(false);
    this->addChild(xx, 0);
    ss = Sprite::create("ssG.png");
    ss->setPosition(visibleSize / 2);
    ss->setVisible(false);
    this->addChild(ss, 0);
    zj = Sprite::create("hlG.png");
    zj->setPosition(visibleSize / 2);
    zj->setVisible(false);
    this->addChild(zj, 0);
    musicContro->playEffect("8.mp3"); //播放音效

    auto key = Sprite::create("bulletSize.png"); //钥匙

    auto keyItem = MenuItemSprite::create(key, key, CC_CALLBACK_1(SceneMComplete::Next, this)); //钥匙 菜单
    keyMenu = Menu::create(keyItem, nullptr);
    this->addChild(keyMenu);
    keyMenu->setEnabled(false);

    scheduleOnce([=](float){
        keyMenu->runAction(FadeOut::create(1.0f)); //钥匙消失
        scheduleOnce([=](float){
            Director::getInstance()->popScene();
        }, 3, "popToMainScene");
    }, 4.5, "next");

    //光点动画
    Vector<SpriteFrame *>loadVector;
    char name[16];

    for (int i = 1; i <= 6; i++)
    {
        sprintf(name, "hurt (%d).png", i);
        loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    }

    auto sprite = Sprite::create();
    sprite->setPosition(keyItem->getContentSize() / 2);
    keyItem->addChild(sprite);
    sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 15.0f))));

    return true;
}

void SceneMComplete::ShowKey()
{
    float pos[3] = { 0.25f, 0.5f, 0.728f };

    //选择棺材
    switch (GameScene)
    {
    case 1:
        xx->setVisible(true);
        keyMenu->setPosition(visibleSize.width * pos[0], visibleSize.height * 0.2f); break;
    case 2:
        ss->setVisible(true);
        keyMenu->setPosition(visibleSize.width * pos[1], visibleSize.height * 0.2f); break;
    case 3:
        zj->setVisible(true);
        keyMenu->setPosition(visibleSize.width * pos[2], visibleSize.height * 0.2f); break;
    default:
        return;
    }

    //淡入上移动画
    keyMenu->runAction(Sequence::create(FadeOut::create(0.001f), Spawn::create(
        FadeIn::create(2.3f),
        MoveTo::create(4.3f, Vec2(visibleSize.width * pos[GameScene - 1], visibleSize.height * 0.85f))),
        nullptr));

    return;
}

void SceneMComplete::Next(Ref* ref)
{
    auto fade = FadeOut::create(1.0f);
    keyMenu->runAction(fade); //钥匙消失

    keyMenu->runAction(Sequence::create(DelayTime::create(3.0f), 
        CallFuncN::create([=](Node*){
        Director::getInstance()->popScene();
        }), nullptr));
    //scheduleOnce([=](float){
    //}, 3.0f, "popToMainScene");

    return;
}