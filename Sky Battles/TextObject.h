#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include "BaseObject.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class TextObject : public BaseObject
{
public:

	enum textColor
	{
		Red = 0,
		White = 1,
		black = 2

	};
	TextObject();
	~TextObject();

	void setText(const std::string& text) { string_text_ = text; }
	void setTextColor(const int& type);
	void GameText(TTF_Font* font, SDL_Surface* des);

private:
	std::string string_text_;
	SDL_Color text_color_;


};

#endif // !TEXT_OBJECT_H_

