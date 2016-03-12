#include "FD_MonsterCreater.h"

FD_MonsterCreater::FD_MonsterCreater()
{
	showtime = 150.0f; // ��ʼ��ʱ��
	currenttime = 0.0f;
}

FD_MonsterCreater::~FD_MonsterCreater()
{
}

bool FD_MonsterCreater::init()
{
	this->scheduleUpdate(); //����update����
	return true;
}

void FD_MonsterCreater::update(float delta)
{
	if (monsterArray.empty())
	{
		return;
	}

	if (currenttime <= showtime) // �ж��Ƿ񵽳���ʱ��
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

void FD_MonsterCreater::SetMonsterPic(const std::string &filename) //���ù�����ԴͼƬ
{
	this->pic = filename;
	return;
}

void FD_MonsterCreater::BindHero(FD_Hero* hero) //��Ӣ�������ö�Ӣ�۵Ĺ���Ч��
{
	pHero = hero;
	return;
}

void FD_MonsterCreater::SetShowTime(float time) //���ó���ʱ��
{
	this->showtime = time;
	return;
}

void FD_MonsterCreater::LetGo(int num, float scale, int atk) //��ʼ����������������͹��������ų�
{
	FD_Monster* monster = NULL;

	for (int i = 0; i < num; i++)
	{
		//��������
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