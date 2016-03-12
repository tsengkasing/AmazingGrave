#include "cocos2d.h"

USING_NS_CC;

class HelpLayer : public Layer
{
public:
    virtual bool init();

    CREATE_FUNC(HelpLayer);

    void FuncCallBack();
private:
    Sprite* tapImage;
};