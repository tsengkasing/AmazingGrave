#include "FD_MonsterCreater.h"

FD_MonsterCreater::FD_MonsterCreater()
{
	showtime = 150.0f; // 初始化时间
	currenttime = 0.0f;
}

FD_MonsterCreater::~FD_MonsterCreater()
{
}

bool FD_MonsterCreater::init()
{
	this->scheduleUpdate(); //开启update函数
	return true;
}

void FD_MonsterCreater::update(float delta)
{
	if (monsterArray.empty())
	{
		return;
	}

	if (currenttime <= showtime) // 判断是否到出场时间
	{
		currenttime += 0.1f;
		for (auto monster : monsterArray)
		{
			monster->setVisible(false);
		}
		return;
	}

	for (auto monster : monsterArray)
	{
		if (monster->IsAlive())
		{
			monster->setPositionX(monster->getPositionX() - 6);
			if (monster->getPositionX() < 0)
			{
				monster->Hide();
			}

			else if (monster->IsCollideWithHero(pHero))
			{
				pHero->Hurt(monster->GetATK());
				monster->Hide();
			}
		}
		else
		{
			monster->Show();
		}

	}
	return;
}

void FD_MonsterCreater::SetMonsterPic(const std::string &filename) //设置怪物资源图片
{
	this->pic = filename;
	return;
}

void FD_MonsterCreater::BindHero(FD_Hero* hero) //绑定英雄以设置对英雄的攻击效果
{
	pHero = hero;
	return;
}

void FD_MonsterCreater::SetShowTime(float time) //设置出场时间
{
	this->showtime = time;
	return;
}

void FD_MonsterCreater::LetGo(int num, float scale, int atk) //初始化怪物形象和数量和攻击力并放出
{
	FD_Monster* monster = NULL;

	for (int i = 0; i < num; i++)
	{
		//创建怪物
		monster = FD_Monster::create();
		monster->BindSprite(Sprite::createWithSpriteFrameName(pic));
		monster->SetATK(atk);
		monster->setScale(scale);
		monster->Reset();

		this->addChild(monster);

		monsterArray.pushBack(monster);

	}
	return;
}