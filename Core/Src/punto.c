/*
 * punto.c
 *
 *  Created on: 28 dic 2022
 *      Author: Utente
 */


#include <stdlib.h>
#include "punto.h"

int score = 0;
int seed = 1;

#define MAX_DIS_X 127
#define MAX_X 120
#define MAX_DIS_Y 63
#define MAX_Y 56
#define MIN_X 0
#define MIN_Y 0


punto pun_gen(uint8_t *x,uint8_t *y) {
	punto punto_gen;
	srand(seed);
	seed +=1;
	if (x == NULL){
		punto_gen.x = (rand() % (((MAX_DIS_X+1)/8)-1))*8;
	}else{
		punto_gen.x = *x;
	}
	if (y == NULL){
		punto_gen.y = (rand() % (((MAX_DIS_Y+1)/8)-1))*8;
	}else{
		punto_gen.y = *y;
	}

	return punto_gen;
};

bool pun_cmp(punto punto1, punto punto2) {
	if (punto1.x == punto2.x && punto1.y == punto2.y)
		return true;
	return false;
};

bool pun_cmp_2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	if (x1 == x2 && y1 == y2)
		return true;
	return false;
};

uint8_t somma_uint_to_int_8(uint8_t cuint,int8_t cint) {

	if (cint >= 0)
		return cuint + (uint8_t)cint;
	else
		return cuint - (uint8_t)abs(cint);
}

void spostamento_offset(punto * pun, int8_t x_offset, int8_t y_offset, punto* frutto, int *flag_mangiato) {
	int8_t current_x =(int8_t) pun -> x;
	int8_t current_y = (int8_t)pun ->y;
	int16_t prev_x = current_x+ x_offset;
	int16_t prev_y = current_y + y_offset;
	bool no_border_x = (prev_x >= MIN_X) && (prev_x <= MAX_X);
	bool no_border_y = (prev_y >= MIN_Y) && (prev_y <= MAX_Y);
	bool no_border = no_border_x && no_border_y;

	bool up_dx_angle = (((current_x == MAX_X) && (prev_y < MIN_Y)) || ((prev_x > MAX_X) && (current_y == MIN_Y)));
	bool up_sx_angle = (((current_x == MIN_X) && (prev_y < MIN_Y)) || ((prev_x < MIN_X) && (current_y == MIN_Y)));
	bool down_dx_angle = (((prev_x > MAX_X) && (current_y == MAX_Y)) || ((current_x == MAX_X) && (prev_y > MAX_Y)));
	bool down_sx_angle =(((prev_x < MIN_X) && (current_y == MAX_Y)) || ((current_x == MIN_X) && (prev_y > MAX_Y)));
	bool angle = up_dx_angle || up_sx_angle || down_dx_angle || down_sx_angle;

	if (no_border)
	{
		pun -> x = (uint8_t)prev_x;
		pun -> y = (uint8_t)prev_y;
	}
	else
	{
		if (angle){
			if (up_dx_angle){
				if (x_offset == 0){
					pun -> y = MAX_Y;
					pun -> x = MAX_X;
				}else if (y_offset == 0){
					pun -> x = MIN_X;
					pun -> y = MIN_Y;
				}
			}else if (up_sx_angle){
				if (x_offset == 0){
					pun -> y = MAX_Y;
					pun -> x = MIN_X;
				}else if (y_offset == 0){
					pun -> x = MAX_X;
					pun -> y = MIN_Y;
				}

			}else if (down_dx_angle){
				if (x_offset == 0){
					pun -> y = MIN_Y;
					pun -> x = MAX_X;
				}else if (y_offset == 0){
					pun -> x = MIN_X;
					pun -> y = MAX_Y;
				}
			}else if (down_sx_angle){
				if (x_offset == 0){
					pun -> y = MIN_Y;
					pun -> x = MIN_X;
				}else if (y_offset == 0){
					pun -> x = MAX_X;
					pun -> y = MAX_Y;
				}
			}

		}else{
			if(prev_x > MAX_X){
				pun -> x = MIN_X;
			}else if(prev_x < MIN_X){
				pun -> x = MAX_X;
			}
			if(prev_y > MAX_Y){
				pun -> y = MIN_Y;
			}else if(prev_y < MIN_Y){
				pun -> y = MAX_Y;
			}
		}

	}

	if(pun_cmp_2(pun-> x,pun->y, frutto->x,frutto->y)){
		score += 1;
		*frutto = pun_gen(NULL,NULL);
		*flag_mangiato = 1;
	}else{
		*flag_mangiato = 0;
	}
};

void spostamento_singolo(punto * pun, dir dir_spostamento, punto* frutto, int *flag_mangiato) {
	switch(dir_spostamento){
		case SOPRA:
			spostamento_offset(pun, 0, -8, frutto,flag_mangiato);
			break;
		case SOTTO:
			spostamento_offset(pun, 0, 8, frutto,flag_mangiato);
			break;
		case DESTRA:
			spostamento_offset(pun, 8, 0, frutto,flag_mangiato);
			break;
		case SINISTRA:
			spostamento_offset(pun, -8, 0, frutto,flag_mangiato);
			break;
		default:
			spostamento_offset(pun, 0, 0, frutto,flag_mangiato);
			break;
	}
};

