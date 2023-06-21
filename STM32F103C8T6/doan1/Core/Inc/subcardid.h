/*
 * subcardid.h
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#ifndef INC_SUBCARDID_H_
#define INC_SUBCARDID_H_

#include "main.h"

uint8_t checkcountUID(void);
uint8_t CheckUID(uint8_t *data, uint32_t address);
uint8_t CheckListUID(uint8_t *data);
void swipesuccess(void);
#endif /* INC_SUBCARDID_H_ */
