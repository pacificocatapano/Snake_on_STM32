/*
 * queue.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Utente
 */
#include "queue.h"
#include <stdlib.h>


void init(dir  * my_queue,dir direzione, int size)
{
	for (int i=0;i<size;++i){
		my_queue[i] = direzione;
	}
}

void enqueue(dir  * my_queue,dir element,int size)
{
	for (int i=size-2;i>=0;--i){
		my_queue[i+1] = my_queue[i];
	}
	my_queue[0] = element;
}



