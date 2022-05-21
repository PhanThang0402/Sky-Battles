#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "COMMON_FUNCTION_H.h"


class BaseObject
{
public:   // de public thi ke thua dc
	BaseObject(); //contructor
	~BaseObject();  //detructor
	void Show(SDL_Surface* des);        //show
	bool LoadImg(const char* file_name);

	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }   // dat position
	SDL_Rect GetRect() const { return rect_; }            //lay position
	SDL_Surface* GetObject() { return p_object_; }

protected:
	SDL_Rect rect_;
	SDL_Surface* p_object_;

};

#endif // !BASE_OBJECT_H_
