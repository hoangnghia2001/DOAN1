/*
 * subgpio.h
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#ifndef INC_SUBGPIO_H_
#define INC_SUBGPIO_H_



void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_IT (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t checkbuton(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void sendrx (char * str);
#endif /* INC_SUBGPIO_H_ */
