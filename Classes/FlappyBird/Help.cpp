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
    
    // ����������
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = [=](Touch *t, Event *e){
        return true;
    };

    listener->onTouchEnded = [=](Touch *t, Event *e){

        // ��ʧ�궯���Ļص�����
        auto funcCallBack = CallFuncN::create(CC_CALLBACK_0(HelpLayer::FuncCallBack, this));

        // ɾ��������
        Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

        auto fade = FadeOut::create(0.5f);

        // ִ�ж�����Ȼ����ʧ
        tapImage->runAction(Sequence::create(fade, funcCallBack, nullptr));
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelpLayer::FuncCallBack()
{
    // ���ϰ�ɾ��
    removeFromParent();
}