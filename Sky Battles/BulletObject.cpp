#include "BulletObject.h"

BulletObject::BulletObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	Bullet_type = NONE;

}
BulletObject::~BulletObject()
{

}
void BulletObject::HandleMove(const int& x_border, const int& y_border)   // ko sd SCRWidht,height vi ko t/m truong hop gap vat can
{
	rect_.x += x_val_;
	if (rect_.x > x_border)
	{
		is_move_ = false;   // ko show nua, dung show anh vien dan do
	}
}

void BulletObject::HandleMoveRightToLeft()
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		is_move_ = false;
	}
}

void BulletObject::HandleInputAction(SDL_Event events)
{

}



