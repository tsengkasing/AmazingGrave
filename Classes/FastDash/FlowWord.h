#ifndef __FLOWWORD_H__
#define __FLOWWORD_H__

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public Node
{
public:
	bool init();
	CREATE_FUNC(FlowWord);
public:
	void ShowWord(bool sign, int num, float duration, int blinks, Point pos, cocos2d::Color3B & color);
	void ShowText(const char* format, float duration, int blinks, Point pos, cocos2d::Color3B & color);
private:
	LabelTTF* textLabel;

	void FlowEnd();
};


#endif