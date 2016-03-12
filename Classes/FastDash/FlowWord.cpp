#include "FlowWord.h"

bool FlowWord::init()
{
	return true;
}

void FlowWord::ShowText(const char* format, float duration, int blinks, Point pos, cocos2d::Color3B & color)
{
	textLabel = LabelTTF::create("", "fonts/ARCHRISTY.ttf", 108);
	textLabel->setString(String::createWithFormat(format)->getCString());
	textLabel->setColor(color);
	textLabel->setPosition(pos);
	this->addChild(textLabel);

	auto blinkAction = Blink::create(duration, blinks);

	auto callfunc = CallFunc::create(this, callfunc_selector(FlowWord::FlowEnd));

	auto actions = Sequence::create(blinkAction, callfunc, NULL);

	textLabel->runAction(actions);

	return;
}

void FlowWord::ShowWord(bool sign, int num,float duration, int blinks ,Point pos, cocos2d::Color3B & color)
{
	textLabel = LabelTTF::create("", "angryblue", 200);
	if (sign)
	{
		textLabel->setString(String::createWithFormat("+%d", num)->getCString());
	}
	else
	{
		textLabel->setString(String::createWithFormat("-%d", num)->getCString());
	}
	textLabel->setColor(color);
	textLabel->setPosition(pos);
	this->getParent()->addChild(textLabel);

	auto blinkAction = Blink::create(duration, blinks);

	auto callfunc = CallFunc::create(this, callfunc_selector(FlowWord::FlowEnd));

	auto actions = Sequence::create(blinkAction, callfunc, NULL);

	textLabel->runAction(actions);

	return;
}

void FlowWord::FlowEnd()
{
	textLabel->setVisible(false);
	textLabel->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
	return;
}