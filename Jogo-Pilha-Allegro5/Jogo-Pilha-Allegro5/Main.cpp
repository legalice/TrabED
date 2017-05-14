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

const float FPS = 60; //frequencia de atualiza��o da tela
const int TELA_LARGURA = 800;
const int TELA_ALTURA = 600;
bool musica_estado = true; //musica ligada ou nao
int mouse; //clicou ou n�o no mouse
//bool bg_menu_trocar = false; //trocar o fundo ao passar o mouse sobre um botao do menu
int bg_menu_trocar_ordem; //ordem do bg_menu_imagens[4]
int tela_estado = 0; //em qual tela estamos
//int desenha_fundo = false;
int pedido_bolo[4];

//display
ALLEGRO_DISPLAY *janela = NULL; //janela para o jogo todo
ALLEGRO_EVENT_QUEUE *eventos_fila = NULL; //cria fila de eventos
ALLEGRO_TIMER *timer = NULL;// temporizador de atualiza��o da tela do jogo

//IMAGENS
ALLEGRO_BITMAP *janela_icone = NULL;

//background-menu
ALLEGRO_BITMAP *bg_menu = NULL;
ALLEGRO_BITMAP *bg_menu_jogar = NULL;
ALLEGRO_BITMAP *bg_menu_opcoes = NULL;
ALLEGRO_BITMAP *bg_menu_creditos = NULL;
ALLEGRO_BITMAP *bg_menu_sair = NULL;
ALLEGRO_BITMAP *bg_menu_imagens[5];

//backgrounds
ALLEGRO_BITMAP *backgrounds[5];
ALLEGRO_BITMAP *bg_instrucoes = NULL;
ALLEGRO_BITMAP *bg_bolo_modelo = NULL;
ALLEGRO_BITMAP *bg_opcoes = NULL;
ALLEGRO_BITMAP *bg_creditos = NULL;
ALLEGRO_BITMAP *bg_jogo_cenario = NULL;

//jogo imagens

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

//FUN��ES PRINCIPAIS - Prot�tipo

bool inicializar_addons();
bool inicializar_imagens();
void destruidores();
void gerador_bolo_modelo();

// ______________________________

bool inicializar_addons() {
	// INICIALIZA��O DE ADD-ONS
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

	//backgrounds

	bg_instrucoes = al_load_bitmap("../imagens/instrucoes.png");
	if (bg_instrucoes) {
		backgrounds[1] = bg_instrucoes;
	}
	else {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_instrucoes!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	bg_bolo_modelo = al_load_bitmap("../imagens/tela_bolo_modelo.png");
	if (bg_bolo_modelo) {
		backgrounds[2] = bg_bolo_modelo;
	}
	else {
			al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_bolo_modelo!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return false;
		}

	bg_jogo_cenario = al_load_bitmap("../imagens/jogo_cenario.png");
	if (bg_jogo_cenario) {
			backgrounds[3] = bg_jogo_cenario;
		}
	else {
			al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_jogo_cenario!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return false;
		}

	//falta tela 4 de op��es

	bg_creditos = al_load_bitmap("../imagens/creditos.png");
	if (bg_creditos) {
		backgrounds[5] = bg_creditos;
	}
	else {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image bg_creditos!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//imagens do jogo

		//bolo base
	jogo_bolo_base1 = al_load_bitmap("../imagens/bolo_base1.png");
	if (!jogo_bolo_base1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_base2 = al_load_bitmap("../imagens/bolo_base2.png");
	if (!jogo_bolo_base2) {
			al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base2!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return false;
		}

	jogo_bolo_base3 = al_load_bitmap("../imagens/bolo_base3.png");
	if (!jogo_bolo_base3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return false;
	}

	jogo_bolo_base4 = al_load_bitmap("../imagens/bolo_base4.png");
	if (!jogo_bolo_base4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_base5 = al_load_bitmap("../imagens/bolo_base5.png");
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
	jogo_bolo_cima1 = al_load_bitmap("../imagens/bolo_cima1.png");
	if (!jogo_bolo_base1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_base1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima2 = al_load_bitmap("../imagens/bolo_cima2.png");
	if (!jogo_bolo_base2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_cima2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima3 = al_load_bitmap("../imagens/bolo_cima3.png");
	if (!jogo_bolo_cima3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_cima3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima4 = al_load_bitmap("../imagens/bolo_cima4.png");
	if (!jogo_bolo_cima4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize image jogo_bolo_cima4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	jogo_bolo_cima5 = al_load_bitmap("../imagens/bolo_cima5.png");
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

	//menu inicial
	al_destroy_bitmap(bg_menu);
	al_destroy_bitmap(bg_menu_jogar);
	al_destroy_bitmap(bg_menu_opcoes);
	al_destroy_bitmap(bg_menu_creditos);
	al_destroy_bitmap(bg_menu_sair);

	//jogo
	al_destroy_bitmap(bg_jogo_cenario);
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
	
	//janela
	al_destroy_display(janela);
	al_destroy_bitmap(janela_icone);
}

void gerador_bolo_modelo() {
	srand(time(NULL));

	pedido_bolo[0] = rand()%5; //0 a 4 - base
	pedido_bolo[1] = rand()%5 + 5; //5 a 9 - recheio
	pedido_bolo[2] = rand()%5 + 10; //10 a 14 - cima
	pedido_bolo[3] = rand()%5 + 15; //14 a 19 - cobertura

	//base

	if (pedido_bolo[0] == 0) {
		al_draw_bitmap(jogo_bolo_base1, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_bolo_base1)/2), 290, 0);
	}
	else if (pedido_bolo[0] == 1) {
		al_draw_bitmap(jogo_bolo_base2, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_bolo_base2)/2), 290, 0);
	}
	else if (pedido_bolo[0] == 2) {
		al_draw_bitmap(jogo_bolo_base3, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_bolo_base3)/2), 290, 0);
	}
	else if (pedido_bolo[0] == 3) {
		al_draw_bitmap(jogo_bolo_base4, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_bolo_base4)/2), 290, 0);
	}
	else if (pedido_bolo[0] == 4) {
		al_draw_bitmap(jogo_bolo_base5, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_bolo_base5)/2), 290, 0);
	}

	//recheio
	if (pedido_bolo[1] == 5) {
		al_draw_bitmap(jogo_recheio1, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio1) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 6) {
		al_draw_bitmap(jogo_recheio2, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio2) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 7) {
		al_draw_bitmap(jogo_recheio3, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio3) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 8) {
		al_draw_bitmap(jogo_recheio4, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio4) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 9) {
		al_draw_bitmap(jogo_recheio5, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio5) / 2), 260, 0);
	}

	//cima

	if (pedido_bolo[2] == 10) {
		al_draw_bitmap(jogo_bolo_cima1, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 11) {
		al_draw_bitmap(jogo_bolo_cima2, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 12) {
		al_draw_bitmap(jogo_bolo_cima3, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 13) {
		al_draw_bitmap(jogo_bolo_cima4, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 14) {
		al_draw_bitmap(jogo_bolo_cima5, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_recheio5) / 2), 200, 0);
	}

	//cobertura
	if (pedido_bolo[3] == 15) {
		al_draw_bitmap(jogo_cobertura1, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_cobertura1) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 16) {
		al_draw_bitmap(jogo_cobertura2, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_cobertura2) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 17) {
		al_draw_bitmap(jogo_cobertura3, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_cobertura3) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 18) {
		al_draw_bitmap(jogo_cobertura4, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_cobertura4) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 19) {
		al_draw_bitmap(jogo_cobertura5, (TELA_LARGURA / 2) - (al_get_bitmap_width(jogo_cobertura5) / 2), 160, 0);
	}
	
}

void jogo(int tempo_jogo) {
	al_set_target_backbuffer(janela);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//al_draw_scaled_bitmap(, 0, 0, 800, 600, 0, 0, al_get_display_width(tela), al_get_display_height(tela), 0);
	bg_jogo_cenario;



}

int main(int argc, char **argv) {
	
	
	bool redraw = false;

	inicializar_addons();
	inicializar_imagens(); 
	if (!inicializar_imagens()) {
		destruidores();
		return 0;
	}
	
	//JANELA
	janela = al_create_display(TELA_LARGURA, TELA_ALTURA);// cria janela
	//caso nao inicialize a janela
	if (!janela) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize janela",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_window_title(janela, "F�brica de Bolos"); //titulo da janela
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

	//timer de atualiza��o da tela
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize timer",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	eventos_fila = al_create_event_queue(); //criacao da fila de eventos
	if (!eventos_fila) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize eventos fila",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//REGISTROS DE SOURCES
	al_register_event_source(eventos_fila, al_get_keyboard_event_source()); //qualquer evento do teclado ser� armazenado na fila de eventos
	al_register_event_source(eventos_fila, al_get_display_event_source(janela)); //qualquer evento do display ser� armazenado na fila de eventos
	al_register_event_source(eventos_fila, al_get_mouse_event_source()); //--evento do mouse
	al_register_event_source(eventos_fila, al_get_timer_event_source(timer));//--evento do timer

	//Coisas antes da repeticao do loop
	al_set_target_backbuffer(janela);
	al_flip_display();
	al_start_timer(timer); //timer do FPS come�a
	al_set_mixer_gain(al_get_default_mixer(), 1.0); //amplificador da musica
	al_play_sample_instance(musica_instancia); //da play na musica

	//LOOP PRINCIPAL
	while (1){
		ALLEGRO_EVENT evento; //o alegro � orientado a eventos, essa � a variavel evento
		al_wait_for_event(eventos_fila, &evento); //coloca um novo evento na fila de eventos, para ent�o executar o while

		if (evento.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
		}

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			destruidores();
			exit(EXIT_SUCCESS);
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

			if (mouse == 1 && evento.mouse.x > 19 && evento.mouse.x < 195 && evento.mouse.y > 480 && evento.mouse.y < 541 && tela_estado == 0) {//jogar
				tela_estado = 1; //imagem de instru��es
				mouse = 0;
				redraw = true;
				//desenha_fundo = true;
				
				//al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE JOGAR",
				//NULL, ALLEGRO_MESSAGEBOX_WARN);
			}
			else if (mouse == 1 && evento.mouse.x > 215 && evento.mouse.x < 397 && evento.mouse.y > 480 && evento.mouse.y < 541 && tela_estado == 0) {//opcoes
				//tela_estado = 4;//tela de opcoes
				mouse = 0;
				redraw = true;
				//desenha_fundo = true;
				//al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE OPCOES",
				//NULL, ALLEGRO_MESSAGEBOX_WARN);
			}
			else if (mouse == 1 && evento.mouse.x > 418 && evento.mouse.x < 595 && evento.mouse.y > 480 && evento.mouse.y < 541 && tela_estado == 0) {//creditos
				tela_estado = 5; //tela de creditos
				mouse = 0;
				redraw = true;
				//desenha_fundo = true;

				//al_show_native_message_box(janela, "TESTE", "TESTE", "TESTE CREDITOS",
				//NULL, ALLEGRO_MESSAGEBOX_WARN);
			}
			else if (mouse == 1 && evento.mouse.x > 611 && evento.mouse.x < 791 && evento.mouse.y > 480 && evento.mouse.y < 541 && tela_estado == 0) {//sair	
				mouse = 0;
				if (al_show_native_message_box(janela, "Aten��o", "Pergunta:", "Tem certeza que deseja sair do jogo?",
					NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL)) {
					destruidores();
					exit(EXIT_SUCCESS);
				}
				
				//redraw = true;
			}
			else if(mouse == 1 && tela_estado == 1) {
				tela_estado = 2; //tela bolo modelo
				mouse = 0;
				redraw = true;
				//desenha_fundo = true;
			}
			else if (mouse == 1 && tela_estado == 2) {
				//jogo tela
				tela_estado = 3;
				mouse = 0;
				redraw = true;
				//desenha_fundo = true;
			}

		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			mouse = 0;

		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
			if (evento.mouse.x > 19 && evento.mouse.x < 195 && evento.mouse.y > 480 && evento.mouse.y < 541) {//jogar
				redraw = true;
				//bg_menu_trocar = true; //vai trocar o fundo pora causa do botao
				bg_menu_trocar_ordem = 1; //imagem que vai trocar

			}
			else if (evento.mouse.x > 215 && evento.mouse.x < 397 && evento.mouse.y > 480 && evento.mouse.y < 541) {//opcoes
				//bg_menu_trocar = true;
				bg_menu_trocar_ordem = 2;
				redraw = true;

			}
			else if (evento.mouse.x > 418 && evento.mouse.x < 595 && evento.mouse.y > 480 && evento.mouse.y < 541) {//creditos
				redraw = true;
				//bg_menu_trocar = true;
				bg_menu_trocar_ordem = 3;

			}
			else if (evento.mouse.x > 611 && evento.mouse.x < 791 && evento.mouse.y > 480 && evento.mouse.y < 541) {//sair
				redraw = true;
				//bg_menu_trocar = true;
				bg_menu_trocar_ordem = 4;

			}
			else {
				redraw = true;
				//bg_menu_trocar = true;
				bg_menu_trocar_ordem = 0;
			}
		}

		//ultimo metodo do while
		if (redraw && al_is_event_queue_empty(eventos_fila)) {
			redraw = false;

			if (musica_estado) {
				al_set_sample_instance_gain(musica_instancia, 1.0);
			} 
			else {
				al_set_sample_instance_gain(musica_instancia, 0.0);
			}

			if (tela_estado == 0) {
				al_draw_scaled_bitmap(bg_menu_imagens[bg_menu_trocar_ordem], 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
			}
			else {
				al_clear_to_color(al_map_rgb(255, 255, 255)); //a imagem do cenario eh meio transparente
				al_draw_scaled_bitmap(backgrounds[tela_estado], 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
			}

			if (tela_estado == 2) {
				//al_set_target_backbuffer(janela);
				gerador_bolo_modelo();
				//al_rest(10);
				//tela_estado = 3;
			}

			al_flip_display();
		}
	}

	//DESTRUTORES
	destruidores();

		return 0;
}

//FUN��ES PRINCIPAIS
