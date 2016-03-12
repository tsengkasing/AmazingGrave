#include"SceneSelect.h"
#include"SimpleAudioEngine.h"
#include"SceneAllComplete.h"

Scene* SceneSelect::createScene(){
	auto scene = Scene::create();
	auto layer = SceneSelect::create();
	scene->addChild(layer);
	return scene;
}

bool SceneSelect::init(){
	if (!Layer::create()){
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();


	auto background1 = Sprite::create("bg2.png");
	background1->setPosition(visibleSize / 2);
	this->addChild(background1, 0);

	auto background2 = Sprite::create("SkullBarMain.png");
	background2->setPosition(visibleSize / 2);
	this->addChild(background2, 1);

	auto One = MenuItemImage::create(
		"Icon.png",
		"Icon.png",
		CC_CALLBACK_1(SceneSelect::menuSelectOneCallBack, this));

	auto Two = MenuItemImage::create(
		"Icon.png",
		"Icon.png",
		CC_CALLBACK_1(SceneSelect::menuSelectTwoCallBack, this));

	auto Three = MenuItemImage::create(
		"Icon.png",
		"Icon.png",
		CC_CALLBACK_1(SceneSelect::menuSelectThreeCallBack, this));

	auto menu = Menu::create(One, Two, Three, NULL);
	menu->alignItemsHorizontallyWithPadding(4 * 32);
	menu->setPosition(visibleSize.width / 2, visibleSize.height*0.8);
	this->addChild(menu, 2);






	return true;


}

void SceneSelect::menuSelectOneCallBack(Ref* pSender){
	Director::getInstance()->replaceScene(SceneAllComplete::createScene());
}

void SceneSelect::menuSelectTwoCallBack(Ref* pSender){

}

void SceneSelect::menuSelectThreeCallBack(Ref* pSender){

}