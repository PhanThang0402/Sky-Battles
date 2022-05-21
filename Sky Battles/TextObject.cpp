#include "TextObject.h"

TextObject::TextObject()
{
	rect_.x = 500;
	rect_.y = 20;
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;
}
TextObject::~TextObject()
{

}
void TextObject::setTextColor(const int& type)
{
	if (type == Red)
	{
		SDL_Color color = { 255, 0, 0 };
		text_color_ = color;
	}
	else if (type == White)
	{
		SDL_Color color = { 255, 255, 255 };
		text_color_ = color;
	}
	else
	{
		SDL_Color color = { 0, 0, 0 };
		text_color_ = color;
	}
}

void TextObject::GameText(TTF_Font* font, SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font, string_text_.c_str(), text_color_); // tao ra doi tuong surface tu ky tu cho vao, mau sac
	Show(des);
}
