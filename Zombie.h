#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SFML/Graphics.hpp>
using namespace sf;


class Zombie {
public:
	Zombie(int que_zombie, Vector2f v2, int x, Texture txt_zombies[]);
	void move_zombie(Texture txt_zombies[]);
	
	void load_txt(int which, Vector2f v2, int x,Texture txt_zombies[]);
	void subtract_life();
	int get_lifes();
	float get_vel_mov();
	bool is_alive();
	void gen_zombie(int x);
	void change_txt(int x,Texture txt_zombies[]);
	Sprite get_zombie();
	
	int get_intzombie();
	
private:
	
	int numof_zomb;
	
	bool alive;
	float vel_mov;
	int life;
	Sprite spr_zomb;
//	Texture *txt_zomb_1;	///cargan las texturas de los zombies para simular el movimiento
//	Texture *txt_zomb_2;
//	Texture *txt_zomb_3;
//	
	int aux;
	int time;
	
	Clock clo2;		
	Time tim2;
	
};



#endif
