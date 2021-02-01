#include "complement.h"
#include <fstream>
#include <iostream>
#include <cstring>


complement::complement() {
	
}

///guarda la resolucion, dependiendo del tipo de booleano que se le pase como parametro
void complement::save_resolution(bool resolut)
{
	data_window win1;

	if(resolut==false){
		win1.ancho=800;
				win1.alto=600;
		
	}
	else{
		win1.ancho=1024;
				win1.alto=700;
		
	}
	std::ofstream fout("data/resolution.xyz", std::ios::binary| std::ios::trunc);
			fout.write(reinterpret_cast<char*>(&win1), sizeof(win1));
					fout.close();

}

///recibe un vector 2f para poder pasar la resolucion guardada en el archivo binario
///que se usara para crear la ventana
void complement::get_resolution(Vector2f &v_aux)
{	
	data_window aux;
	
	std::ifstream fin("data/resolution.xyz", std::ios::binary| std::ios::in);
			fin.seekg(0);
					fin.read(reinterpret_cast<char*>(&aux), sizeof(aux));
	
	v_aux.x=float(aux.ancho);
			v_aux.y=float(aux.alto);
	
	
}

void complement::save_name_player(std::string s, int point)
{
	
	
	load_names_player(v_scoraux);			///copia los datos del binario en el vector de complement
	
	Score sco_aux;											///auxiliar para poder comparar el resultado del jugador
			sco_aux.set_name(s);						///las otras puntuaciones, si es mas alta que alguno de los primeros
					sco_aux.set_score(point);		///cinco, guarda los datos
	
	v_scoraux.push_back( sco_aux );
					
	sco_aux.sort_scores( v_scoraux );
	
	int size_vec = v_scoraux.size();
	
	std::ofstream fout("data/scores.xyz", std::ios::binary| std::ios::trunc);

	Score to_save; 	std::string name_plus;	///auxiliar para guardar todo el vector nuevamente al archiuo
	
	for(int i = 0; i < size_vec ; ++i)
	{
		to_save.set_score( v_scoraux[i].get_score() );
				name_plus = v_scoraux[i].get_name();
						to_save.set_name (	name_plus	);
								fout.write(reinterpret_cast<char*>(&to_save), sizeof(Score));
	}
	
	fout.close();
	
}


///se requiere un vector de la clase Score para poder copiar los datos del archivo
///y guardarlos directamente en el vector
void complement::load_names_player( std::vector<Score> &v_scores)
{
	Score s_aux;
	
	std::ifstream fin("data/scores.xyz", std::ios::binary|std::ios::in);
			fin.seekg(0);
			
	while( fin.read(reinterpret_cast<char*>(&s_aux), sizeof(Score)))
	{
				v_scores.push_back(s_aux);
	}
	fin.close();
	
	
}

