#include "MainObject.h"
#include "BaseObject.h"
#include "COMMON_FUNCTION_H.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGTH_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}
MainObject::~MainObject()
{
	;
}
void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)                              // di chuyen main
		{
		case SDLK_UP:
			y_val_ -= HEIGTH_MAIN_OBJECT / 6;
			//todo
			break;
		case SDLK_DOWN:
			y_val_ += HEIGTH_MAIN_OBJECT / 6;
			//todo
			break;
		case SDLK_LEFT:
			x_val_ -= WIDTH_MAIN_OBJECT / 8;
			//todo
			break;
		case  SDLK_RIGHT:
			x_val_ += WIDTH_MAIN_OBJECT / 8;
			//todo
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)                            // xoa du anh khi nha? phim bam 
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ += HEIGTH_MAIN_OBJECT / 6;
			break;
		case SDLK_DOWN:
			y_val_ -= HEIGTH_MAIN_OBJECT / 6;
			//todo
			break;
		case SDLK_LEFT:
			x_val_ += WIDTH_MAIN_OBJECT / 8;
			//todo
			break;
		case  SDLK_RIGHT:
			x_val_ -= WIDTH_MAIN_OBJECT / 8;
			//todo
			break;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)                         // ban dan
	{
		BulletObject* p_bullet = new BulletObject();
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_bullet->SetWightHeight(WIDHT_BULLET1, HEIGHT_BULLET1);               // size bullet
			p_bullet->LoadImg("bullet1.png");									// 
			p_bullet->set_type(BulletObject::BULLET1);							// bullet type
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_bullet->SetWightHeight(WIDHT_BULLET2, HEIGHT_BULLET2);
			p_bullet->LoadImg("bullet2.png");
			p_bullet->set_type(BulletObject::BULLET2);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}

		p_bullet->SetRect(this->rect_.x + 65, this->rect_.y + 20);  // vi tri vien dan bat dau ban
		p_bullet->set_is_move(true);       //cho phep ban ra 
		p_bullet->set_x_val(20);             // speed bullet
		p_bullet_list.push_back(p_bullet);   // 1 list vien dan, bam 1 phat ra 1 vien

	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}
	else
	{

	}
}

void MainObject::MakeBullet(SDL_Surface* des)
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{

		BulletObject* p_bullet = p_bullet_list.at(i);

		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move())      // neu cho phep ban ra ( true )
			{

				p_bullet->Show(des);
				p_bullet->HandleMove(SCREEN_WIDGHT, SCREEN_HEGIHT);
			}
			else
			{
				if (p_bullet != NULL)
				{
					p_bullet_list.erase(p_bullet_list.begin() + i);   // tru di 1 dan
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}

	}
}

void MainObject::HandleMove()
{
	//TOdo
	rect_.x += x_val_;
	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDGHT)        // ngan ko cho main ra khoi SCR

	{
		rect_.x -= x_val_;
	}

	rect_.y += y_val_;
	if (rect_.y < 0 || rect_.y + HEIGTH_MAIN_OBJECT >SCREEN_HEGIHT - 150)
	{
		rect_.y -= y_val_;
	}


}


void MainObject::RemoveBullet(const int& idx)
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		if (idx < p_bullet_list.size())
		{
			BulletObject* p_bullet = p_bullet_list.at(idx);
			p_bullet_list.erase(p_bullet_list.begin() + idx);
			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}

}