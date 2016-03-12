#include"SceneAllComplete.h"
#include"SceneSelect.h"

Scene* SceneAllComplete::createScene(){
	auto scene = Scene::create();
	auto layer = SceneAllComplete::create();
	scene->addChild(layer);
	return scene;
}

bool SceneAllComplete::init(){
	if (!Layer::create()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create("bg2.png");
	background->setPosition(visibleSize / 2);

	this->nodegrid = NodeGrid::create();
	this->addChild(nodegrid);
	nodegrid->addChild(this->background);
	
	this->gate = Sprite::create("gate.jpg");
	this->gate->setScale(2.0);
	auto fadeOut = FadeOut::create(2.0f);
	this->gate->setPosition(visibleSize.width/2,visibleSize.height*0.4f);
	this->gate->runAction(fadeOut);
	this->gate->setVisible(false);
	this->addChild(this->gate);

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(SceneAllComplete::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(SceneAllComplete::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneAllComplete::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}	

bool SceneAllComplete::onTouchBegan(Touch* touch, Event* event){
	this->tuchnum++;
	if (this->touchable == true){
		Size gateSize = this->gate->getContentSize();
		Point gatePosition = this->gate->getPosition();
		Point touchPosition = touch->getLocation();
		if (touchPosition.x <= gatePosition.x + gateSize.width&&touchPosition.x >= gatePosition.x - gateSize.width){
			if (touchPosition.y <= gatePosition.y + gateSize.height&&touchPosition.y >= gatePosition.y - gateSize.height){
				transform();
			}
		}

	}
	return true;
}

void SceneAllComplete::onTouchEnded(Touch* touch, Event* event){
	if (this->tuchnum == 2){
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto shaky3D = CCShaky3D::create(3.0f, Size(32,32), 5, false);
		auto callbackFunc = [&](){
			fadeIn();
		};
		CallFunc* callFunc = CallFunc::create(callbackFunc);
		auto actions = Sequence::create(shaky3D, callFunc, NULL);
		this->nodegrid->runAction(actions);

		//auto fadeOut = FadeOut::create(2.0f);
		//this->background->runAction(fadeOut);

		
	}
	
}

void SceneAllComplete::fadeIn(){
	scheduleOnce(schedule_selector(SceneAllComplete::setTouch),2.1f);
	this->background->setVisible(false);
	auto fadeIn = FadeIn::create(2.0f);
	this->gate->setVisible(true);
	this->gate->runAction(fadeIn);
}

void SceneAllComplete::setTouch(float dt){
	this->touchable = true;
}

void SceneAllComplete::transform(){
	this->gate->removeFromParentAndCleanup(true);
	this->touchable = false;
}