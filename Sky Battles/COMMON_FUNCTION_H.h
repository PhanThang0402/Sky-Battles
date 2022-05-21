#ifndef COMMON_FUNCTION_H_       //dinh nghia
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int WIDHT_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDGHT = 1200;
const int SCREEN_HEGIHT = 600;
const int SCREEN_BBP = 32;
const int NUM_THREATS = 3;

static SDL_Surface* g_screen = NULL;   // vùng nhớ tồn tại theo vòng đời của chương trình. giá trị của những lần gọi trước đó được lưu lại
static SDL_Surface* g_background = NULL;
static SDL_Surface* g_menu_img = NULL;
static SDL_Event g_even;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_explosion[2];
static Mix_Music* g_music = NULL;



namespace SDLCommonFunc        // phan biet cac ham ben duoi voi cac ham khac trung ten
{
	SDL_Surface* LoadImage(std::string file_path);  ////hàm nhận tên của ảnh, đọc ảnh và trả về kiểu SDL_Surface
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);      // show anh 
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);  // show clip
	void Cleanup();
	bool CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2);  // ktra va cham
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool checkFocus(const int& x, const int& y, const SDL_Rect& rect);  // kiem tra vi tri mouse dang focus

}

#endif // !COMMON_FUNCTION_H
