#pragma once

#include "TextReader.h"
#include "cocos2d.h"

USING_NS_CC;

class StoryPlayer : public LayerColor
{
public:
    static StoryPlayer* getInstance();

    void playStory(int startTag, int endTag, Node* scene);

    virtual bool init(Node* scene);

    void imageSetter(Node* player, int tag);
private:
    int tagID;		//������
    int tagIndex;	//��������
    
    Size visibleSize;

    Sprite* chatBg;
    LabelTTF* m_pName;
    LabelTTF* m_pContext;
};