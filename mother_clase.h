#ifndef MOTHER_CLASE_H
#define MOTHER_CLASE_H
#include "complement.h"
#include "screen.h"

using namespace sf;



class mother_clase {
public:
	
	mother_clase();
	void get_reso();
	void run();
	
	void set_next(screen *s);
	
	void change(bool b);
	
	void set_bool(bool b);
	
	bool get_bool();
	
	void change_resolution();
	
	
protected:
	int x;
	
	bool finishall;
	
	Vector2f v_resolution;

	screen *first = nullptr;
	screen *second = nullptr;
	
	RenderWindow *w;

};

#endif
