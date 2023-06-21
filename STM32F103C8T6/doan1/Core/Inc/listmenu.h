/*
 * listmenu.h
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#ifndef INC_LISTMENU_H_
#define INC_LISTMENU_H_

#include "main.h"

void selectmenu(void);

void menucard(void);
void menuface(void);

void adduid(uint8_t key);
void removeuid(uint32_t address);
void checkthe(void);
void startadd(void);
void setaddress(void);
void remoall(void);
void resetflash(void);
uint32_t CheckKey(uint8_t key);

void addface(uint8_t key);
void removeface(uint8_t key);
uint8_t checkfaceid(uint8_t key);

#endif /* INC_LISTMENU_H_ */
