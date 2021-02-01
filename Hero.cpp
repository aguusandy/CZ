#include "Hero.h"
#include <string>
#include <iostream>


Hero::Hero() 				
	: col_letter_ammo(Color::Black)	
{
		
	txt_mira.loadFromFile("sprites/mirita.png");	
	spr_mira.setTexture(txt_mira);
	spr_mira.setScale(2,2);
	spr_mira.setPosition( 600,400);
	
	shot.loadFromFile("sound/pistol.wav");	
	disp.setBuffer(shot);
	disp.setVolume(20);
	
	buffer_rel_gun.loadFromFile("sound/pistol_empty.wav");	
	sound_empty.setBuffer(buffer_rel_gun);
	sound_empty.setVolume(25);
	
	font_mun.loadFromFile("fonts/letra_muni.ttf");		
	tx_mun.setFont(font_mun);
	tx_mun.setString(std::to_string(get_ammo()));
	tx_mun.setColor(col_letter_ammo);
	
		
	
}

void Hero::setInfo(int munition, int x)		///int x se pasa por referencia dependiendo de la resolucion de la pantalla
{																					///si es 1, la res es 800,600 y si es 2 es 1024,700
	ammo = munition;
	if(x==1){
		tx_mun.setPosition(190,8);
		
	}
	if(x==2){
		tx_mun.setScale(1.3,1.3);
		tx_mun.setPosition(250,20);
	}
	
}

///dibuja todo lo que corresponde al heroe, se pasa la ventana por referencia
///en vez de retornar los sprites, ya que toma menos tiempo dibujar desde la clase sobre
///la ventana a pasar todos los sprites y dibujarlo en el main

void Hero::draw_all(RenderWindow *w)
{	
	tx_mun.setString(std::to_string(get_ammo()));
	w->draw(spr_mira);
	w->draw(tx_mun);
}


///resta una municion por cada disparo, el arma posee 6 municiones, y si llega
///a cero, esta se recarga en un lapso de 2 segundos, donde no se puede disparar

void Hero::subtract_ammo()
{	
	clo1.restart();
	
	tim1 = clo1.getElapsedTime();
	
	if(ammo>=1){
		
		--ammo;
		
		disp.play();
	}
	
	if(ammo == 0){ 
		sound_empty.play();
		
	}
}


///retorna la cantidad de municion

int Hero::get_ammo()
{
	return ammo;
}



///todas estas funciones corresponden al movimiento de la mira, que sera indicado
///por el tipo de evento, segun se presione cierta tecla
void Hero::move_down(){
	spr_mira.move(0,5);
}

void Hero::move_up(){
	spr_mira.move(0,-5);
}

void Hero::move_left(){
	spr_mira.move(-5,0);
}

void Hero::move_right(){
	spr_mira.move(5,0);
}

void Hero::do_shot(){
	
	subtract_ammo();
	
}	


///retorna solo el sprite de la mira, para comparar con las de los zombies
///y saber si hubo colisiones
Sprite Hero::get_mira()
{
	return spr_mira;
}
