#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "complement.h"
#include "screen.h"
#include "Score.h"


using namespace sf;

class menu: public screen {

public:
	menu(int x1);
	
	void update(RenderWindow *w,mother_clase &m1)override;
	
	void show_start(RenderWindow *w,mother_clase &m1);
	void show_menu(RenderWindow *w,mother_clase &m1);
	
	void move_option_down(Sprite &spr_rect);
	void move_option_up(Sprite &spr_rect);
	float get_pos_op(Sprite spr_rect);
	
	void show_options(RenderWindow *w,mother_clase &m1);
	void wha_resolution(RenderWindow *w,mother_clase &m1);

	void show_scores(RenderWindow *w, mother_clase &m1);

	
private:
		
	int x;		///determina la resolucion de la ventana
	
	bool m_change;
	Color c;
	int que_eligio;
	Text t_menu1;
	Text t_menu2;
	Text t_menu3;
	
	Font f_menu1;
	Font f_menu2;
	
	
	Music song_menu;
	Event e_menu;
	
	Texture txt_rect;
	Sprite spr_rect;
	
	complement com;
	
	Texture txt_mback;
	Sprite spr_mback;
	
};

#endif

