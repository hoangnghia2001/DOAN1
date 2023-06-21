/*
 * password.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#include "main.h"
#include "password.h"

extern CLCD_Name LCD1;
extern uint8_t exitmenu;
extern uint8_t PassWord[8];


void password(void){
	CLCD_Display(&LCD1, "NHAP PASSWORD :", "");
	exitmenu =120;
	readpassword();
	uint8_t pass[8] = {-1};
	uint8_t k=0;
	uint8_t pas = -1;
	HAL_Delay(1000);
	while(checkbuton(MENU_GPIO_Port, MENU_Pin) != 0){}
	CLCD_SetCursor(&LCD1, k, 1);
	CLCD_WriteChar(&LCD1, 95);
	while(exitmenu){
		if(checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) == 1){
			pas++;
			if(pas >= 10)	pas = 0;
			CLCD_SetCursor(&LCD1, k, 1);
			CLCD_WriteChar(&LCD1, pas + 0x30);
		}
		if(checkbuton(MENU_GPIO_Port, MENU_Pin) == 1){
			pass[k] = pas;
			k = k+1;
			pas = -1;
			if(k == 8){
				for(uint8_t i = 0; i<8; i++){
					if(pass[i] != PassWord[i]){
						return;
					}
				}
				menupass();
			}
			CLCD_SetCursor(&LCD1, k, 1);
			CLCD_WriteChar(&LCD1, 95);
		}

	}

}

void menupass(void)
{
	exitmenu = Delaymenu;
	uint8_t statusmenu = -1;
	CLCD_Display(&LCD1, "  PASSWORD", "  OPEN DOOR");
	while(exitmenu){
		if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
		{
			exitmenu = Delaymenu;
			statusmenu++;
			statusmenu = (statusmenu > 3) ? 0 : statusmenu;
			switch (statusmenu)
			{
			case 0:
				CLCD_Display(&LCD1, "  PASSWORD", "=>OPEN DOOR");
				break;
			case 1:
				CLCD_Display(&LCD1, "  PASSWORD", "=>REMOVEALL");
				break;
			case 2:
				CLCD_Display(&LCD1, "  PASSWORD", "=>CHANGEPASSWORD");
				break;
			default:
				CLCD_Display(&LCD1, "  PASSWORD", "=>EXIT        ");
				break;
			}
		}
		if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
		{
			exitmenu = Delaymenu;
			switch (statusmenu)
			{
			case 0:
				opendoor();
				CLCD_Display(&LCD1, "  PASSWORD", "=>OPEN DOOR");
				break;
			case 1:
				HAL_GPIO_WritePin(KHOA_GPIO_Port, KHOA_Pin, 1);
				HAL_Delay(5000);
				HAL_GPIO_WritePin(KHOA_GPIO_Port, KHOA_Pin, 0);
				remoall();
				startadd();
				exitmenu =0;
				CLCD_Display(&LCD1, "  PASSWORD", "=>REMOVEALL");
				break;
			case 2:
				changepass();
				exitmenu = 0;
				CLCD_Display(&LCD1, "  PASSWORD", "=>CHANGEPASSWORD");
				break;
			default:
				CLCD_Clear(&LCD1);
				exitmenu = 0;
				break;
			}
		}
	}

}

void writepassword(void){
	uint32_t pt = StartAddressPassword;
	Flash_Erase(pt);
	Flash_Write_Array(pt, PassWord, 8);
}

void readpassword(void)
{
	uint32_t pt = StartAddressPassword;
	for(uint8_t i = 0; i< 8 ; i++ ){
		PassWord[i] = Flash_Read_Byte(pt +i);
	}
}

void changepass(void)
{
	CLCD_Display(&LCD1, "  NEWPASSWORD:", "");
	exitmenu =120;
	uint8_t passs[8] = {0};
	uint8_t k=0;
	uint8_t pas = 0;
	HAL_Delay(1000);
	while(checkbuton(MENU_GPIO_Port, MENU_Pin) != 0){}
	CLCD_SetCursor(&LCD1, k, 1);
	CLCD_WriteChar(&LCD1, 0);
	while(exitmenu){
		if(checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) == 1){
			pas++;
			if(pas > 9)	pas = 0;
			CLCD_SetCursor(&LCD1, k, 1);
			CLCD_WriteChar(&LCD1, pas + 0x30);
		}
		if(checkbuton(MENU_GPIO_Port, MENU_Pin) == 1){
			passs[k] = pas;
			k = k+1;
			pas = 0;
			if(k == 8){
				for(uint8_t i = 0 ; i < 8; i++){
					PassWord[i] = passs[i];
				}
				writepassword();
				CLCD_Display(&LCD1, "CHANGE PASSWORD", "THANH CONG");
				HAL_Delay(1000);
				return;
			}
			CLCD_SetCursor(&LCD1, k, 1);
			CLCD_WriteChar(&LCD1, 48);
		}

	}
}
