#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


class Hero {
public:
	Hero();
	void Upgrade(RenderWindow *w);		///dibuja el sprite en la ventana
	
	void draw_all(RenderWindow *w);
	
	void setInfo(int munition, int x);
	
	void subtract_ammo();
	int get_ammo();
	
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void do_shot();
	
	Sprite get_mira();
	
private:
	Color col_letter_ammo;
	
	Clock clo1;		///calculan los tiempos de recarga
	Time tim1;
	
	Sprite spr_mira;
	Texture txt_mira;
	
	SoundBuffer shot;
	Sound disp;	
	
	SoundBuffer buffer_rel_gun;
	Sound sound_empty;	
	
	Font font_mun;
	Text tx_mun;
	
	
	int ammo;
	
};

#endif

