#include "menu.h"
#include <iostream>
#include <fstream>
#include "Game.h"

menu::menu(int x1): m_change(false), x(x1)
{
	c.r=0;
	c.b=0;
	c.g=210;
	
	song_menu.openFromFile("sound/menu_song.ogg");///musica de fondo
	song_menu.setVolume(20);
	song_menu.setLoop(true);
		
	///textos y fuentes
	f_menu1.loadFromFile("fonts/letra_start.ttf");	
	f_menu2.loadFromFile("fonts/letra_muni.ttf");
	
	t_menu1.setFont(f_menu1);
	t_menu1.setColor(c);
	
	t_menu2.setFont(f_menu1);
	t_menu2.setColor(c);
	
	t_menu3.setFont(f_menu1);
	t_menu3.setColor(c);
	
	txt_rect.loadFromFile("sprites/rect_menu.png");
	spr_rect.setTexture(txt_rect);
	spr_rect.setPosition(200,250);
	
	t_menu1.setScale(2.5,4.f);
	t_menu2.setScale(2.5,4.f);
	t_menu3.setScale(0.7,0.7);
	
	if(x==1)
	{
		txt_mback.loadFromFile("sprites/menu_background1.png");
		t_menu1.setPosition(200,100);
		t_menu2.setPosition(200,250);
		t_menu3.setPosition(220,420);

	}
	else if(x==2)
	{
		txt_mback.loadFromFile("sprites/menu_background2.png");
		t_menu1.setPosition(300,150);
		t_menu2.setPosition(300,300);
		t_menu3.setPosition(320,450);
		
	}
	
	spr_mback.setTexture(txt_mback);
	
}

void menu::update(RenderWindow *w,mother_clase &m1)
{
	show_start( w , m1);
	
}


void menu::show_start(RenderWindow *w,mother_clase &m1)
{

	song_menu.play();
	
	t_menu1.setString("COLLEGE");
	t_menu2.setString("ZOMBIES");
	t_menu3.setString("PRESS ENTER TO CONTINUE");
	
	while(m_change==false) {
		
		while(w->pollEvent(e_menu)) {
			
			switch (e_menu.type){
				
			case Event::Closed:
				song_menu.stop();
				w->close();	
				m1.set_bool(true);
				m_change=true;
				break;
				
			case Event::KeyPressed:
				
				if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
				song_menu.stop();
				w->close();
				m1.set_bool(true);
				m_change=true;
				break;
			}
				if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
					show_menu(w, m1); break;
				}
				
			}
		}
			w->clear(Color(0,0,0));
			w->draw(t_menu1);
			w->draw(t_menu2);
			w->draw(t_menu3);
			
			w->display();
	}
}

void menu::show_menu(RenderWindow *w,mother_clase &m1)
{	
	
	t_menu1.setFont(f_menu2);
	t_menu2.setFont(f_menu2);
	t_menu3.setFont(f_menu2);
	
	t_menu1.setString("INICIAR");
	t_menu2.setString("OPCIONES");
	t_menu3.setString("SALIR");

		t_menu1.setScale(2.5,2.5);
		t_menu2.setScale(2.5,2.5);
		t_menu3.setScale(2.5,2.5);
		
		t_menu1.setPosition(200,150);
		t_menu2.setPosition(200,250);
		t_menu3.setPosition(200,350);
		
	
	
	while(m_change==false) {
		
		while(w->pollEvent(e_menu) ) {
			
			switch (e_menu.type){
				
			case Event::Closed:
				song_menu.stop();
				m_change=true;
				w->close();	
				m1.set_bool(true);
				break;
				
			case Event::KeyPressed:
				
				if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
				song_menu.stop();
				m_change=true;
						w->close(); 
						m1.set_bool(true);
						break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
					
					que_eligio = int(get_pos_op(spr_rect));
					
					switch(que_eligio){
					case 250:
						song_menu.stop();
						m_change=true;
						m1.set_next(new Game(w));
						break;
						
					case 350:
						show_options(w, m1);
						break;
						
					case 450:
						song_menu.stop();
						m_change=true;
						w->close(); 
						m1.set_bool(true);
						break;
					}
					
					break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Down))
				{
					move_option_down(spr_rect);
					break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Up))
				{
					move_option_up(spr_rect);
					 break;
				}
				
			}
			
			
		}
		
		w->draw(spr_mback);
		w->draw(t_menu1);
		w->draw(t_menu2);
		w->draw(t_menu3);
		w->draw(spr_rect);
		
		w->display();
	}

	
	
}	

void menu::move_option_up(Sprite &spr_rect)
{
	switch (int(get_pos_op(spr_rect))){
		case 250:
			spr_rect.setPosition(200,450); break;
			
		case 350:
			spr_rect.setPosition(200,250);break;
			
		case 450:
			spr_rect.setPosition(200,350);break;
		
	}

}

void menu::move_option_down(Sprite &spr_rect)
{
	switch (int(get_pos_op(spr_rect))){
	case 250:
		spr_rect.setPosition(200,350); break;
		
	case 350:
		spr_rect.setPosition(200,450);break;
		
	case 450:
		spr_rect.setPosition(200,250);break;
		
	}

}


float menu::get_pos_op(Sprite spr_rect)
{
	Vector2f pos = spr_rect.getPosition();
	
	return (pos.y);
	
}

void menu::show_options(RenderWindow *w, mother_clase &m1)
{	
	
	t_menu1.setString("PUNTAJES");
	t_menu2.setString("RESOLUCION");
	t_menu3.setString("VOLVER");

	while(m_change==false ) {
		
		
		while(w->pollEvent(e_menu)) {
			
			switch (e_menu.type){
				
			case Event::Closed:
				song_menu.stop();
				m_change=true;
				w->close(); 
				m1.set_bool(true);
				break;
				
			case Event::KeyPressed:
				
				if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
				show_menu(w, m1); break;
					}
				if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
					
					que_eligio = int(get_pos_op(spr_rect));
					
					switch(que_eligio){
					case 250:
						show_scores( w, m1 );
						break;
						
					case 350:
						wha_resolution(w, m1);
						break;
						
					case 450:
						show_menu(w, m1);
						break;
					}
					
					break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Down)){
					
					move_option_down(spr_rect);
					break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
					move_option_up(spr_rect);
					break;
				}
				
			}
			w->clear(Color(0,0,0));
			w->draw(spr_mback);
			w->draw(t_menu1);
			w->draw(t_menu2);
			w->draw(t_menu3);
			w->draw(spr_rect);
			
			w->display();
			
		}
	}
}


void menu::wha_resolution(RenderWindow *w,mother_clase &m1)
{
	w->clear(Color(0,0,0));
	t_menu1.setString("800x600");
	t_menu2.setString("1024x700");
	t_menu3.setString("VOLVER");
	
	while(m_change==false) {
		
		while(w->pollEvent(e_menu)) {
			
			switch (e_menu.type){
				
			case Event::Closed:
				song_menu.stop();
				m_change=true;
				w->close(); 
				m1.set_bool(true);
				break;
				
			case Event::KeyPressed:
				
				if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
				show_options(w, m1); break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
					
					que_eligio = int(get_pos_op(spr_rect));
					
					switch(que_eligio){
					case 250:
						com.save_resolution(false);
							m1.change_resolution();
								x=1;
									show_options(w, m1);
					break;

					case 350:
						com.save_resolution(true);
							m1.change_resolution();
								x=2;
									show_options(w, m1);
						break;

					case 450:
						show_options(w, m1);
						break;
						
					}
					break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Down)){
					
					move_option_down(spr_rect);
					break;
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
					move_option_up(spr_rect);
					break;
				}
				
			}
				w->clear(Color(0,0,0));
				w->draw(spr_mback);
				w->draw(t_menu1);
				w->draw(t_menu2);
				w->draw(t_menu3);
				w->draw(spr_rect);
				
				w->display();
			}	
		}
		
	}

void menu::show_scores(RenderWindow *w, mother_clase &m1)
{
	Text t_score1;
	Text t_score2;
	Text t_score3;
	Text t_score4;
	Text t_score5;
	Font f_score;
	
	std::vector<Score> vm_sc;
	
	w->clear(Color(0,0,0));
	
		com.load_names_player( vm_sc );
		
		vm_sc[0].sort_scores( vm_sc );
		
	int size_v = vm_sc.size();	
	
	f_score.loadFromFile("fonts/letra_score.ttf");
	
	t_score1.setFont(f_score);
	t_score2.setFont(f_score);
	t_score3.setFont(f_score);
	t_score4.setFont(f_score);
	t_score5.setFont(f_score);
	
	t_score1.setColor(Color::Green);
	t_score2.setColor(Color::Green);
	t_score3.setColor(Color::Green);
	t_score4.setColor(Color::Green);
	t_score5.setColor(Color::Green);
	
	if(x==1){
		t_score1.setPosition(80,20); 	t_score1.setScale(2.f,2.f);
		t_score2.setPosition(80,100);	t_score2.setScale(2.f, 2.f);
		t_score3.setPosition(80,200);	t_score3.setScale(2.f,2.f);
		t_score4.setPosition(80,300);	t_score4.setScale(2.f,2.f);
		t_score5.setPosition(80,400);	t_score5.setScale(2.f,2.f);
	}
	else if(x==2)
		t_score1.setPosition(80,50); 	t_score1.setScale(3.f,3.f);
		t_score2.setPosition(80,170);	t_score2.setScale(3.f, 3.f);
		t_score3.setPosition(80,290);	t_score3.setScale(3.f,3.f);
		t_score4.setPosition(80,410);	t_score4.setScale(3.f,3.f);
		t_score5.setPosition(80,530);	t_score5.setScale(3.f,3.f);
	
	switch( size_v )
	{
			case 1:
				t_score1.setString( vm_sc[0].get_name() + " " + std::to_string(vm_sc[0].get_score()));
				break;
			case 2:
				t_score1.setString( vm_sc[0].get_name() + " " + std::to_string(vm_sc[0].get_score()));
				t_score2.setString( vm_sc[1].get_name() + " " + std::to_string(vm_sc[1].get_score()));
				break;
			case 3:
				t_score1.setString( vm_sc[0].get_name() + " " + std::to_string(vm_sc[0].get_score()));
				t_score2.setString( vm_sc[1].get_name() + " " + std::to_string(vm_sc[1].get_score()));
				t_score3.setString( vm_sc[2].get_name() + " " + std::to_string(vm_sc[2].get_score()));
				break;
				
			case 4:
				t_score1.setString( vm_sc[0].get_name() + " " + std::to_string(vm_sc[0].get_score()));
				t_score2.setString( vm_sc[1].get_name() + " " + std::to_string(vm_sc[1].get_score()));
				t_score3.setString( vm_sc[2].get_name() + " " + std::to_string(vm_sc[2].get_score()));
				t_score4.setString( vm_sc[3].get_name() + " " + std::to_string(vm_sc[3].get_score()));
				break;
			case 5:	
				t_score1.setString( vm_sc[0].get_name() + " " + std::to_string(vm_sc[0].get_score()));
				t_score2.setString( vm_sc[1].get_name() + " " + std::to_string(vm_sc[1].get_score()));
				t_score3.setString( vm_sc[2].get_name() + " " + std::to_string(vm_sc[2].get_score()));
				t_score4.setString( vm_sc[3].get_name() + " " + std::to_string(vm_sc[3].get_score()));
				t_score5.setString( vm_sc[4].get_name() + " " + std::to_string(vm_sc[4].get_score()));
				break;
	}
	
	
	

	while(m_change==false)
	{
			
		while(w->pollEvent(e_menu))
		{
			
			switch(e_menu.type)
			{
			case Event::KeyPressed:
				return;

					
			case Event::Closed:
				song_menu.stop();
				m_change=true;
				w->close(); 
				m1.set_bool(true);
				break;
			}
			
		w->clear(Color(0,0,0));
		w->draw(spr_mback);
		
		switch( size_v )
		{
		case 1:
			w->draw(t_score1);
			break;
		case 2:
			w->draw(t_score1);
			w->draw(t_score2);
			break;
		case 3:
			w->draw(t_score1);
			w->draw(t_score2);
			w->draw(t_score3);
			break;
			
		case 4:
			w->draw(t_score1);
			w->draw(t_score2);
			w->draw(t_score3);
			w->draw(t_score4);
			break;
		case 5:	
			w->draw(t_score1);
			w->draw(t_score2);
			w->draw(t_score3);
			w->draw(t_score4);
			w->draw(t_score5);
			break;
		}
			
		w->display();
		}	
	
	}
		
	
	
}
