#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// ______________________________

//BIBLIOTECAS DO ALLEGRO
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

//INCLUDES DO JOGO

#include "pilha.h"
// ______________________________

//VARIAVEIS GLOBAIS
const float FPS = 60; //frequencia de atualização da tela
const int TELA_LARGURA = 800;
const int TELA_ALTURA = 600;
int mouse;

//display
ALLEGRO_DISPLAY *janela = NULL; //janela para o jogo todo
ALLEGRO_EVENT_QUEUE *eventos_fila = NULL; //cria fila de eventos
ALLEGRO_TIMER *timer = NULL;// temporizador de atualização da tela do jogo

//imagens
ALLEGRO_BITMAP *janela_icone = NULL;
ALLEGRO_BITMAP *bg_main1 = NULL;



// ______________________________

//FUNÇÕES PRINCIPAIS - Protótipo

// ______________________________

int main(int argc, char **argv) {
	
	bool redraw = false;

	// ______________________________

	// INICIALIZAÇÃO DE ADD-ONS
	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();

	//caso  nao inicialize o allegro
	if (!al_init()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//caso nao inicialize o addon de imagens
	if (!al_init_image_addon()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//INICIALIZAR IMAGENS

	bg_main1 = al_load_bitmap("../imagens/main1.png");
	if (!bg_main1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize bg_main!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	janela_icone = al_load_bitmap("../imagens/janela_icone.png");
	if (!janela_icone) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize bg_main!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}




	janela = al_create_display(TELA_LARGURA, TELA_ALTURA);// cria janela
	//caso nao inicialize a janela
	if (!janela) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize janela",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_window_title(janela, "Fábrica de Bolos"); //titulo da janela
	//al_set_display_icon(janela, janela_icone); //carrega o icone do jogo na janela

	 // _____________________________________________________________

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize timer",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

		//al_set_target_bitmap(bouncer);
		//al_clear_to_color(al_map_rgb(255, 0, 255));
		//al_set_target_bitmap(al_get_backbuffer(display));
		//al_register_event_source(event_queue, al_get_display_event_source(display));
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		//al_flip_display();


	eventos_fila = al_create_event_queue(); //criacao da fila de eventos
	if (!eventos_fila) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize janela",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//REGISTROS DE SOURCES
	al_register_event_source(eventos_fila, al_get_keyboard_event_source()); //qualquer evento do teclado será armazenado na fila de eventos
	al_register_event_source(eventos_fila, al_get_display_event_source(janela)); //qualquer evento do display será armazenado na fila de eventos
	al_register_event_source(eventos_fila, al_get_mouse_event_source()); //--evento do mouse
	al_register_event_source(eventos_fila, al_get_timer_event_source(timer));//--evento do timer

																				 //LOOP PRINCIPAL
	al_set_target_backbuffer(janela);
	al_flip_display();
	al_start_timer(timer);

	while (1){
		ALLEGRO_EVENT evento; //o alegro é orientado a eventos, essa é a variavel evento
		al_wait_for_event(eventos_fila, &evento); //coloca um novo evento na fila de eventos, para então executar o while

		if (evento.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
		}


		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break; 
		}

		if (redraw && al_is_event_queue_empty(eventos_fila)) {
			redraw = false;
			al_draw_scaled_bitmap(bg_main1, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
			//al_draw_bitmap(bg_main1, 0, 0, 0);
			//al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
		}

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				break; 
			}
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
				//movimentação do mouse
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				mouse = evento.mouse.button;
		}

		al_flip_display();
	}

		al_destroy_bitmap(bg_main1);//
		al_destroy_bitmap(janela_icone);//
		al_destroy_timer(timer);//
		al_destroy_display(janela);//
		al_destroy_event_queue(eventos_fila);//

		return 0;
}


//FUNÇÕES PRINCIPAIS
