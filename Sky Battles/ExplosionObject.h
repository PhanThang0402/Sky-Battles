
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "BaseObject.h"
#include "COMMON_FUNCTION_H.h"

const int EXP_WIGHT = 165;
const int EXP_HEIGHT = 165;

class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();

	void set_clip();
	void set_frame(const int& fr) { frame = fr; }
	void showExp(SDL_Surface* des);

private:
	int frame;
	SDL_Rect clip_[4];

};


#endif // !EXPLOSION_H_
