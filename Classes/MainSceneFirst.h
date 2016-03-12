#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MainSceneFirst : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();

    void menuCloseCallback(Ref* pSender);

    void menuPlayCallback(Ref* pSender);

    void menuCharactersCallback(Ref* pSender);

    void CharactersShow();

    void menuMusicCallback(Ref* pSender);

    void menuSettingsCallback(Ref* pSender);

    void menuBackCallBack(Ref* pSender);

    CREATE_FUNC(MainSceneFirst);

    void update(float delta);
private:
    Sprite* backGround;
    Sprite* wordAmazingGrave;
    Sprite* characterXZJ;
    Sprite* copyRight;

    bool isBGMPlay;

    Menu* menu;
    Menu* back;

    Size visibleSize;

    Sprite* huolong;
    Sprite* star;
    Sprite* sensen;
    Sprite* zijian;

    LabelTTF* list;
};