#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "mother_clase.h"
#include "Score.h"
#include <iostream>
#include <vector>
#include <fstream>


using namespace sf;

int main(int argc, char *argv[]){
	
	std::srand(time(NULL));
	
	mother_clase m1;
	
	while(m1.get_bool() == false)
		m1.run();

		
	return 0;
}

