/*
 * lock.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#include "lock.h"
#include "main.h"
#include "lock.h"

extern CLCD_Name LCD1;
extern char str[20];

void opendoor(void)
{
	HAL_GPIO_WritePin(KHOA_GPIO_Port, KHOA_Pin, 1);
	CLCD_Display(&LCD1, "    WELCOME","");
	HAL_Delay(5000);
	HAL_GPIO_WritePin(KHOA_GPIO_Port, KHOA_Pin, 0);
}
void noopendoor(void)
{
	CLCD_Display(&LCD1, "      SAI","");
	HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 1);
	HAL_Delay(2000);
	HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 0);
	HAL_Delay(3000);
}
