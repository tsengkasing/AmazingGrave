#pragma once

#include "cocos2d.h"

USING_NS_CC;

class LoadScene : public Layer
{
public:
    // 常规创建
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(LoadScene);

    void LoadingDone();
private:
    // 用来设置文件名称的
    char name[20];
};