/*
 * snake.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Utente
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include "punto.h"
#include "queue.h"
#define	N 2

typedef struct {
	punto * punti_snake;
	dir *   q_dir;
	int size;
}snake;

void inizializza(snake * my_snake);
void muovi(snake * my_snake,dir direzione,punto * frutto);
void ingrandisci(snake * my_snake);

#endif /* INC_SNAKE_H_ */
