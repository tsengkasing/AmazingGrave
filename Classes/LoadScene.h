#pragma once

#include "cocos2d.h"

USING_NS_CC;

class LoadScene : public Layer
{
public:
    // ���洴��
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(LoadScene);

    void LoadingDone();
private:
    // ���������ļ����Ƶ�
    char name[20];
};