#include "Game.h"
#include "menu.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Score.h"


Game::Game(RenderWindow *w) : finish_game(false), aux_time(0), pro(0), g_change(false), aux_y(0), nivel_actual(0),puntuacion(0)
{
	load_lvls();
	
	song.openFromFile("sound/game_song.ogg");					///musica de fondo
			song.setVolume(70);
					song.setLoop(true);

	c1.restart();
			
	txt_zombies[0].loadFromFile("sprites/z1-1.png");
	txt_zombies[1].loadFromFile("sprites/z1-2.png");
	txt_zombies[2].loadFromFile("sprites/z1-3.png");
	txt_zombies[3].loadFromFile("sprites/z2-1.png");
	txt_zombies[4].loadFromFile("sprites/z2-2.png");
	txt_zombies[5].loadFromFile("sprites/z2-3.png");
	
	munition = 100;		///municion total durante el juego
	
	Vector2u resolution = w->getSize();
	
	if(resolution.y== 600 and resolution.x == 800){
		x=1;
		txt_back.loadFromFile("sprites/background1_1player.png");
	}
	else{
		x=2;
		txt_back.loadFromFile("sprites/background2_1player.png");
	}
	spr_back.setTexture(txt_back);
	
	///FUENTES Y TEXTOS
	
	///fuentes y textos del puntaje
	f_puntaje.loadFromFile("fonts/letra_muni.ttf");		
	t_puntaje.setFont(f_puntaje);
	t_puntaje.setString( std::to_string( puntuacion ));
	t_puntaje.setColor(Color::Black);
	
	///fuentes y textos del cartel de nivel actual
	flvl_act.loadFromFile("fonts/letra_muni.ttf");		
	tlvl_act.setFont(flvl_act);
	
	tlvl_act.setColor(Color::Black);
	
	///fuentes y textos del cartel de game over
	f_over.loadFromFile("fonts/letra_over.ttf");	
	t_over.setFont(f_over);
	t_over.setString("GAME OVER");
	t_over.setColor(Color::Red);
	
	///fuentes y textos del cartel de game win
	f_win.loadFromFile("fonts/letra_win.ttf");	
	t_win.setFont(f_win);
	t_win.setString("YOU WON");
	t_win.setFillColor(Color::Blue);
	
	///dependiendo de la resolucion las scalas seras distintas
	if(x==1)	///resolucion 800x600
	{
		t_over.setPosition(180,250);
		t_over.setScale(2.5,4.f);
		
		t_win.setPosition(180,350);
		t_win.setScale(3.f,3.5);
		
		t_puntaje.setPosition(190,50);
		
		tlvl_act.setPosition(300,10);
	}
	
	if(x==2)	///resolucion 1024x700
	{
		t_over.setPosition(260,350);
		t_over.setScale(2.5,4.f);
		
		t_win.setPosition(260,350);
		t_win.setScale(3.f,3.5);
		
		t_puntaje.setScale(1.3,1.3);
		t_puntaje.setPosition(250,65);
		
		tlvl_act.setScale(1.3,1.3);
		tlvl_act.setPosition(400,20);	
	}
	


	hero1.setInfo(munition, x);		///textura y sprites del heroe

}


void Game::update(RenderWindow *w,mother_clase &m1)
{
	
	while( nivel_actual < 10 and g_change==false)
	{
		update_game( w , m1 );
	}
	
}

void Game::update_game(RenderWindow *w,mother_clase &m1)
{
	
	registrar_tiempocreacion( tiempo_creacion , nivel_actual );		///marca el tiempo de creacion de cada zombie, dependen del nivel
	
	if(nivel_actual==0)
	{
		tlvl_act.setString("NIVEL "+ std::to_string( nivel_actual+1 )+ " (Tienes municion limitada\n para sobrevivir, usala bien. \nPresiona enter para disparar)");	///actualiza el cartel de nivel actual
	}
	else{
		tlvl_act.setString("NIVEL "+ std::to_string( nivel_actual+1 ));	///actualiza el cartel de nivel actual
	}
	
	
	zombi_4_lvl = niveles[nivel_actual];			///mantiene la cantidad de zombies que se crearan en el nivel
	
	v_zom.push_back(create_zombie());	
			zombies_creados=1;
					tamanio_vector = v_zom.size();
		
	song.play();
		
	while(g_change==false) {		///loop que mantiene el game
		
		t1= c1.getElapsedTime();
		
		if( t1.asSeconds() > ( tiempo_creacion + aux_time) and	 zombies_creados < zombi_4_lvl ){	
			aux_time+= tiempo_creacion;							
					pro = probability();
			
				if(	pro >= 25	 )		///la probability 1/2 esta dada para que se creen al azar los zombies
				{	
						v_zom.push_back(create_zombie());			///se crea el zombie
								zombies_creados++;				///se actualiza el contador
				}
			
		}	
		
		tamanio_vector = v_zom.size();
		
		for(int i= 0; i<tamanio_vector;++i)
		{
			finish_game = game_over(v_zom[i]);		///si algun zombie a pasado la linea el juego termina 
			if(finish_game==true)
			{
				draw_gameover(w,t_over,c1,t1, m1); break;			///si el juego ha terminado, se muestra el cartel de game over
			}
		}
		if(	you_win(v_zom, zombi_4_lvl, zombies_creados))
		{
			nivel_actual++;
				draw_gamewin(w,t_win,c1,t1,v_zom); return;						///si el nivel es ganado, se muestra el cartel de game win
		}
		
		///comienzan a registrarse los eventos
		while(w->pollEvent(e)) {
			
			switch (e.type){
				
			case Event::Closed:
				song.stop();
					g_change=true;
						w->close(); 
							m1.set_bool(true);
						break;
						
			case Event::KeyPressed:
				if(Keyboard::isKeyPressed(Keyboard::Key::Escape))
				{
					song.stop();
						show_quit(w, m1);
				break;
				}
				
				if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
						hero1.move_up(); break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Down)){
						hero1.move_down(); break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Left)){
						hero1.move_left(); break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Right)){
						hero1.move_right(); break;
				}
				
				if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
					hero1.do_shot();
					for(int i= 0; i<zombies_creados;++i)
					{
						if(impact(hero1.get_mira() , v_zom[i].get_zombie() ) )
						{
							v_zom[i].subtract_life();
								
							if(v_zom[i].get_lifes() == 0)
								{
									make_score( v_zom[i].get_intzombie() );
								}
						}
					}
					break;
				}				
			}
			
		}
		
		tamanio_vector = v_zom.size();
		t_puntaje.setString( std::to_string( puntuacion ));
		w->clear(Color(0,0,0));
		w->draw(spr_back);
		 
		
		if(tamanio_vector > 0){
			for(int i= 0; i<tamanio_vector; ++i)
			{
				
				if(v_zom[i].is_alive()==true)
				{
					v_zom[i].move_zombie(txt_zombies);
						finish_game = game_over(v_zom[i]);		///si algun zombie a pasado la linea el juego termina 
							w->draw(v_zom[i].get_zombie()); continue;
				}

			tamanio_vector = v_zom.size();
			
			for(int i= 0; i<tamanio_vector;++i)
			{
				finish_game = game_over(v_zom[i]);		///si algun zombie a pasado la linea el juego termina 
				if(finish_game==true)
				{
					draw_gameover(w,t_over,c1,t1, m1); break;			///si el juego ha terminado, se muestra el cartel de game over
				}
			}
			
		}
		if(tamanio_vector==0)
		{
			if(	you_win(v_zom, zombi_4_lvl, zombies_creados))
			{
				nivel_actual++;
				draw_gamewin(w,t_win,c1,t1, v_zom); return;						///si el nivel es ganado, se muestra el cartel de game win
			}
			else
				continue;
		}
		
		hero1.draw_all(w);
		w->draw(t_puntaje);
		w->draw(tlvl_act);
		w->display();
	
	}
	}
}

///compara los sprites de la mira y de algun zombie, si hay una interseccion
///retorna true para quitar luego quitar una vida a dicho zombie
bool Game::impact(Sprite s, Sprite x)
{
	if(s.getGlobalBounds().intersects(x.getGlobalBounds()))
	{
		return true;
	}
	else{
		return false;
	}
}


///toma la posicion de un zombie, si el eje x pasa de 150, entonces retorna true
/// y el juego termina, sino el bool es falso hasta que termine el loop
bool Game::game_over(Zombie z)
{
	Vector2f pos_zomb(z.get_zombie().getPosition());
	
	if( pos_zomb.x <= 150 )
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


///dibuja el cartel de gameover si algun zombie retorna el booleano game_over como true
///durante dos segundos se muestra el cartel, donde se guardara el puntaje obtenido, y regresa al menu
void Game::draw_gameover(RenderWindow *w, Text t,Clock c1, Time t1, mother_clase &m1)
{
	w->draw(t);
			w->display();
					song.stop();
					
	c1.restart();
			t1 = c1.getElapsedTime();
	while(t1.asSeconds()	<=	2)
	{	
		t1= c1.getElapsedTime();
	}
	
	std::vector<Score> vg_scores;				///vector de la clases score para comparar
			c_game.load_names_player(vg_scores);	///carga los nombres guardados en el archivo
			
	int size_vsc = vg_scores.size();				///tamaño del vector
	
	for(int i=0;i<size_vsc; ++i)
	{
		if(puntuacion >= vg_scores[i].get_score() )			///compara la puntuacion obtenida con las guardadas
		{																		///si es mayor a alguna de las guardadas se agrega al archivo
				inputbox(w, m1, puntuacion);
		}
	}

	m1.set_next(new menu(x));		///retorna al menu
			g_change = true;
					w->clear(Color(0,0,0));
}

///dibuja el cartel de win si el booleano game_over es false y si se han creados la cantidad
///de zombies que el nivel lo requieran, todos con su atributo alive en false
///durante dos segundos se muestra el cartel y comienza un nuevo nivel
void Game::draw_gamewin(RenderWindow *w, Text t,Clock c1, Time t1,  std::vector<Zombie> &v_zom)
{
	w->draw(t);
			w->display();
		
	c1.restart();
			t1 = c1.getElapsedTime();
					
	while(t1.asSeconds()	<=	2)
	{	
		t1= c1.getElapsedTime();
	}
	
	reset_vector(v_zom);
}


///crea un zombie y retorna para que se agregue al vector 

Zombie Game::create_zombie()
{
	Vector2f where;		///vector de la que sera creado el zombie
	
	
	int choice;			///al azar elige el numero de zombie que se creara
		choice = rand()%3+1;
		
	int rand_x;
	int aux_x;								///posicion del x
		if(nivel_actual == 0)
		{
			if(x==1)
				aux_x=780.2;
			else
				aux_x=980.2;
		}
		else if(nivel_actual > 0 and nivel_actual<=3)
		{
			if(x==1)
			{
				rand_x = rand()%3+1;
					aux_x = 780.2 - (rand_x*60);
			}
			else if(x==x)
			{
				rand_x = rand()%3+1;
					aux_x = 980.2 - (rand_x*120);
			}
		}
		else if(nivel_actual>3 and nivel_actual<=6)
		{
			if(x==1)
			{
				rand_x = rand()%3+1;
				aux_x = 780.2 - (rand_x*85);
			}
			else if(x==x)
			{
				rand_x = rand()%3+1;
				aux_x = 980.2 - (rand_x*130);
			}
		}
		else if(nivel_actual > 6)
		{
			if(x==1)
			{
				rand_x = rand()%3+1;
				aux_x = 780.2 - (rand_x*140);
			}
			else if(x==x)
			{
				rand_x = rand()%3+1;
				aux_x = 980.2 - (rand_x*200);
			}
		}
		
		
		///carga los valores dependiendo de la resolucion	
		if(x==1)			///resolucion 800x600
		{
			where.x= aux_x;
			where.y = (aux_y*30)+320;
			
		}
		if(x==2)			///resolucion 1024x700
		{
			where.x= aux_x;
			where.y = (aux_y*30)+370;
		}	
	
	
	if(aux_y==5)
	{
		aux_y = 0;  ///se reinicia para que los sprites de loz zombies esten unos sobre otros y cree la ilusion de perspectiva
	}
	aux_y++;	
	
	Zombie aux (choice,where, x, txt_zombies);
	
	return aux;
}

///crea la probabilidad y retorna un int para que se cree o no un zombie
int Game::probability()
{
	return (rand()%100+1);
}


///verifica si hay al menos ui zombie vivo y retorna true; si no retorna false
bool Game::you_win(std::vector<Zombie> v, int zom_4, int created)
{	
	int size = v.size();
	
	if(created == zom_4){
		for(int i = 0; i < size; i++)
		{
			if(v[i].is_alive()==true){
				return false;
			}
		}
		return true;
	}
	else{
		return false;
	}
}


///carga los datos en el vector de los niveles para que ejecute el juego
///segun la cantidad de zombies que el nivel tenga
void Game::load_lvls()
{
	int howmany=0;		///how many zombies
	
	for(int i=0;i<10;i++)
	{
		howmany += (i*5)+5;
		niveles.push_back(howmany);
	}
	
}

///muestra el cartel para que el jugador ingrese su nombre, si la puntuacion es alta,
///para ser guardado en el archivo de puntajes
void Game::inputbox(RenderWindow *w, mother_clase &m1, int puntaje)
{
	Sprite spr_box;
	Texture txt_box;
	Text tx;
	Font fx;
	
	bool closethis=false;
	
	txt_box.loadFromFile("sprites/inputbox.png");
	
	spr_box.setTexture(txt_box);
			spr_box.setPosition(200,200);
	

	fx.loadFromFile("fonts/letra_muni.ttf");
	
	tx.setFillColor(sf::Color::White);
			tx.setFont(fx);
					tx.setScale(1.5,1.5);
							tx.setPosition(240,300);
	
	std::string s;
	
	while(closethis==false){
		
		while(w->pollEvent(e)) {
			if(e.type == Event::Closed){
				song.stop();
				closethis=true;
					g_change=true;
						w->close();
						m1.set_bool(true);
					
			}
			
			else if(e.type == Event::KeyPressed)
			{				
				if(Keyboard::isKeyPressed(Keyboard::Key::Return))
				{
					c_game.save_name_player( s , puntaje );
					song.stop();
					closethis=true;
					g_change=true;
					m1.set_next(new menu(x));
					
				}
			}
			else if(e.type == Event::TextEntered){
				if (e.text.unicode < 128 and s.size()<12){
					s += static_cast<char>(e.text.unicode);
					if(Keyboard::isKeyPressed(Keyboard::Key::Escape))
					{
						song.stop();
						closethis=true;
						g_change=true;
						m1.set_next(new menu(x));
					}
				}
			}
		}
		w->clear(Color(0,0,0,200));
		tx.setString(s);
				w->draw(spr_box);
						w->draw(tx);
								w->display();
	}
	
		
}

void Game::show_quit(RenderWindow *w, mother_clase &m1)
{
		RectangleShape rect({300.f, 150.f});
				rect.setFillColor(Color(100,0,250,20));
						rect.setPosition(250,200);
		
		RectangleShape rect2({50,40});
				rect2.setFillColor(Color(255,255,255,0));
						rect2.setPosition(327,300);
								rect2.setOutlineThickness(4);
										rect2.setOutlineColor(sf::Color(250, 150, 100));
		
		Text t;
		Font f; 
				f.loadFromFile("fonts/letra_muni.ttf");
		
		t.setColor(sf::Color::Black);
				t.setFont(f);
						t.setScale(1.5,1.5);
								t.setPosition(330,200);
										std::string s="PAUSA";
		t.setString(s);
		
		Text t2;
				t2.setColor(sf::Color::Black);
						t2.setFont(f);
								t2.setPosition(310,250);
										std::string s2="DESEA SALIR?";
		t2.setString(s2);
		
		Text t3;
				t3.setColor(sf::Color::Black);
						t3.setFont(f);
								t3.setPosition(340,300);
										std::string s3="SI\tNO";
		t3.setString(s3);
		
		bool back_togame = false;
		
		Vector2f pos;
		
		while(back_togame==false)
		{
			while(w->pollEvent(e)) {
				
				pos = rect2.getPosition();
				
				if(e.type == Event::Closed){
					song.stop();
					g_change=true;
					w->close(); 
					m1.set_bool(true);
					break;
				}
				if(e.type == Event::KeyPressed)
				{
					if(Keyboard::isKeyPressed(Keyboard::Key::Right))
					{
						if(pos.x == 327)
							rect2.move(80,0);
					}
					if(Keyboard::isKeyPressed(Keyboard::Key::Left))
					{
						if(pos.x == 407)
							rect2.move(-80,0);
					}
					if(Keyboard::isKeyPressed(Keyboard::Key::Return))
					{
						if(pos.x == 327){
							song.stop();
							back_togame=true;
							g_change=true;
							m1.set_next(new menu(x));
							break;
						}
							
						else if(pos.x== 407)
							return;
					}
				}
			}
			pos = rect2.getPosition();
	
			w->draw(rect);
			w->draw(t);
			w->draw(t2);
			w->draw(t3);
			w->draw(rect2);
			w->display();
		}
}

void Game::registrar_tiempocreacion( float &tiem , int lvl_ac )
{
	if( lvl_ac <= 2)
		tiem = 1.2;			///en segundos
	else if( lvl_ac > 2 and lvl_ac <= 4)
		tiem = 1;
	else if( lvl_ac > 4 and lvl_ac <= 6)
		tiem = 0.6;
	else if( lvl_ac > 6 and lvl_ac <= 8)
		tiem = 0.4;
	else if( lvl_ac > 8 and lvl_ac == 9)
		tiem = 0.2;
}

void Game::make_score(int wichzomb)
{
	switch(wichzomb){
		
	case 1:
		puntuacion+=20; break;
		
	case 2:
		puntuacion+=35; break;
		
	case 3:	
		puntuacion+=45; break;
	}
			
}

void Game::reset_vector( std::vector<Zombie> &v_zom)
{

	v_zom.erase( v_zom.begin(), v_zom.end() );
	
}
