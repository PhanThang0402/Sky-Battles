#include "COMMON_FUNCTION_H.h"
#include "TextObject.h"
#include "BaseObject.h"

bool SDLCommonFunc::checkFocus(const int& x, const int& y,const SDL_Rect& rect) 
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
	g_menu_img = LoadImage("start_img.png");
	if (g_menu_img == NULL)
	{
		return 1;
	}
	const int menuItems = 2;
	SDL_Rect pos_item_arr[menuItems];

	pos_item_arr[0].x = SCREEN_WIDGHT * 0.5 - 100;
	pos_item_arr[0].y = SCREEN_HEGIHT * 0.5;

	pos_item_arr[1].x = SCREEN_WIDGHT * 0.5 - 100;
	pos_item_arr[1].y = SCREEN_HEGIHT * 0.5 + 80;

	TextObject Text_Menu[menuItems];
	Text_Menu[0].setText("Play Game");
	Text_Menu[0].setTextColor(TextObject::black);
	Text_Menu[0].SetRect(pos_item_arr[0].x, pos_item_arr[0].y);

	Text_Menu[1].setText("Quit Game");
	Text_Menu[1].setTextColor(TextObject::black);
	Text_Menu[1].SetRect(pos_item_arr[1].x, pos_item_arr[1].y);
	 

	SDL_Event menu_event;
	int x_menu = 0; //toa do chuot
	int y_menu = 0;
	while (true)
	{
		SDLCommonFunc::ApplySurface(g_menu_img, des, 0, 0);
		for (int i = 0; i < menuItems; i++)
		{
			Text_Menu[i].GameText(font, des);

		}
		while (SDL_PollEvent(&menu_event))
		{
			switch (menu_event.type)
			{
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEBUTTONDOWN:
			{
				x_menu = menu_event.button.x; // toa do click chuot
				y_menu = menu_event.button.y;

				for (int i = 0; i < menuItems; i++)
				{
					if (checkFocus(x_menu, y_menu, Text_Menu[i].GetRect()))
					{
						return i;
					}
				}
			}
			case SDL_KEYDOWN:
			{
				if (menu_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 1;
				}
			}
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	return 1;

}


SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path) {     ////hàm nhận tên của ảnh, đọc ảnh và trả về kiểu SDL_Surface
	SDL_Surface* load_image = NULL;                          // SDL_Surface là kieu du lieu de chua anh
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);      //Chuyển đổi ảnh nhận được sang định dạng hiển thị.
		SDL_FreeSurface(load_image);                          //dữ liệu đã được đưa vào optimize_image nên load_image không cần nữa, ta giải phóng load_image
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0, 0);    // xoa phong 
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)     //show anh
{
	SDL_Rect offset;    //SDL_Rect là một kiểu dữ liệu đại diện cho một hình chữ nhật gom x ,y ,h, w
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset); //tải ảnh vào screen

	return offset;
}

void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y) // show clip
{
	SDL_Rect offset; ////SDL_Rect là một kiểu dữ liệu đại diện cho một hình chữ nhật gom x ,y ,h, w
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset); //tải ảnh vào screen
}

void SDLCommonFunc::Cleanup()                                  //clear man hinh
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_background);
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2) //check va cham
{
	int left_a = object_1.x;
	int right_a = object_1.x + object_1.w;
	int top_a = object_1.y;
	int bottom_a = object_1.y + object_1.h;

	int left_b = object_2.x;
	int right_b = object_2.x + object_2.w;
	int top_b = object_2.y;
	int bottom_b = object_2.y + object_2.h;

	// TH1 size object1 < size object2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	//TH2 size ob1 > size ob2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// TH 3 size ob1 = size ob2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;

}