/*
 * stateFaceID.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */
#include "stateFaceID.h"
#include "main.h"
#include "lock.h"


extern CLCD_Name LCD1;
extern int8_t Rx_Buffer[128];
void startface(void)
{
	if(Rx_Buffer[0] == 'T'){
		opendoor();
	}else if(Rx_Buffer[0] == 'F'){
		noopendoor();
	}
	memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
}


