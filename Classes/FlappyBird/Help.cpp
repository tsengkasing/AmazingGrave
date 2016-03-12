#include "Help.h"

bool HelpLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    tapImage = Sprite::createWithSpriteFrameName("tap.png");
    tapImage->setPosition(visibleSize / 2);
    addChild(tapImage);
    
    // 创建侦听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = [=](Touch *t, Event *e){
        return true;
    };

    listener->onTouchEnded = [=](Touch *t, Event *e){

        // 消失完动画的回调函数
        auto funcCallBack = CallFuncN::create(CC_CALLBACK_0(HelpLayer::FuncCallBack, this));

        // 删除侦听器
        Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

        auto fade = FadeOut::create(0.5f);

        // 执行动画，然后消失
        tapImage->runAction(Sequence::create(fade, funcCallBack, nullptr));
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelpLayer::FuncCallBack()
{
    // 从老爸删除
    removeFromParent();
}