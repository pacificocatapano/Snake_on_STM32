/*
 * punto.h
 *
 *  Created on: 28 dic 2022
 *      Author: Utente
 */

#ifndef INC_PUNTO_H_
#define INC_PUNTO_H_

#include<stdint.h>
#include<time.h>

typedef enum { false, true } bool;

typedef struct{
	uint8_t x;
	uint8_t y;
}punto;

typedef enum
{
	SOPRA = 0,
	SOTTO = 1,
	DESTRA = 2,
	SINISTRA = 3
} dir;

punto pun_gen(uint8_t *x,uint8_t *y);
bool pun_cmp(punto punto1, punto punto2);
bool pun_cmp_2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void spostamento_offset(punto * pun, int8_t x_offset, int8_t y_offset, punto* frutto,int *flag_mangiato);
void spostamento_singolo(punto * pun, dir dir_spostamento, punto* frutto, int *flag_mangiato);
uint8_t somma_uint_to_int_8(uint8_t cuint,int8_t cint);

#endif /* INC_PUNTO_H_ */
