/*
 * queue.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Utente
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include "punto.h"

void init(dir  * my_queue,dir direzione, int size);
void enqueue(dir  * my_queue,dir element,int size);

#endif /* INC_QUEUE_H_ */
