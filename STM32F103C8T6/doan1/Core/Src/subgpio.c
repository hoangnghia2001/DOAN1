/*
 * subgpio.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */
#include "main.h"
#include "subgpio.h"

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_IT (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

uint8_t checkbuton(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1)
		return 0;
	else
	{
		HAL_Delay(50);
		if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1)	return 0;
		uint8_t i = 50;
		while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0)
		{
			HAL_Delay(10);
			i--;
			if (i == 0)
			{
				i = 250;
				while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0)
				{
					HAL_Delay(10);
					i--;
					if(i == 0)	return 3;
				}
				return 2;
			}
		}
		return 1;
	}
}


