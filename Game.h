#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Zombie.h"
#include "screen.h"
#include "mother_clase.h"

using namespace sf;

class Game: public screen {
	
public:
	
	Game(RenderWindow *w);
	
	void update(RenderWindow *w, mother_clase &m1)override;
	
	void update_game(RenderWindow *w, mother_clase &m1);
	bool you_win(std::vector<Zombie> v, int zom_4, int created);
	int probability();
	Zombie create_zombie();
	void draw_gamewin(RenderWindow *w, Text t,Clock c1, Time t1, std::vector<Zombie> &v_zom);
	void draw_gameover(RenderWindow *w, Text t,Clock c1, Time t1, mother_clase &m1);
	bool game_over(Zombie z);
	bool impact(Sprite s, Sprite x);
	
	void load_lvls();	

	void inputbox(RenderWindow *w, mother_clase &m1,int puntaje);
	
	void show_quit(RenderWindow *w, mother_clase &m1);
	
	void registrar_tiempocreacion(float &tiem, int lvl_ac);
	
	void make_score(int wichzomb);
	
	void reset_vector( std::vector<Zombie> &v_zom);
	
private:
	
	int tamanio_vector;

	float tiempo_creacion;
	
	std::vector<int> niveles;		///contiene la cantidad de zombies
	
	bool g_change;
	int x;
	
	int puntuacion; ///llevara el puntaje que vaya consiguiendo el jugador
	
	complement c_game;
	
	bool finish_game;		///sirve para comprobar si el juego ha terminado
	bool aux_check;
	Music song;				///musica de fondo del juego
	Event e;						///registra los eventos 
	
	Hero hero1;
	
	Texture txt_back;	///textura y sprite del fondo del juego
	Sprite spr_back;
	
	Texture txt_quit;	///textura y sprite del cartel de salir
	Sprite spr_quit;
	
	Font f_over;			///fuente y texto del game over			
	Text t_over;
	
	Font flvl_act;			///fuente y texto del cartel de nivel actual			
	Text tlvl_act;
	
	Font f_win;			///fuente y texto del game win					
	Text t_win;
	
	Font f_puntaje;			///fuente y texto del puntaje				
	Text t_puntaje;
	
	Texture txt_zombies[6];			///texturas de los zombies
	
	std::vector<Zombie> v_zom;			///Vector que va a contener los zombies que se vayan creando
	int zombies_creados;				///cuenta la cantidad de zombies que se crean para comparar el tamaño del vector
	int zombi_4_lvl;			///registra la cantidad de zombies que se crearan en el nivel
	int munition;
	int nivel_actual;			///contiene el nivel actual para poder moverse por el vector de los niveles
	
	int aux_y;						///auxiliar para saber donde crear los zombies y que los sprites no se alteren

	Clock c1;		///sirven para tener un contador de tiempo
	Time t1;
	float aux_time;		///auxiliar que ayuda a comparar con el reloj c1
	
	int pro;		///lanza una probabilidad de que se cree un zombie
	
};

#endif
