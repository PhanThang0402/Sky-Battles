#include "COMMON_FUNCTION_H.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "BulletObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#undef main

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_text_menu = NULL;
bool init() {                                   //khởi tạo các thuộc tính ban đầu.
	
	// khoi tao SDL, man hinh;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDGHT, SCREEN_HEGIHT, SCREEN_BBP, SDL_SWSURFACE);  //định dạng màn hình được hiển thị với (chiều rộng)x(chiều dài), pixel, và Uint32 flags

	if (g_screen == NULL)
		return false;


	// khoi tao font
	if (TTF_Init() == -1)     
	{
		return false;
	}

	g_font_text_menu = TTF_OpenFont("Lobster-Regular.ttf", 50); // load font,size
	g_font_text = TTF_OpenFont("Lobster-Regular.ttf", 20); // load font,size
	if (g_font_text == NULL || g_font_text_menu == NULL)
	{
		return false; 
	}
	


	// khoi tao am thanh
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return false;
	g_sound_bullet[0] = Mix_LoadWAV("voice_bullet1.wav");
	g_sound_bullet[1] = Mix_LoadWAV("voice_bullet2.wav");
	g_sound_explosion[0] = Mix_LoadWAV("voice_main.wav");
	g_sound_explosion[1] = Mix_LoadWAV("voice_die.wav");
	g_music = Mix_LoadMUS("abc.wav");

	if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL ||
		g_sound_explosion[0] == NULL || g_sound_explosion[1] == NULL||
		g_music == NULL)
	{
		return false;
	}


	return true;
}



int main(int arc, char* argv[]) {

	bool is_run_screen = true;

	int bkgn_x = 0;
	bool is_quit = false;

	if (init() == false)
	{
		return 0;
	}

	g_background = SDLCommonFunc::LoadImage("bk3.jpg");
	if (g_background == NULL)
	{
		return 0;
	}


	// Font 
	TextObject score_game;
	score_game.setTextColor(TextObject::White);

	TextObject time_game;
	time_game.setTextColor(TextObject::White);


	// MainObject
	MainObject plane_object;
	plane_object.SetRect(100, 200);
	bool ret = plane_object.LoadImg("plane.png");
	if (!ret)
	{
		return 0;
	}
	plane_object.Show(g_screen);



	// explosion object
	ExplosionObject exp_main;
	ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clip();
	if (ret == false)
		return 0;
	ExplosionObject exp_threat;
	ret = exp_threat.LoadImg("exp.png");
	exp_threat.set_clip();
	if (ret == false)
		return 0;


	// ThreatsObject
	ThreatsObject* p_threats = new ThreatsObject[NUM_THREATS];        // list gom 3 monsters

	for (int t = 0; t < NUM_THREATS; t++)
	{
		ThreatsObject* p_threat = p_threats + t;
		if (p_threat != NULL)
		{
			ret = p_threat->LoadImg("threat1.png");
			if (ret == false)
			{
				delete[] p_threats;
				SDLCommonFunc::Cleanup();
				SDL_Quit();
				return 0;
			}

			int rand_y = rand() % 400;
			if (rand_y > SCREEN_HEGIHT - 200)
			{
				rand_y = SCREEN_HEGIHT * 0.5;
			}
			p_threat->SetRect(SCREEN_WIDGHT + t * 300, rand_y);   // +t*300 de monster ko xuat hien cung thoi diem

			p_threat->set_x_val(5);
		}



		BulletObject* p_bullet = new BulletObject();      // lay dan cho threats
		p_threat->InitBullet(p_bullet);
	}

	int score_val = 0;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text_menu);
	if (ret_menu == 1)
	{
		is_quit = true;
	}
	Mix_PlayMusic(g_music, -1);

	while (!is_quit)
	{
		
		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			plane_object.HandleInputAction(g_even, g_sound_bullet);  // control main

		}

		if (is_run_screen == true)
		{
			bkgn_x -= 2;
			if (bkgn_x <= -(WIDHT_BACKGROUND - SCREEN_WIDGHT))     // 3 phan cua background;
			{
				bkgn_x = 0;
			}
			else
			{
				SDLCommonFunc::ApplySurface(g_background, g_screen, bkgn_x, 0);
			}
		}


		//Implement main object
		plane_object.HandleMove();
		plane_object.Show(g_screen);
		plane_object.MakeBullet(g_screen);


		//Implement threats object
		for (int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatsObject* p_threat = p_threats + tt;
			if (p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDGHT, SCREEN_HEGIHT);
				p_threat->Show(g_screen);
				p_threat->MakeBullet(g_screen, SCREEN_WIDGHT, SCREEN_HEGIHT);

				// check collision main and threats;
				bool is_col1 = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
				if (is_col1)
				{
					Mix_PlayChannel(-1, g_sound_explosion[0], 0);
					for (int exp = 0; exp < 4; exp++)   // hieu ung explosion
					{
						int x_position = plane_object.GetRect().x + plane_object.GetRect().w * 0.5 - EXP_WIGHT * 0.5;
						int y_position = plane_object.GetRect().y + plane_object.GetRect().h * 0.5 - EXP_HEIGHT * 0.5;

						exp_main.set_frame(exp);
						exp_main.SetRect(x_position, y_position);
						exp_main.showExp(g_screen);

						// update screen
						if (SDL_Flip(g_screen) == -1)
						{
							delete[] p_threats;
							SDLCommonFunc::Cleanup();
							SDL_Quit();
							return 0;
						}

					}

					if (MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)   // ct ket thuc
					{
						delete[] p_threats;
						SDLCommonFunc::Cleanup();
						SDL_Quit();
						return 1;
					}
				}

				//check collision main and threats bullet
				bool is_col2 = false;
				std::vector<BulletObject*> bullet_arr = p_threat->GetBulletList();
				for (int am = 0; am < bullet_arr.size(); am++)
				{
					BulletObject* p_bullet = bullet_arr.at(am);
					if (p_bullet != NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), plane_object.GetRect());
						if (ret_col == true)
						{
							Mix_PlayChannel(-1, g_sound_explosion[0], 0);
							for (int exp = 0; exp < 4; exp++)         // hieu ung explosion
							{
								int x_position = plane_object.GetRect().x + plane_object.GetRect().w * 0.5 - EXP_WIGHT * 0.5;
								int y_position = plane_object.GetRect().y + plane_object.GetRect().h * 0.5 - EXP_HEIGHT * 0.5;

								exp_main.set_frame(exp);
								exp_main.SetRect(x_position, y_position);
								exp_main.showExp(g_screen);

								//update screen
								if (SDL_Flip(g_screen) == -1)
								{
									delete[] p_threats;
									SDLCommonFunc::Cleanup();
									SDL_Quit();
									return 0;
								}
							}

							if (MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)   // ct ket thuc
							{

								SDLCommonFunc::Cleanup();
								SDL_Quit();
								return 1;
							}
						}
					}
				}




				// check collision main bullet with threats
				std::vector<BulletObject*> bullet_list = plane_object.GetBulletList();
				for (int im = 0; im < bullet_list.size(); im++)
				{
					BulletObject* p_bullet = bullet_list.at(im);
					if (p_bullet != NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
						if (ret_col)
						{
							Mix_PlayChannel(0, g_sound_explosion[1], 0);
							score_val++;
							for (int exp = 0; exp < 4; exp++)
							{
								int x_position = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - EXP_WIGHT * 0.5;
								int y_position = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - EXP_HEIGHT * 0.5;

								exp_threat.set_frame(exp);
								exp_threat.SetRect(x_position, y_position);
								exp_threat.showExp(g_screen);

								// update screen
								if (SDL_Flip(g_screen) == -1)
								{
									delete[] p_threats;
									SDLCommonFunc::Cleanup();
									SDL_Quit();
									return 0;
								}
							}
							p_threat->Reset(SCREEN_WIDGHT + tt * 300);
							plane_object.RemoveBullet(im);
							
						}
					}
				}
			}
		}

		//show time game
		std::string strTime = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		std::string time_str_val = std::to_string(time_val);
		strTime += time_str_val;  // them thoi gian
		time_game.setText(strTime);
		time_game.SetRect(SCREEN_WIDGHT - 150, 10);
		time_game.GameText(g_font_text, g_screen);


		//show scores val to screen
		std::string score_str_val = std::to_string(score_val);
		std::string strScore("Score: ");
		strScore += score_str_val;    // them diem so 1,2,3,4,..
		score_game.setText(strScore);
		score_game.GameText(g_font_text, g_screen);

		// update screen
		if (SDL_Flip(g_screen) == -1)
		{
			delete[] p_threats;
			SDLCommonFunc::Cleanup();
			SDL_Quit();
			return 0;
		}
	}
	

	delete[] p_threats;

	SDLCommonFunc::Cleanup();
	SDL_Quit();

	return 1;
}


