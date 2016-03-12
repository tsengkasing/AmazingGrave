#include"MapScene.h"

int MapScene::step = 1;

Scene* MapScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = MapScene::create();
	scene->addChild(layer);
	return scene;
}

bool MapScene::init()
{
	if (!Layer::create())
	{
		return false;
	}
	/*¼ÓÔØÍßÆ¬µØÍ¼*/

	switch (this->step)
	{
	case 1:{
			   std::string file = "Map.tmx";
			   auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
			   this->map = TMXTiledMap::createWithXML(str->getCString(), "");
			   TMXLayer* obscatle= map->layerNamed("obscatle");
			   obscatle->setVisible(false);
			   this->objGroup = map->getObjectGroup("Object");
			   this->addChild(map, 0);
	}break;
	case 2:{
			   std::string file = "MapStep2.tmx";
			   auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
			   this->map = TMXTiledMap::createWithXML(str->getCString(), "");
			   TMXLayer* obscatle = map->layerNamed("obscatle");
			   obscatle->setVisible(false);
			   this->objGroup = map->getObjectGroup("Object"); 
			   this->addChild(map, 0);

	}break;
	case 3:{
			   std::string file = "MapStep3.tmx";
			   auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
			   this->map = TMXTiledMap::createWithXML(str->getCString(), "");
			   TMXLayer* obscatle = map->layerNamed("obscatle");
			   obscatle->setVisible(false);
			   this->objGroup = map->getObjectGroup("Object");
			   this->addChild(map, 0);

	}break;
	default:
		break;
	}

	
	
	return true;
}

TMXObjectGroup* MapScene::getObjectGroup()
{
	return this->objGroup;
}

TMXTiledMap* MapScene::getMap()
{
	return this->map;
}