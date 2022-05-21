#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#define WIDHT_BULLET1 35
#define HEIGHT_BULLET1 20

#define WIDHT_BULLET2 35
#define HEIGHT_BULLET2 20

#define WIDHT_BULLETTHREAT1 60
#define HEIGHT_BULLETTHREAT1 30


#include "BaseObject.h"
#include "COMMON_FUNCTION_H.h"

class BulletObject : public BaseObject
{
public:
	enum BulletType          //kiểu dữ liệu cố định, chỉ cho phép biến nhận số số giá trị nhất định nào đó.
	{
		NONE = 0,
		BULLET1 = 1,
		BULLET2 = 2,
		BULLETthreat1 = 3
	};
	BulletObject();
	~BulletObject();
	void HandleInputAction(SDL_Event events);
	void HandleMove(const int& x_border, const int& y_border);              // ko sd WIDGHT SCR vi ko tm truong hop xay ra va cham
	void HandleMoveRightToLeft();                                           //  bullet di chuyen tu phai sang trai

	int get_type() const { return Bullet_type; }								// lay dan
	void set_type(const int& type) { Bullet_type = type; }						// lay kieu dan

	bool get_is_move() const { return is_move_; }								//ktra xem dan co tm ko
	void set_is_move(bool is_move) { is_move_ = is_move; }						// lay gia tri true or false
	void SetWightHeight(const int& wight, const int& height) { rect_.w = wight, rect_.h = height; }  // set size bullet

	void set_x_val(const int& val) { x_val_ = val; }
	void set_y_val(const int& val) { y_val_ = val; }

	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }


private:
	int x_val_;
	int y_val_;
	bool is_move_;
	int Bullet_type;

};
#endif // !BULLET_OBJECT_H_
