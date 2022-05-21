#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#define WIDHT_THREATS  80
#define HEIGHT_THREATS  55

const int UNDER_LIMIT_THREAT = 200;

#include "BaseObject.h"
#include "BulletObject.h"
#include "COMMON_FUNCTION_H.h"
#include "MainObject.h"
#include <vector>


class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();

	void HandleMove(const int& x_border, const int& y_border);           // di chuyen 
	void HandleInputAction(SDL_Event events);
	void set_x_val(const int& val) { x_val_ = val; }						// set vi tri 					
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void SetBulletList(std::vector<BulletObject*> bullet_list) { p_bullet_list = bullet_list; }    //tao list dan
	std::vector<BulletObject*> GetBulletList() const { return p_bullet_list; }

	void InitBullet(BulletObject* p_bullet);
	void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);    // ha`m ban dan, Gioi han cho phep cua vien dan

	void Reset(const int& xborder);
	void ResetBullet(BulletObject* p_bullet);

private:
	int x_val_;
	int y_val_;

	std::vector<BulletObject*> p_bullet_list;
};

#endif // !THREATS_OBJECT_H_
