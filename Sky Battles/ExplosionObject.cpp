#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{

}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIGHT;
	clip_[0].h = EXP_HEIGHT;

	clip_[1].x = EXP_HEIGHT;
	clip_[1].y = 0;
	clip_[1].w = EXP_WIGHT;
	clip_[1].h = EXP_HEIGHT;

	clip_[2].x = EXP_HEIGHT * 2;
	clip_[2].y = 0;
	clip_[2].w = EXP_WIGHT;
	clip_[2].h = EXP_HEIGHT;

	clip_[3].x = EXP_HEIGHT * 3;
	clip_[3].y = 0;
	clip_[3].w = EXP_WIGHT;
	clip_[3].h = EXP_HEIGHT;

}

void ExplosionObject::showExp(SDL_Surface* des)
{
	if (frame >= 4)
	{
		frame = 0;
	}

	SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip_[frame], rect_.x, rect_.y);


}