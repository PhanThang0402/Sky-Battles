#include "ThreatsObject.h"
#include "BulletObject.h"
#include "MainObject.h"
#include "COMMON_FUNCTION_H.h"

ThreatsObject::ThreatsObject()
{
	rect_.x = SCREEN_WIDGHT;
	rect_.y = SCREEN_HEGIHT * 0.5;
	rect_.w = WIDHT_THREATS;
	rect_.h = HEIGHT_THREATS;
	x_val_ = 0;
	y_val_ = 0;

}

ThreatsObject::~ThreatsObject()                        // giai phong vung nho 
{
	if (p_bullet_list.size() > 0)
	{
		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			BulletObject* p_bullet = p_bullet_list.at(i);
			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
		p_bullet_list.clear();
	}
}

void ThreatsObject::HandleInputAction(SDL_Event events)
{
	//to do
}

void ThreatsObject::HandleMove(const int& x_border, const int& y_border)      // di chuyen threat
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDGHT;        // di het man hinh quay lai di tiep;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEGIHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEGIHT * 0.5;
		}
		rect_.y = rand_y;
	}
}
void ThreatsObject::InitBullet(BulletObject* p_bullet)    // truyen 1 doi tuong bullet o ben ngoai vao

{
	if (p_bullet != NULL)
	{
		bool ret = p_bullet->LoadImg("BulletThreat2.png");     //doc anh
		if (ret == true)
		{
			p_bullet->set_is_move(true);    // cho phep di chuyen
			p_bullet->SetWightHeight(WIDHT_BULLETTHREAT1, HEIGHT_BULLETTHREAT1);
			p_bullet->set_type(BulletObject::BULLETthreat1);    // loai dan
			p_bullet->SetRect(rect_.x, rect_.y + 30);  // vi tri vien dan
			p_bullet->set_x_val(8);
			p_bullet_list.push_back(p_bullet);
			
		}
	}
}

void ThreatsObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_bullet_list.size(); i++)     //ktra list
	{
		BulletObject* p_bullet = p_bullet_list.at(i);
		if (p_bullet)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->HandleMoveRightToLeft();
				p_bullet->Show(des);

			}
			else      // khi vien dan di het, no quay lai vi tri monster
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x, rect_.y + 30);
			}
		}

	}
}

void ThreatsObject::Reset(const int& xborder)      // reset vi tri threat ve cuoi man hinh
{
	rect_.x = xborder;
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEGIHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEGIHT * 0.5;
	}
	rect_.y = rand_y;

	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list.at(i);
		if (p_bullet != NULL)
		{
			ResetBullet(p_bullet);

		}
	}
}

void ThreatsObject::ResetBullet(BulletObject* p_bullet)    // set vi tri vien dan
{
	p_bullet->SetRect(rect_.x, rect_.y + 30);
}


