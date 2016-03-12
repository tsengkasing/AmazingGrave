#include "SceneIntro.h"
#include "SceneMComplete.h"
#include "LevelInfo.h"
#include "json\document.h"
#include "json\rapidjson.h"

using namespace rapidjson;

Scene* SceneIntro::createScene()
{
	Scene* scene = Scene::create();
	auto layer = SceneIntro::create();
	scene->addChild(layer);
	return scene;
}

bool SceneIntro::init()
{
	if (!Layer::init())
	{
		return false;
	}

    // 从JSON读取中文显示的文字
    ssize_t size;
    unsigned char* ch = FileUtils::getInstance()->getFileData("SceneInto.json", "r", &size);
    std::string data = std::string((const char*)ch, size);

    Document doc;
    doc.Parse<0>(data.c_str());

    if (doc.HasParseError())
    {
        log("GetParseError%s\n", doc.GetParseError());
    }

    // 显示三句话
    rapidjson::Value& valObj1 = doc["Tag1"];
    rapidjson::Value& valObj2 = doc["Tag2"];
    rapidjson::Value& valObj3 = doc["Tag3"];

	visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("Intro_wall.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 0);

	curtain = Sprite::create("Intro_curtain.png");
	curtain->setPosition(visibleSize.width / 2, -0.8f * visibleSize.height);
	this->addChild(curtain, 1);

	curtainFollow = Sprite::create("Intro_curtain.png");
	curtainFollow->setPosition(visibleSize.width / 2, -1.8f * visibleSize.height);
	this->addChild(curtainFollow, 1);
	
    auto caption1 = Label::create(valObj1.GetString(), "fonts/RTWSYueGoTrial-Regular.ttf", 32);
	caption1->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	curtain->addChild(caption1, 0);
    auto caption2 = Label::create(valObj2.GetString(), "fonts/RTWSYueGoTrial-Regular.ttf", 32);
	caption2->setPosition(visibleSize.width / 2, visibleSize.height - 200);
	curtain->addChild(caption2, 0);
    auto caption3 = Label::create(valObj3.GetString(), "fonts/RTWSYueGoTrial-Regular.ttf", 32);
	caption3->setPosition(visibleSize.width / 2, visibleSize.height - 300);
	curtain->addChild(caption3, 0);
	auto caption4 = Label::create("GO and OPEN THEM", "fonts/RTWSYueGoTrial-Regular.ttf", 32);
	caption4->setPosition(visibleSize.width / 2, visibleSize.height - 400);
	curtain->addChild(caption4, 0);

	auto start = Label::create("Start Adventure", "fonts/FFADMatro.ttf", 98); 
	start->setColor(Color3B(0xEE, 0, 0));
	start->setPosition(visibleSize.width / 2, visibleSize.height - 800);
	curtain->addChild(start, 1);
	
	auto handprintNormal = Sprite::create("handprint.png");  //手印
	auto handprintSelected = Sprite::create("handprint.png"); //手印按下
	handprintSelected->setScale(0.9f);

	auto handprint = MenuItemSprite::create(handprintNormal, handprintSelected, CC_CALLBACK_1(SceneIntro::Next, this)); 

	auto handMenu = Menu::create(handprint, NULL);
	handMenu->setPosition(visibleSize.width / 2, visibleSize.height - 900);
	curtain->addChild(handMenu);

    auto click = Label::create("Click...", "fonts/ARCHRISTY.ttf", 36);
    click->setPosition(visibleSize / 2);
    click->runAction(FadeOut::create(0));
    click->runAction(FadeIn::create(1));
    addChild(click);

	auto contro = EventListenerTouchOneByOne::create();
	contro->onTouchBegan = [=](Touch* touch, Event* event) {
		this->scheduleUpdate();
        click->runAction(FadeOut::create(2));
		return true;
	};
	
	contro->onTouchEnded = [=](Touch* touch, Event* event) {
		Director::getInstance()->getEventDispatcher()->removeEventListener(contro);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contro, this);

    // 创建一个星星粒子层装饰
    auto emitter1 = ParticleSystemQuad::create("star1.plist");
    emitter1->retain();
    auto batch = ParticleBatchNode::createWithTexture(emitter1->getTexture());
    batch->addChild(emitter1);
    emitter1->setPosition(visibleSize / 2);
    emitter1->release();
    addChild(batch);

	return true;
}

void SceneIntro::update(float delta)
{
	if (curtain->getPositionY() < 1.3f * visibleSize.height)
	{
		curtain->setPositionY(curtain->getPositionY() + 1.5f);
		curtainFollow->setPositionY(curtainFollow->getPositionY() + 1.5f);
	}
	else
	{
		this->unscheduleUpdate();
	}
	return;
}

void SceneIntro::Next(Ref* ref)
{
    extern enum _nowScene nowScene;
    nowScene = Grave;
    Director::getInstance()->popScene();
	return;
}