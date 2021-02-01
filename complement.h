#ifndef COMPLEMENT_H
#define COMPLEMENT_H
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>
#include "Score.h"


struct data_window{
	float ancho;
	float alto;
	
};

using namespace sf;

class complement {
public:
	complement();
	static void save_resolution(bool re);
	static void get_resolution(Vector2f &aux);
	
	void save_name_player(std::string, int point);
	void load_names_player(std::vector<Score> &v_scores);
	
	
private:
	std::vector<Score> v_scoraux;
	
};

#endif

