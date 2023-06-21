/*
 * stateCardID.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */
#include "main.h"
#include "stateCardID.h"
#include "subcardid.h"
#include "lock.h"

extern CLCD_Name LCD1;
extern uint8_t IDCard[MFRC522_MAX_LEN];
extern char str[20];

void startcard(void)
{
	sprintf(str, "ID: 0x%02X%02X%02X%02X%02X", IDCard[0], IDCard[1], IDCard[2], IDCard[3], IDCard[4]);
	swipesuccess();
	if (CheckListUID(IDCard) != 0)
	{
		opendoor();
	}
	else
	{
		noopendoor();
	}
	CLCD_Display(&LCD1, " MOI QUET THE ", "");

}


