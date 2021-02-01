#include "Zombie.h"
#include <SFML/Graphics.hpp>  
#include <iostream>
using namespace sf;

///el constructor pide un int para saber que tipo de zombie crear, este va a ser pasado
///por un rand para que sea aleatorio, y el vector 2f de posicion indica la posicion 
///en la que el sprite va a ser dibujado, el vector varia entre y =(320,5 y 470) y
///en x siempre sera x= 780.2

Zombie::Zombie(int que_zombie, Vector2f position, int x,Texture txt_zombies[])
	: aux(0), time(0),alive(true), numof_zomb(que_zombie)
{
	load_txt(que_zombie, position, x, txt_zombies);
	
}


///carga todas las texturas correspondientes, segun el int que se pase por referencia
///por un rand de 3 a 1 a si los zombies son aleatorios

void Zombie::load_txt(int one_zombie, Vector2f position, int x, Texture txt_zombies[])
{		
	gen_zombie(one_zombie);
	
	switch (one_zombie==1)
	{
	case 1:

		spr_zomb.setTexture(txt_zombies[0]); break;
			
	
	case 2:
	
		spr_zomb.setTexture(txt_zombies[0]);
		spr_zomb.setColor(Color::Green); break;
		
	
	case 3:
	
		spr_zomb.setTexture(txt_zombies[3]); break;
		
	}
	
	spr_zomb.setPosition(position.x, position.y);
	
	if(x==1)
	{
		spr_zomb.setScale(2.5,2.5);
	}
	if(x==2)
	{
		spr_zomb.setScale(3.0,3.0);
	}
	
}

///resta una vida al zombie por disparo, en caso de que haya colision

void Zombie::subtract_life()
{
	life--;
	if(life==0)
	{
		alive=false;
	}
}

///retorna las vidas para poder comparar

int Zombie::get_lifes()
{
	return life;
}

///retorna la velocidad de movimiento, para poder mover el sprite

float Zombie::get_vel_mov()
{
	return vel_mov;
}


///genera los valores de vidas y velocidad de movimiento del zombie, cambian en cuanto
///al tipo de zombie para que haya mas variedad

void Zombie::gen_zombie(int que_zom)
{
	switch (que_zom)
	{
	case 1: 
		life = 2;
		vel_mov = 10.5; break;
		
	case 2: 
		life = 1;
		vel_mov = 15.2; break;
		
	case 3: 
		life = 3;
		vel_mov = 7.1; break;
		
	}
}

///mueve el sprite del zombie que avanza en direccion al personaje cada 1 segundo
///cambia la textura y avanza la cantidad dependiendo del zombie

void Zombie::move_zombie(Texture txt_zombies[])
{	
	
	float tim_aux = 1;								
	
	tim2= clo2.getElapsedTime();					
	
	if(tim2.asSeconds() >= tim_aux){
		
		change_txt(aux, txt_zombies);
		spr_zomb.move(-get_vel_mov(),0);
		clo2.restart();
		
		if(aux==2){
			aux	=	0;
		}
		else{
			aux++;
		}
		
	}
	
}


///se encarga de cambiar las texturas en el sprite, para simular el movimiento
///la textura a cargar es indicada por el int, en este caso se usa el atributo aux

void Zombie::change_txt(int x,Texture txt_zombies[])
{
	if( numof_zomb == 1 or numof_zomb==2)
	{
		switch(x){										
	case 0:																	
		spr_zomb.setTexture(txt_zombies[0]);	
			if(numof_zomb==2)
				spr_zomb.setColor(Color::Green);
		break;
		
	case 1:	
		spr_zomb.setTexture(txt_zombies[1]);
		if(numof_zomb==2)
			spr_zomb.setColor(Color::Green);
		break;
		
	case 2:
		spr_zomb.setTexture(txt_zombies[2]);
		if(numof_zomb==2)
			spr_zomb.setColor(Color::Green);
		break;
		}
	}
	else if(numof_zomb==3)
	{
		switch(x){										
		case 0:																	
			spr_zomb.setTexture(txt_zombies[3]);		
			break;
			
		case 1:	
			spr_zomb.setTexture(txt_zombies[4]);
			break;
			
		case 2:
			spr_zomb.setTexture(txt_zombies[5]);
			break;
		}
	}
	
}


///retorna el sprite para poder hacer la colision

Sprite Zombie::get_zombie()
{
	return spr_zomb;			
}

bool Zombie::is_alive()
{
	return alive;
}

int Zombie::get_intzombie()
{
	return numof_zomb;
}
