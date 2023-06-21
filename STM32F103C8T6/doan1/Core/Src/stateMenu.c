/*
 * stateMenu.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */
#include "stateMenu.h"
#include "main.h"
#include "subcardid.h"
#include "subgpio.h"
#include "listmenu.h"


extern CLCD_Name LCD1;
extern uint8_t IDCard[MFRC522_MAX_LEN];
extern uint8_t exitmenu;
extern uint8_t buton;
extern int8_t Rx_Buffer[128];


void startmenu(void)
{

	HAL_NVIC_DisableIRQ(MENU_EXTI_IRQn);
	Set_Pin_Input(MENU_GPIO_Port, MENU_Pin);
	exitmenu = Delaymenu;
	CLCD_SetCursor(&LCD1, 0, 1);
	CLCD_WriteString(&LCD1, "THE NGUOI LON");
	uint8_t key = 0;
	uint8_t stat ;
	while (exitmenu )
	{
		if (TM_MFRC522_Check(IDCard) == MI_OK)
		{
			swipesuccess();
			key = CheckListUID(IDCard);
			key = key >> 4;
			break;
		}
		if(Rx_Buffer[0] != 0){
			if (Rx_Buffer[0] == 'T')
			{
				key = (Rx_Buffer[5] -48)*10 + (Rx_Buffer[6] -48) ;
				key = key >> 4;
			} else
			{
				key = 2;
			}
			memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
			break;
		}
		stat = checkbuton(MENU_GPIO_Port, MENU_Pin);
		switch(stat){
		case 0:
			break;
		case 3:
			password();
			key = 99;
			exitmenu = 0;
			break;
		default :
			key = 2;
			exitmenu = 0;
			break;
		}
	}
	switch (key){
	case 1:
		CDC_Transmit_FS("Stop  ", 6);
		selectmenu();
		CDC_Transmit_FS("Ready ", 6);
		break;
	case 99:
		break;
	default:
		CLCD_Display(&LCD1, "      SAI ", "KHONG CO QUYEN");
		HAL_Delay(1000);
		CLCD_Clear(&LCD1);
		break;
	}
	buton = 1;
	Set_Pin_IT(MENU_GPIO_Port, MENU_GPIO_Port);
	CLCD_Clear(&LCD1);
}

