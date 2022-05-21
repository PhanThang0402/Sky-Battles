#ifndef MAIN_OBJECT_H_            //dinh nghia
#define MAIN_OBJECT_H_

#include "COMMON_FUNCTION_H.h"
#include "BaseObject.h"
#include <vector>
#include "BulletObject.h"


#define  WIDTH_MAIN_OBJECT 77
#define  HEIGTH_MAIN_OBJECT 52



class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();


	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);      // hanh dong cua main
	void HandleMove();								// di chuyen main

	void SetBulletList(std::vector<BulletObject*> bullet_list) { p_bullet_list = bullet_list; }   // tao list cac vien dan
	std::vector<BulletObject*> GetBulletList() const { return p_bullet_list; }
	void MakeBullet(SDL_Surface* g_screen);

	void RemoveBullet(const int& idx);              //xoa dan

private:
	int x_val_;
	int y_val_;

	std::vector<BulletObject*> p_bullet_list;
};


#endif // MAIN_OBJECT_H_
