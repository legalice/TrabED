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

// ______________________________

//INCLUDES DO JOGO
#include "pilha.h"

// ______________________________

//VARIAVEIS GLOBAIS

const float FPS = 60; //frequencia de atualização da tela
const int TELA_LARGURA = 800;
const int TELA_ALTURA = 600;
bool musica_estado = true; //musica ligada ou nao
int mouse; //clicou ou não no mouse
bool bg_menu_trocar = false; //trocar o fundo ao passar o mouse sobre um botao do menu
int bg_menu_trocar_ordem; //ordem do bg_menu_imagens[4]
int tela_estado = 0; //em qual tela estamos

//display
ALLEGRO_DISPLAY *janela = NULL; //janela para o jogo todo
ALLEGRO_EVENT_QUEUE *eventos_fila = NULL; //cria fila de eventos
ALLEGRO_TIMER *timer = NULL;// temporizador de atualização da tela do jogo

//IMAGENS
ALLEGRO_BITMAP *janela_icone = NULL;

//background-menu
ALLEGRO_BITMAP *bg_menu = NULL;
ALLEGRO_BITMAP *bg_menu_jogar = NULL;
ALLEGRO_BITMAP *bg_menu_opcoes = NULL;
ALLEGRO_BITMAP *bg_menu_creditos = NULL;
ALLEGRO_BITMAP *bg_menu_sair = NULL;
ALLEGRO_BITMAP *bg_menu_imagens[5];

//jogo imagens
ALLEGRO_BITMAP *jogo_cenario = NULL;

ALLEGRO_BITMAP *jogo_bolo_base1 = NULL;
ALLEGRO_BITMAP *jogo_bolo_base2 = NULL;
ALLEGRO_BITMAP *jogo_bolo_base3 = NULL;
ALLEGRO_BITMAP *jogo_bolo_base4 = NULL;
ALLEGRO_BITMAP *jogo_bolo_base5= NULL;

ALLEGRO_BITMAP *jogo_recheio1 = NULL;
ALLEGRO_BITMAP *jogo_recheio2 = NULL;
ALLEGRO_BITMAP *jogo_recheio3 = NULL;
ALLEGRO_BITMAP *jogo_recheio4 = NULL;
ALLEGRO_BITMAP *jogo_recheio5 = NULL;

ALLEGRO_BITMAP *jogo_bolo_cima1 = NULL;
ALLEGRO_BITMAP *jogo_bolo_cima2 = NULL;
ALLEGRO_BITMAP *jogo_bolo_cima3 = NULL;
ALLEGRO_BITMAP *jogo_bolo_cima4 = NULL;
ALLEGRO_BITMAP *jogo_bolo_cima5 = NULL;

ALLEGRO_BITMAP *jogo_cobertura1 = NULL;
ALLEGRO_BITMAP *jogo_cobertura2 = NULL;
ALLEGRO_BITMAP *jogo_cobertura3 = NULL;
ALLEGRO_BITMAP *jogo_cobertura4 = NULL;
ALLEGRO_BITMAP *jogo_cobertura5 = NULL;

//Audio
ALLEGRO_SAMPLE *musica = NULL;
ALLEGRO_SAMPLE_INSTANCE *musica_instancia = NULL;

// ______________________________

//FUNÇÕES PRINCIPAIS - Protótipo

bool inicializar_addons();
bool inicializar_imagens();
void destruidores();

// ______________________________

bool inicializar_addons() {
	// INICIALIZAÇÃO DE ADD-ONS
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();

	//caso  nao inicialize o allegro
	if (!al_init()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//caso nao inicialize o addon de imagens
	if (!al_init_image_addon()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize primitive addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_font_addon()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize font addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_ttf_addon()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize ttf addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_keyboard()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize install keyboard addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize install mouse addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_audio()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize install audio addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_acodec_addon()) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize acodec audio addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	return true;

}

bool inicializar_imagens() {

	//MENU INICIAL

	bg_menu = al_load_bitmap("../imagens/bg_menu.png");
	if (bg_menu) {
		bg_menu_imagens[0] = bg_menu;
	}
	else {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_menu!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	bg_menu_jogar = al_load_bitmap("../imagens/bg_menu_jogar.png");
	if (bg_menu_jogar) {
		bg_menu_imagens[1] = bg_menu_jogar;
	}
	else {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_menu_jogar!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	bg_menu_opcoes = al_load_bitmap("../imagens/bg_menu_opcoes.png");
	if (bg_menu_opcoes) {
		bg_menu_imagens[2] = bg_menu_opcoes;
	}
	else {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_menu_opcoes!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	bg_menu_creditos = al_load_bitmap("../imagens/bg_menu_creditos.png");
	if (bg_menu_creditos) {
		bg_menu_imagens[3] = bg_menu_creditos;
	}
	else {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_menu_creditos!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	bg_menu_sair = al_load_bitmap("../imagens/bg_menu_sair.png");
	if (bg_menu_sair) {
		bg_menu_imagens[4] = bg_menu_sair;
	}
	else {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_menu_sair!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//icone da janela

	janela_icone = al_load_bitmap("../imagens/janela_icone.png");
	if (!janela_icone) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image janela icone!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//imagens do jogo

	jogo_cenario = al_load_bitmap("../imagens/jogo_cenario.png");
	if (!jogo_cenario) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_cenario!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//bolo base
	jogo_bolo_base1 = al_load_bitmap("../imagens/bolo1.png");
	if (!jogo_bolo_base1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_base2 = al_load_bitmap("../imagens/bolo2.png");
	if (!jogo_bolo_base2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_base3 = al_load_bitmap("../imagens/bolo3.png");
	if (!jogo_bolo_base3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_base4 = al_load_bitmap("../imagens/bolo4.png");
	if (!jogo_bolo_base4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_base5 = al_load_bitmap("../imagens/bolo5.png");
	if (!jogo_bolo_base5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//recheios
	jogo_recheio1 = al_load_bitmap("../imagens/recheio1.png");
	if (!jogo_recheio1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image recheio1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_recheio2 = al_load_bitmap("../imagens/recheio2.png");
	if (!jogo_recheio2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image recheio2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_recheio3 = al_load_bitmap("../imagens/recheio3.png");
	if (!jogo_recheio3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image recheio3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_recheio4 = al_load_bitmap("../imagens/recheio4.png");
	if (!jogo_recheio4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image recheio4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_recheio5 = al_load_bitmap("../imagens/recheio5.png");
	if (!jogo_recheio5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image recheio5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//bolo de cima
	jogo_bolo_cima1 = al_load_bitmap("../imagens/bolo1.png");
	if (!jogo_bolo_base1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima2 = al_load_bitmap("../imagens/bolo2.png");
	if (!jogo_bolo_base2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_cima2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima3 = al_load_bitmap("../imagens/bolo3.png");
	if (!jogo_bolo_cima3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_cima3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima4 = al_load_bitmap("../imagens/bolo4.png");
	if (!jogo_bolo_cima4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_cima4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima5 = al_load_bitmap("../imagens/bolo5.png");
	if (!jogo_bolo_cima5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_cima5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//cobertura

	jogo_cobertura1 = al_load_bitmap("../imagens/cobertura1.png");
	if (!jogo_cobertura1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image cobertura1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_cobertura2 = al_load_bitmap("../imagens/cobertura2.png");
	if (!jogo_cobertura2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image cobertura2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_cobertura3 = al_load_bitmap("../imagens/cobertura3.png");
	if (!jogo_cobertura3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image cobertura3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_cobertura4 = al_load_bitmap("../imagens/cobertura4.png");
	if (!jogo_cobertura4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image cobertura4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_cobertura5 = al_load_bitmap("../imagens/cobertura5.png");
	if (!jogo_cobertura5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image cobertura5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	return true;
}

void destruidores() {
	//IMAGENS

	//janela
	al_destroy_bitmap(janela_icone);

	//menu inicial
	al_destroy_bitmap(bg_menu);
	al_destroy_bitmap(bg_menu_jogar);
	al_destroy_bitmap(bg_menu_opcoes);
	al_destroy_bitmap(bg_menu_creditos);
	al_destroy_bitmap(bg_menu_sair);

	//jogo
	al_destroy_bitmap(jogo_cenario);
	al_destroy_bitmap(jogo_bolo_base1);
	al_destroy_bitmap(jogo_bolo_base2);
	al_destroy_bitmap(jogo_bolo_base3);
	al_destroy_bitmap(jogo_bolo_base4);
	al_destroy_bitmap(jogo_bolo_base5);

	al_destroy_bitmap(jogo_recheio1);
	al_destroy_bitmap(jogo_recheio2);
	al_destroy_bitmap(jogo_recheio3);
	al_destroy_bitmap(jogo_recheio4);
	al_destroy_bitmap(jogo_recheio5);

	al_destroy_bitmap(jogo_bolo_cima1);
	al_destroy_bitmap(jogo_bolo_cima2);
	al_destroy_bitmap(jogo_bolo_cima3);
	al_destroy_bitmap(jogo_bolo_cima4);
	al_destroy_bitmap(jogo_bolo_cima5);

	al_destroy_bitmap(jogo_cobertura1);
	al_destroy_bitmap(jogo_cobertura2);
	al_destroy_bitmap(jogo_cobertura3);
	al_destroy_bitmap(jogo_cobertura4);
	al_destroy_bitmap(jogo_cobertura5);

	//MUSICA
	al_destroy_sample_instance(musica_instancia);
	al_destroy_sample(musica);
	
	//OUTROS

	al_destroy_timer(timer);
	al_destroy_event_queue(eventos_fila);
	al_destroy_display(janela);

}

void jogo() {
}

int main(int argc, char **argv) {
	
	bool redraw = false;

	inicializar_addons();
	inicializar_imagens(); 
	
	//JANELA
	janela = al_create_display(TELA_LARGURA, TELA_ALTURA);// cria janela
	//caso nao inicialize a janela
	if (!janela) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize janela",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_window_title(janela, "Fábrica de Bolos"); //titulo da janela
	al_set_display_icon(janela, janela_icone); //carrega o icone do jogo na janela

	//AUDIO
	al_reserve_samples(2); //quantos sons podem tocar AO MESMO TEMPO?
	musica = al_load_sample("../sons/caketown.ogg");
	if (!musica){
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize musica",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	musica_instancia = al_create_sample_instance(musica);
	al_set_sample_instance_playmode(musica_instancia, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(musica_instancia, al_get_default_mixer());

	//timer de atualização da tela
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


	eventos_fila = al_create_event_queue(); //criacao da fila de eventos
	if (!eventos_fila) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize eventos fila",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//REGISTROS DE SOURCES
	al_register_event_source(eventos_fila, al_get_keyboard_event_source()); //qualquer evento do teclado será armazenado na fila de eventos
	al_register_event_source(eventos_fila, al_get_display_event_source(janela)); //qualquer evento do display será armazenado na fila de eventos
	al_register_event_source(eventos_fila, al_get_mouse_event_source()); //--evento do mouse
	al_register_event_source(eventos_fila, al_get_timer_event_source(timer));//--evento do timer

	//Coisas antes da repeticao do loop
	al_set_target_backbuffer(janela);
	al_flip_display();
	al_start_timer(timer); //timer do FPS começa
	al_set_mixer_gain(al_get_default_mixer(), 1.0); //amplificador da musica
	al_play_sample_instance(musica_instancia); //da play na musica

	//LOOP PRINCIPAL
	while (1){
		ALLEGRO_EVENT evento; //o alegro é orientado a eventos, essa é a variavel evento
		al_wait_for_event(eventos_fila, &evento); //coloca um novo evento na fila de eventos, para então executar o while

		if (evento.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
		}


		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
			//colocar destrutores
		}


		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				break; 
			}
		}

		if (evento.type == ALLEGRO_EVENT_KEY_UP) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_M) {
				//toca ou para musiquinha
				redraw = true;
				musica_estado = (!musica_estado);
			}
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			mouse = evento.mouse.button;

			if (mouse == 1 && evento.mouse.x > 19 && evento.mouse.x < 195 && evento.mouse.y > 480 && evento.mouse.y < 541) {//jogar
				tela_estado = 0;

				//al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE JOGAR",
					//NULL, ALLEGRO_MESSAGEBOX_WARN);
				mouse = 0;
				redraw = true;
			}
			else if (mouse == 1 && evento.mouse.x > 215 && evento.mouse.x < 397 && evento.mouse.y > 480 && evento.mouse.y < 541) {//opcoes
				tela_estado = 1;
				//al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE OPCOES",
					//NULL, ALLEGRO_MESSAGEBOX_WARN);
				mouse = 0;
				redraw = true;
			}
			else if (mouse == 1 && evento.mouse.x > 418 && evento.mouse.x < 595 && evento.mouse.y > 480 && evento.mouse.y < 541) {//creditos
				tela_estado = 2;
					//al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE CREDITOS",
					//NULL, ALLEGRO_MESSAGEBOX_WARN);
				mouse = 0;
				redraw = true;
			}
			else if (mouse == 1 && evento.mouse.x > 611 && evento.mouse.x < 791 && evento.mouse.y > 480 && evento.mouse.y < 541) {//sair
				tela_estado = 3;																												  //al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE CREDITOS",
				//al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE SAIR",
					//NULL, ALLEGRO_MESSAGEBOX_WARN);
				mouse = 0;
				redraw = true;
			}
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			mouse = 0;

		}
		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
			if (evento.mouse.x > 19 && evento.mouse.x < 195 && evento.mouse.y > 480 && evento.mouse.y < 541) {//jogar
				redraw = true;
				bg_menu_trocar = true; //vai trocar o fundo pora causa do botao
				bg_menu_trocar_ordem = 1; //imagem que vai trocar

			}
			else if (evento.mouse.x > 215 && evento.mouse.x < 397 && evento.mouse.y > 480 && evento.mouse.y < 541) {//opcoes
				bg_menu_trocar = true;
				bg_menu_trocar_ordem = 2;
				redraw = true;

			}
			else if (evento.mouse.x > 418 && evento.mouse.x < 595 && evento.mouse.y > 480 && evento.mouse.y < 541) {//creditos
				redraw = true;
				bg_menu_trocar = true;
				bg_menu_trocar_ordem = 3;

			}
			else if (evento.mouse.x > 611 && evento.mouse.x < 791 && evento.mouse.y > 480 && evento.mouse.y < 541) {//sair
				redraw = true;
				bg_menu_trocar = true;
				bg_menu_trocar_ordem = 4;

			}
			else {
				redraw = true;
				bg_menu_trocar = true;
				bg_menu_trocar_ordem = 0;
			}
		}

		//clique no menu
		

		//ultimo metodo do while
		if (redraw && al_is_event_queue_empty(eventos_fila)) {
			redraw = false;

			if (musica_estado) {
				al_set_sample_instance_gain(musica_instancia, 1.0);
			}
			else {
				al_set_sample_instance_gain(musica_instancia, 0.0);
			}

			if (bg_menu_trocar) {
				al_draw_scaled_bitmap(bg_menu_imagens[bg_menu_trocar_ordem], 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
			}
			else {
				al_draw_scaled_bitmap(bg_menu, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
			}


			
			//al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
		}

		//al_flip_display(); //colocar isso faz ficar lento, melhor dar redraw
	}

		//DESTRUTORES
		
		destruidores();

		return 0;
}


//FUNÇÕES PRINCIPAIS
