/*
 * subcardid.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#include "subcardid.h"

extern uint32_t delayloa ;

uint8_t checkcountUID(void)
{
	uint32_t pt = StartAddressUID;
	uint8_t count = 0;
	while (Flash_Read_Byte(pt + 5) != 0xFF)
	{
		if(Flash_Read_2Byte(pt + 6) == 0xFFFF){
			if ((Flash_Read_Byte(pt + 5) >> 4) == 1)
			{
				count++;
			}
		}
		pt = pt + 8;
	}
	return count;
}
uint8_t CheckUID(uint8_t *data, uint32_t address)
{
	uint8_t arr[8];
	Flash_Read_Array(address, arr, 8);
	if (arr[6] != 0xFF)
		return 0;
	for (uint8_t i = 0; i < 5; i++)
	{
		if (data[i] != arr[i])
			return 0;
	}
	return 1;
}
uint8_t CheckListUID(uint8_t *data)
{
	uint32_t pt = StartAddressUID;
	while (Flash_Read_Byte(pt + 5) != 0xFF)
	{
		if(Flash_Read_2Byte(pt + 6) == 0xFFFF){
			if (CheckUID(data, pt) == 1)
				return *(uint8_t *)(pt + 5);
		}
		pt = pt + 8;
	}
	return 0;
}
void swipesuccess(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
	HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 1);
	HAL_Delay(delayloa);
	HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 0);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
}
