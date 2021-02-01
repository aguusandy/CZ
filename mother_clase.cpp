#include "mother_clase.h"
#include <fstream>
#include <iostream>
#include "screen.h"
#include "menu.h"


mother_clase::mother_clase() : finishall(false)
{
	get_reso();
	
	w = new RenderWindow(VideoMode(v_resolution.x, v_resolution.y),"College'Zombies");
	w->setFramerateLimit(60);							///limite de fps
	w->setMouseCursorVisible(false);				///ocultar el mouse	
	
	if(v_resolution.x == 800)		x=1;
	else		x=2;
		
	first = new menu(x);
} 

///consigue el struct que se guarda en binario para saber la resolucion establecida
///y poder iniciar la ventana
void mother_clase::get_reso()
{
	complement::get_resolution(v_resolution);
}


void mother_clase::run()
{
	while(w->isOpen())
	{
		first->update(w, *this);
		if (second) {
			delete first;
			first	= second;
			second = nullptr;
		}
	}	
}

void mother_clase::set_next(screen *s_next)
{
	second = s_next;
}

void mother_clase::set_bool(bool bo)
{
	finishall = bo;
}

bool mother_clase::get_bool()
{
	return finishall;
}

void mother_clase::change_resolution ( ) {
	get_reso();
	w->create(VideoMode(v_resolution.x, v_resolution.y),"College'Zombies");
	Vector2f v_center = v_resolution; 
	v_center.x/=2; v_center.y/=2;
	w->setView(sf::View(v_center,v_resolution));
}

