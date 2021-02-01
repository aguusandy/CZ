#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics/RenderWindow.hpp>

class mother_clase;

using namespace sf;

class screen {
public:
	screen();
	
	virtual void update(RenderWindow *w, mother_clase &m1)=0;
	
	
private:
		
};

#endif

