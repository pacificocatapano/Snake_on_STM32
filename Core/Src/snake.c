/*
 * snake.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Utente
 */


#include "snake.h"
#include <stdlib.h>
#include "punto.h"
bool game_over=false;

void inizializza(snake * my_snake){
	my_snake -> punti_snake = (punto*) malloc(N * sizeof(punto));
	my_snake -> q_dir = (dir*) malloc(N * sizeof(dir));

	punto primoPunto = pun_gen(NULL,NULL);
	(my_snake->punti_snake)[0] = primoPunto;


	dir diro = DESTRA;
	init(my_snake -> q_dir, diro, N);

	for (int i=1;i<N;++i){
		uint8_t temp = primoPunto.x - i*8;
		punto temp_punto = pun_gen(&(temp),&(primoPunto.y));
		(my_snake->punti_snake)[i] = temp_punto;
	}

	my_snake -> size = N;
}

void muovi(snake * my_snake,dir direzione, punto* frutto){
	enqueue(my_snake -> q_dir,direzione,my_snake->size);

	for(int i=0;i<my_snake->size;++i){
		int flag_mangiato = 0;
		spostamento_singolo(&((my_snake->punti_snake)[i]), (my_snake -> q_dir)[i], frutto, &flag_mangiato);
		if (i == 0 && flag_mangiato == 1){
			ingrandisci(my_snake);
		}

	}

	punto el = (my_snake->punti_snake)[0];
	for(int i=1;i<my_snake->size;++i){
		if (pun_cmp(el,(my_snake->punti_snake)[i])){
			game_over = true;
			break;
		}else{
			game_over = false;
		}
	}
}

void ingrandisci(snake * my_snake){
	my_snake -> size +=1;
	my_snake ->punti_snake = realloc(my_snake ->punti_snake,my_snake -> size*sizeof(punto));
	punto prev = my_snake ->punti_snake[my_snake -> size-2];
	int8_t x_off =0;
	int8_t y_off =0;

	switch(my_snake ->q_dir[my_snake -> size-2]){
		case SOPRA:
			y_off = 8;
			break;
		case SOTTO:
			y_off = -8;
			break;
		case DESTRA:
			x_off = -8;
			break;
		case SINISTRA:
			x_off = 8;
			break;
		default:
			break;
	}
	uint8_t somma_uix = somma_uint_to_int_8(prev.x,x_off);
	uint8_t somma_uiy = somma_uint_to_int_8(prev.y,y_off);
	my_snake ->punti_snake[my_snake -> size-1] = pun_gen(&(somma_uix),&(somma_uiy));

	my_snake ->q_dir = realloc(my_snake ->q_dir,my_snake -> size*sizeof(dir));
	my_snake ->q_dir[my_snake -> size-1] = my_snake ->q_dir[my_snake -> size-2];
}

