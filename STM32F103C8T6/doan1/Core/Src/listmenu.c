/*
 * listmenu.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#include "listmenu.h"
#include "main.h"
#include <stdio.h>

extern CLCD_Name LCD1;
extern uint8_t IDCard[MFRC522_MAX_LEN];
extern uint8_t exitmenu;
extern uint32_t AddressUID;
extern int8_t Rx_Buffer[128];
extern uint8_t PassWord[8];
char str1[8];
extern char Tx_Buffer[6];

void selectmenu(void)
{
	exitmenu = Delaymenu;
	uint8_t statusmenu = -1;
	CLCD_Display(&LCD1, "  SELECT MENU  ", "    CARDID      ");
	while(exitmenu){
		if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
		{
			exitmenu = Delaymenu;
			statusmenu++;
			statusmenu = (statusmenu > 3) ? 0 : statusmenu;
			switch (statusmenu)
			{
			case 0:
				CLCD_Display(&LCD1, "  SELECT MENU  ", "=>  CARDID      ");
				break;
			case 1:
				CLCD_Display(&LCD1, "  SELECT MENU  ", "=>  FACEID      ");
				break;
			case 2:
				CLCD_Display(&LCD1, "  SELECT MENU  ", "=>  PASSWORD    ");
				break;
			default:
				CLCD_Display(&LCD1, "  SELECT MENU  ", "=>  EXIT        ");
				break;
			}
		}
		if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
		{
			exitmenu = Delaymenu;
			switch (statusmenu)
			{
			case 0:
				menucard();
				exitmenu = Delaymenu;
				CLCD_Display(&LCD1, "  SELECT MENU  ", "=>  CARDID      ");
				break;
			case 1:
				menuface();
				exitmenu = Delaymenu;
				CLCD_Display(&LCD1, "  SELECT MENU  ", "=>  FACEID      ");
				break;
			case 2:
				readpassword();
				sprintf(str1, "%d%d%d%d%d%d%d%d",PassWord[0],PassWord[1],PassWord[2],PassWord[3],PassWord[4],PassWord[5],PassWord[6],PassWord[7]);
				CLCD_Display(&LCD1, "  PASSWORD:", str1);
				break;
			default:
				CLCD_Clear(&LCD1);
				exitmenu = 0;
				break;
			}
		}
	}
}

void menucard(void)
{
	exitmenu = Delaymenu;
	uint8_t status = -1;
	CLCD_Display(&LCD1, "     CARDID     ", "    THEM THE    ");
	while (exitmenu )
	{
		if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
		{
			exitmenu = Delaymenu;
			status++;
			status = (status > 3) ? 0 : status;
			switch (status)
			{
			case 0:
				CLCD_Display(&LCD1, "=>  THEM THE", "    XOA THE");
				break;
			case 1:
				CLCD_Display(&LCD1, "    THEM THE", "=>  XOA THE");
				break;
			case 2:
				CLCD_Display(&LCD1, "    XOA THE", "=>  TRA THE");
				break;
			default:
				CLCD_Display(&LCD1, "    TRA THE", "=>  BACK");
				break;
			}
		}
		if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
		{
			exitmenu = Delaymenu;
			switch (status)
			{
			case 0:
				CLCD_Display(&LCD1, "    SELECT ", "   THE NGUOI LON");
				uint8_t statusadd = 0;
				uint8_t back = 1;
				while (back == 1)
				{
					if (exitmenu == 0)
					{
						CLCD_Clear(&LCD1);
						HAL_Delay(1000);
						return;
					}
					if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
					{
						exitmenu = Delaymenu;
						statusadd++;
						statusadd = (statusadd > 2) ? 0 : statusadd;
						switch (statusadd)
						{
						case 1:
							CLCD_Display(&LCD1, "=> THE NGUOI LON", "   THE TRE EM");
							break;
						case 2:
							CLCD_Display(&LCD1, "   THE NGUOI LON", "=> THE TRE EM");
							break;
						default:
							CLCD_Display(&LCD1, "   THE TRE EM", "=> BACK");
							break;
						}
					}
					if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
					{
						exitmenu = Delaymenu;
						switch (statusadd)
						{
						case 1:
							CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
							uint8_t statusadd1 = 1;
							uint8_t back11 = 1;
							while (back11 == 1)
							{
								if (exitmenu == 0)
								{
									CLCD_Clear(&LCD1);
									HAL_Delay(1000);
									return;
								}
								if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
								{
									exitmenu = Delaymenu;
									statusadd1++;
									statusadd1 = (statusadd1 > 4) ? 0 : statusadd1;
									switch (statusadd1)
									{
									case 1:
										CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
										break;
									case 2:
										CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
										break;
									case 3:
										CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
										break;
									case 4:
										CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
										break;
									default:
										CLCD_Display(&LCD1, "    THE 4 ", "=>  BACK ");
										break;
									}
								}
								if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
								{
									exitmenu = Delaymenu;
									uint8_t keyadd1 = (statusadd << 4) + statusadd1;
									switch (statusadd1)
									{
									case 1:
										if (CheckKey(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 1 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
										}
										else
										{
											adduid(keyadd1);
											CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
										}
										break;
									case 2:
										if (CheckKey(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 2 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
										}
										else
										{
											adduid(keyadd1);
											CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
										}
										break;
									case 3:
										if (CheckKey(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 3 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
										}
										else
										{
											adduid(keyadd1);
											CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
										}
										break;
									case 4:
										if (CheckKey(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 4 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
										}
										else
										{
											adduid(keyadd1);
											CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
										}
										break;
									default:
										back11 = 0;
										break;
									}
								}
							}
							CLCD_Display(&LCD1, "=> THE NGUOI LON", "   THE TRE EM");
							break;
						case 2:
							CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
							uint8_t statusadd2 = 1;
							uint8_t back12 = 1;
							while (back12 == 1)
							{
								if (exitmenu == 0)
								{
									CLCD_Clear(&LCD1);
									HAL_Delay(1000);
									return;
								}
								if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
								{
									exitmenu = Delaymenu;
									statusadd2++;
									statusadd2 = (statusadd2 > 4) ? 0 : statusadd2;
									switch (statusadd2)
									{
									case 1:
										CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
										break;
									case 2:
										CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
										break;
									case 3:
										CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
										break;
									case 4:
										CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
										break;
									default:
										CLCD_Display(&LCD1, "    THE 4 ", "=>  BACK ");
										break;
									}
								}
								if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
								{
									exitmenu = Delaymenu;
									uint8_t keyadd2 = (statusadd << 4) + statusadd2;
									switch (statusadd2)
									{
									case 1:
										if (CheckKey(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 1 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
										}
										else
										{
											adduid(keyadd2);
											CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
										}
										break;
									case 2:
										if (CheckKey(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 2 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
										}
										else
										{
											adduid(keyadd2);
											CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
										}
										break;
									case 3:
										if (CheckKey(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 3 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
										}
										else
										{
											adduid(keyadd2);
											CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
										}
										break;
									case 4:
										if (CheckKey(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO THE 4 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
										}
										else
										{
											adduid(keyadd2);
											CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
										}
										break;
									default:
										back12 = 0;
										break;
									}
								}
							}
							CLCD_Display(&LCD1, "   THE NGUOI LON", "=> THE TRE EM");
						default:
							back = 0;
							break;
						}
					}
				}
				CLCD_Display(&LCD1, "=>  THEM THE", "    XOA THE");
				break;
			case 1:
				CLCD_Display(&LCD1, "     SELECT ", "   XOA 1 THE");
				uint8_t statusremove = -1;
				uint8_t backrm = 1;
				while (backrm == 1)
				{
					if (exitmenu == 0)
					{
						CLCD_Clear(&LCD1);
						HAL_Delay(1000);
						return;
					}
					if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
					{
						exitmenu = Delaymenu;
						statusremove++;
						statusremove = (statusremove > 2) ? 0 : statusremove;
						switch (statusremove)
						{
						case 0:
							CLCD_Display(&LCD1, "=> XOA 1 THE", "   XOA TAT CA");
							break;
						case 1:
							CLCD_Display(&LCD1, "   XOA 1 THE", "=> XOA TAT CA");
							CLCD_Clear(&LCD1);
							CLCD_SetCursor(&LCD1, 0, 0);
							CLCD_WriteString(&LCD1, "   XOA 1 THE");
							CLCD_SetCursor(&LCD1, 0, 1);
							CLCD_WriteString(&LCD1, "=> XOA TAT CA");
							break;
						default:
							CLCD_Display(&LCD1, "   XOA TAT CA", "=> BACK");
							break;
						}
					}
					if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
					{
						exitmenu = Delaymenu;
						switch (statusremove)
						{
						case 0:
							CLCD_Display(&LCD1, "=> CHON THE", "   QUET THE");
							uint8_t statusrm1 = 0;
							uint8_t backrm1 = 1;
							while (backrm1 == 1)
							{
								if (exitmenu == 0)
								{
									CLCD_Clear(&LCD1);
									HAL_Delay(1000);
									return;
								}
								if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
								{
									statusrm1++;
									statusrm1 = (statusrm1 > 2) ? 0 : statusrm1;
									switch (statusrm1)
									{
									case 0:
										CLCD_Display(&LCD1, "=> CHON THE", "   QUET THE");
										break;
									case 1:
										CLCD_Display(&LCD1, "   CHON THE", "=> QUET THE");
										;
										break;
									default:
										CLCD_Display(&LCD1, "   QUET THE", "=> BACK");
										break;
									}
								}
								if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
								{
									exitmenu = Delaymenu;
									switch (statusrm1)
									{
									case 0:
										CLCD_Display(&LCD1, "=> THE NGUOI LON", "   THE TRE EM");
										uint8_t statusadd = 1;
										uint8_t backrm10 = 1;
										while (backrm10 == 1)
										{
											if (exitmenu == 0)
											{
												CLCD_Clear(&LCD1);
												HAL_Delay(1000);
												return;
											}
											if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
											{
												exitmenu = Delaymenu;
												statusadd++;
												statusadd = (statusadd > 2) ? 0 : statusadd;
												switch (statusadd)
												{
												case 1:
													CLCD_Display(&LCD1, "=> THE NGUOI LON", "   THE TRE EM");
													break;
												case 2:
													CLCD_Display(&LCD1, "   THE NGUOI LON", "=> THE TRE EM");
													break;
												default:
													CLCD_Display(&LCD1, "   THE TRE EM", "=> BACK");
													break;
												}
											}
											if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
											{
												exitmenu = Delaymenu;
												switch (statusadd)
												{
												case 1:
													CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
													uint8_t statusadd1 = 1;
													uint8_t back11 = 1;
													while (back11 == 1)
													{
														if (exitmenu == 0)
														{
															CLCD_Clear(&LCD1);
															HAL_Delay(1000);
															return;
														}
														if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
														{
															exitmenu = Delaymenu;
															statusadd1++;
															statusadd1 = (statusadd1 > 4) ? 0 : statusadd1;
															switch (statusadd1)
															{
															case 1:
																CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
																break;
															case 2:
																CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
																break;
															case 3:
																CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
																break;
															case 4:
																CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
																break;
															default:
																CLCD_Display(&LCD1, "    THE 4 ", "=>  BACK ");
																break;
															}
														}
														if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
														{
															exitmenu = Delaymenu;
															uint8_t keyadd1 = (statusadd << 4) + statusadd1;
															switch (statusadd1)
															{
															case 1:
																if (CheckKey(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 1 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
																}
																else
																{
																	removeuid(CheckKey(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
																	}
																}
																break;
															case 2:
																if (CheckKey(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 2 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
																}
																else
																{
																	removeuid(CheckKey(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
																	}
																}
																break;
															case 3:
																if (CheckKey(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 3 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
																}
																else
																{
																	removeuid(CheckKey(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
																	}
																}
																break;
															case 4:
																if (CheckKey(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 4 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
																}
																else
																{
																	removeuid(CheckKey(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
																	}
																}
																break;
															default:
																back11 = 0;
																break;
															}
														}
													}
													CLCD_Display(&LCD1, "=> THE NGUOI LON", "   THE TRE EM");
													break;
												case 2:
													CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
													uint8_t statusadd2 = 1;
													uint8_t back12 = 1;
													while (back12 == 1)
													{
														if (exitmenu == 0)
														{
															CLCD_Clear(&LCD1);
															HAL_Delay(1000);
															return;
														}
														if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
														{
															exitmenu = Delaymenu;
															statusadd2++;
															statusadd2 = (statusadd2 > 4) ? 0 : statusadd2;
															switch (statusadd2)
															{
															case 1:
																CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
																break;
															case 2:
																CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
																break;
															case 3:
																CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
																break;
															case 4:
																CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
																break;
															default:
																CLCD_Display(&LCD1, "    THE 4 ", "=>  BACK ");
																break;
															}
														}
														if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
														{
															exitmenu = Delaymenu;
															uint8_t keyadd2 = (statusadd << 4) + statusadd2;
															switch (statusadd2)
															{
															case 1:
																if (CheckKey(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 1 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
																}
																else
																{
																	removeuid(CheckKey(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 1 ", "    THE 2 ");
																}
																break;
															case 2:
																if (CheckKey(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 2 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
																}
																else
																{
																	removeuid(CheckKey(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 2 ", "    THE 3 ");
																}
																break;
															case 3:
																if (CheckKey(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 3 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
																}
																else
																{
																	removeuid(CheckKey(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 3 ", "    THE 4 ");
																}
																break;
															case 4:
																if (CheckKey(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO THE 4 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
																}
																else
																{
																	removeuid(CheckKey(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  THE 4 ", "    BACK ");
																}
																break;
															default:
																back12 = 0;
																break;
															}
														}
													}
													CLCD_Display(&LCD1, "   THE NGUOI LON", "=> THE TRE EM");
													break;
												default:
													backrm10 = 0;
													break;
												}
											}
										}
										CLCD_Display(&LCD1, "=> CHON THE", "   QUET THE");
										break;
									case 1:
										CLCD_Display(&LCD1, "QUET THE", "=>  BACK ");
										uint8_t rmquet = 1;
										while (rmquet)
										{
											if (TM_MFRC522_Check(IDCard) == MI_OK)
											{
												swipesuccess();
												if (CheckListUID(IDCard) != 0)
												{
													removeuid(CheckKey(CheckListUID(IDCard)));
													CLCD_Display(&LCD1, "XOA THANH CONG", "");
													HAL_Delay(1000);
													if (checkcountUID() == 0)
													{
														startadd();
														rmquet = 1;
														exitmenu = 0;
														return;
													}else{
														CLCD_Display(&LCD1, "QUET THE", "=>  BACK ");
													}

												}
												else
												{
													CLCD_Display(&LCD1, "THE CHUA THEM", "");
													HAL_Delay(1000);
													CLCD_Display(&LCD1, "QUET THE", "=>  BACK ");
												}
											}
											if (checkbuton(MENU_GPIO_Port, MENU_Pin) == 1)
											{
												rmquet = 0;
											}
										}
										CLCD_Display(&LCD1, "   CHON THE", "=> QUET THE");;
										break;
									default:
										backrm1 = 0;
										break;
									}
								}
							}
							CLCD_Display(&LCD1, "=> XOA 1 THE", "   XOA TAT CA");
							break;
						case 1:
							remoall();
							startadd();
							exitmenu = 0;
							break;
						default:
							backrm = 0;
							break;
						}
					}
				}
				CLCD_Display(&LCD1, "    THEM THE", "=>  XOA THE");
				break;
			case 2:
				checkthe();
				CLCD_Display(&LCD1, "    XOA THE", "=>  TRA THE");
				break;
			default:
				exitmenu = 0;
				break;
			}
		}
	}
	CLCD_Clear(&LCD1);
}

void menuface(void) {
	exitmenu = Delaymenu;
	uint8_t status = -1;
	CLCD_Display(&LCD1, "     CARDID     ", "    THEM FACE    ");
	while (exitmenu )
	{
		if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
		{
			exitmenu = Delaymenu;
			status++;
			status = (status > 3) ? 0 : status;
			switch (status)
			{
			case 0:
				CLCD_Display(&LCD1, "=>  THEM FACE", "    XOA FACE");
				break;
			case 1:
				CLCD_Display(&LCD1, "    THEM FACE", "=>  XOA FACE");
				break;
			case 2:
				CLCD_Display(&LCD1, "    XOA FACE", "=>  TRA FACE");
				break;
			default:
				CLCD_Display(&LCD1, "    TRA FACE", "=>  BACK");
				break;
			}
		}
		if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
		{
			exitmenu = Delaymenu;
			switch (status)
			{
			case 0:
				CLCD_Display(&LCD1, "    SELECT ", "FACE NGUOI LON");
				uint8_t statusadd = 0;
				uint8_t back = 1;
				while (back == 1)
				{
					if (exitmenu == 0)
					{
						CLCD_Clear(&LCD1);
						HAL_Delay(1000);
						return;
					}
					if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
					{
						exitmenu = Delaymenu;
						statusadd++;
						statusadd = (statusadd > 2) ? 0 : statusadd;
						switch (statusadd)
						{
						case 1:
							CLCD_Display(&LCD1, "=>FACE NGUOI LON", "  FACE TRE EM");
							break;
						case 2:
							CLCD_Display(&LCD1, "  FACE NGUOI LON", "=>FACE TRE EM");
							break;
						default:
							CLCD_Display(&LCD1, "  FACE TRE EM", "=> BACK");
							break;
						}
					}
					if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
					{
						exitmenu = Delaymenu;
						switch (statusadd)
						{
						case 1:
							CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
							uint8_t statusadd1 = 1;
							uint8_t back11 = 1;
							while (back11 == 1)
							{
								if (exitmenu == 0)
								{
									CLCD_Clear(&LCD1);
									HAL_Delay(1000);
									return;
								}
								if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
								{
									exitmenu = Delaymenu;
									statusadd1++;
									statusadd1 = (statusadd1 > 4) ? 0 : statusadd1;
									switch (statusadd1)
									{
									case 1:
										CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
										break;
									case 2:
										CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
										break;
									case 3:
										CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
										break;
									case 4:
										CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
										break;
									default:
										CLCD_Display(&LCD1, "    FACE 4 ", "=>  BACK ");
										break;
									}
								}
								if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
								{
									exitmenu = Delaymenu;
									uint8_t keyadd1 = (statusadd << 4) + statusadd1;
									switch (statusadd1)
									{
									case 1:
										if (checkfaceid(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 1 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
										}
										else
										{
											addface(keyadd1);
											CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
										}
										break;
									case 2:
										if (checkfaceid(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 2 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
										}
										else
										{
											addface(keyadd1);
											CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
										}
										break;
									case 3:
										if (checkfaceid(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 3 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
										}
										else
										{
											addface(keyadd1);
											CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
										}
										break;
									case 4:
										if (checkfaceid(keyadd1) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 4 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
										}
										else
										{
											addface(keyadd1);
											CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
										}
										break;
									default:
										back11 = 0;
										break;
									}
								}
							}
							CLCD_Display(&LCD1, "=>FACE NGUOI LON", "  FACE TRE EM");
							break;
						case 2:
							CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
							uint8_t statusadd2 = 1;
							uint8_t back12 = 1;
							while (back12 == 1)
							{
								if (exitmenu == 0)
								{
									CLCD_Clear(&LCD1);
									HAL_Delay(1000);
									return;
								}
								if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
								{
									exitmenu = Delaymenu;
									statusadd2++;
									statusadd2 = (statusadd2 > 4) ? 0 : statusadd2;
									switch (statusadd2)
									{
									case 1:
										CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
										break;
									case 2:
										CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
										break;
									case 3:
										CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
										break;
									case 4:
										CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
										break;
									default:
										CLCD_Display(&LCD1, "    FACE 4 ", "=>  BACK ");
										break;
									}
								}
								if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
								{
									exitmenu = Delaymenu;
									uint8_t keyadd2 = (statusadd << 4) + statusadd2;
									switch (statusadd2)
									{
									case 1:
										if (checkfaceid(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 1 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
										}
										else
										{
											addface(keyadd2);
											CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
										}
										break;
									case 2:
										if (checkfaceid(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 2 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
										}
										else
										{
											addface(keyadd2);
											CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
										}
										break;
									case 3:
										if (checkfaceid(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 3 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
										}
										else
										{
											addface(keyadd2);
											CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
										}
										break;
									case 4:
										if (checkfaceid(keyadd2) != 0)
										{
											CLCD_Display(&LCD1, "  DA CO FACE 4 ", "");
											HAL_Delay(1000);
											CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
										}
										else
										{
											addface(keyadd2);
											CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
										}
										break;
									default:
										back12 = 0;
										break;
									}
								}
							}
							CLCD_Display(&LCD1, "  FACE NGUOI LON", "=>FACE TRE EM");
						default:
							back = 0;
							break;
						}
					}
				}
				CLCD_Display(&LCD1, "=>  THEM FACE", "    XOA FACE");
				break;
			case 1:
				CLCD_Display(&LCD1, "     SELECT ", "   XOA 1 FACE");
				uint8_t statusremove = -1;
				uint8_t backrm = 1;
				while (backrm == 1)
				{
					if (exitmenu == 0)
					{
						CLCD_Clear(&LCD1);
						HAL_Delay(1000);
						return;
					}
					if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
					{
						exitmenu = Delaymenu;
						statusremove++;
						statusremove = (statusremove > 2) ? 0 : statusremove;
						switch (statusremove)
						{
						case 0:
							CLCD_Display(&LCD1, "=> XOA 1 FACE", "   XOA TAT CA");
							break;
						case 1:
							CLCD_Display(&LCD1, "   XOA 1 FACE", "=> XOA TAT CA");
							CLCD_Clear(&LCD1);
							CLCD_SetCursor(&LCD1, 0, 0);
							CLCD_WriteString(&LCD1, "   XOA 1 FACE");
							CLCD_SetCursor(&LCD1, 0, 1);
							CLCD_WriteString(&LCD1, "=> XOA TAT CA");
							break;
						default:
							CLCD_Display(&LCD1, "   XOA TAT CA", "=> BACK");
							break;
						}
					}
					if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
					{
						exitmenu = Delaymenu;
						switch (statusremove)
						{
						case 0:
							CLCD_Display(&LCD1, "=> CHON FACE", "   QUET FACE");
							uint8_t statusrm1 = 0;
							uint8_t backrm1 = 1;
							while (backrm1 == 1)
							{
								if (exitmenu == 0)
								{
									CLCD_Clear(&LCD1);
									HAL_Delay(1000);
									return;
								}
								if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
								{
									statusrm1++;
									statusrm1 = (statusrm1 > 2) ? 0 : statusrm1;
									switch (statusrm1)
									{
									case 0:
										CLCD_Display(&LCD1, "=> CHON FACE", "   QUET FACE");
										break;
									case 1:
										CLCD_Display(&LCD1, "   CHON FACE", "=> QUET FACE");
										;
										break;
									default:
										CLCD_Display(&LCD1, "   QUET FACE", "=> BACK");
										break;
									}
								}
								if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
								{
									exitmenu = Delaymenu;
									switch (statusrm1)
									{
									case 0:
										CLCD_Display(&LCD1, "=>FACE NGUOI LON", "  FACE TRE EM");
										uint8_t statusadd = 1;
										uint8_t backrm10 = 1;
										while (backrm10 == 1)
										{
											if (exitmenu == 0)
											{
												CLCD_Clear(&LCD1);
												HAL_Delay(1000);
												return;
											}
											if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
											{
												exitmenu = Delaymenu;
												statusadd++;
												statusadd = (statusadd > 2) ? 0 : statusadd;
												switch (statusadd)
												{
												case 1:
													CLCD_Display(&LCD1, "=>FACE NGUOI LON", "  FACE TRE EM");
													break;
												case 2:
													CLCD_Display(&LCD1, "  FACE NGUOI LON", "=>FACE TRE EM");
													break;
												default:
													CLCD_Display(&LCD1, "  FACE TRE EM", "=> BACK");
													break;
												}
											}
											if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
											{
												exitmenu = Delaymenu;
												switch (statusadd)
												{
												case 1:
													CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
													uint8_t statusadd1 = 1;
													uint8_t back11 = 1;
													while (back11 == 1)
													{
														if (exitmenu == 0)
														{
															CLCD_Clear(&LCD1);
															HAL_Delay(1000);
															return;
														}
														if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
														{
															exitmenu = Delaymenu;
															statusadd1++;
															statusadd1 = (statusadd1 > 4) ? 0 : statusadd1;
															switch (statusadd1)
															{
															case 1:
																CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
																break;
															case 2:
																CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
																break;
															case 3:
																CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
																break;
															case 4:
																CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
																break;
															default:
																CLCD_Display(&LCD1, "    FACE 4 ", "=>  BACK ");
																break;
															}
														}
														if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
														{
															exitmenu = Delaymenu;
															uint8_t keyadd1 = (statusadd << 4) + statusadd1;
															switch (statusadd1)
															{
															case 1:
																if (checkfaceid(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 1 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
																}
																else
																{
																	removeface(checkfaceid(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
																	}
																}
																break;
															case 2:
																if (checkfaceid(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 2 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
																}
																else
																{
																	removeface(checkfaceid(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
																	}
																}
																break;
															case 3:
																if (checkfaceid(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 3 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
																}
																else
																{
																	removeface(checkfaceid(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
																	}
																}
																break;
															case 4:
																if (checkfaceid(keyadd1) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 4 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
																}
																else
																{
																	removeface(checkfaceid(keyadd1));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	if (checkcountUID() == 0)
																	{
																		startadd();
																		exitmenu = 0;
																	}
																	else
																	{
																		CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
																	}
																}
																break;
															default:
																back11 = 0;
																break;
															}
														}
													}
													CLCD_Display(&LCD1, "=>FACE NGUOI LON", "  FACE TRE EM");
													break;
												case 2:
													CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
													uint8_t statusadd2 = 1;
													uint8_t back12 = 1;
													while (back12 == 1)
													{
														if (exitmenu == 0)
														{
															CLCD_Clear(&LCD1);
															HAL_Delay(1000);
															return;
														}
														if (checkbuton(SELECCT_GPIO_Port, SELECCT_Pin) != 0)
														{
															exitmenu = Delaymenu;
															statusadd2++;
															statusadd2 = (statusadd2 > 4) ? 0 : statusadd2;
															switch (statusadd2)
															{
															case 1:
																CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
																break;
															case 2:
																CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
																break;
															case 3:
																CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
																break;
															case 4:
																CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
																break;
															default:
																CLCD_Display(&LCD1, "    FACE 4 ", "=>  BACK ");
																break;
															}
														}
														if (checkbuton(MENU_GPIO_Port, MENU_Pin) != 0)
														{
															exitmenu = Delaymenu;
															uint8_t keyadd2 = (statusadd << 4) + statusadd2;
															switch (statusadd2)
															{
															case 1:
																if (checkfaceid(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 1 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
																}
																else
																{
																	removeface(checkfaceid(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 1 ", "    FACE 2 ");
																}
																break;
															case 2:
																if (checkfaceid(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 2 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
																}
																else
																{
																	removeface(checkfaceid(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 2 ", "    FACE 3 ");
																}
																break;
															case 3:
																if (checkfaceid(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 3 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
																}
																else
																{
																	removeface(checkfaceid(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 3 ", "    FACE 4 ");
																}
																break;
															case 4:
																if (checkfaceid(keyadd2) == 0)
																{
																	CLCD_Display(&LCD1, "CHUA CO FACE 4 ", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
																}
																else
																{
																	removeface(checkfaceid(keyadd2));
																	CLCD_Display(&LCD1, "XOA THANH CONG", "");
																	HAL_Delay(1000);
																	CLCD_Display(&LCD1, "=>  FACE 4 ", "    BACK ");
																}
																break;
															default:
																back12 = 0;
																break;
															}
														}
													}
													CLCD_Display(&LCD1, "  FACE NGUOI LON", "=>FACE TRE EM");
													break;
												default:
													backrm10 = 0;
													break;
												}
											}
										}
										CLCD_Display(&LCD1, "=> CHON FACE", "   QUET FACE");
										break;
									case 1:
										CLCD_Display(&LCD1, "QUET FACE", "=>  BACK ");
										CDC_Transmit_FS("Rem.00", 6);
										uint8_t rmquet = 1;
										while (rmquet)
										{
											if( Rx_Buffer[0] == 'T'){
												CLCD_Display(&LCD1, "XOA THANH CONG", "");
												HAL_Delay(2000);
												memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
												CLCD_Display(&LCD1, "QUET FACE", "=>  BACK ");
											}
											if (checkbuton(MENU_GPIO_Port, MENU_Pin) == 1)
											{
												rmquet = 0;
											}
										}
										CDC_Transmit_FS("Exit  ", 6);
										CLCD_Display(&LCD1, "   CHON FACE", "=> QUET FACE");;
										break;
									default:
										backrm1 = 0;
										break;
									}
								}
							}
							CLCD_Display(&LCD1, "=> XOA 1 FACE", "   XOA TAT CA");
							break;
						case 1:
							sprintf(Tx_Buffer , "Rem.99" );
							CDC_Transmit_FS(Tx_Buffer, 6);
							CLCD_Display(&LCD1, "WAITING....", "");
							exitmenu = 60;
							while(exitmenu != 0){
								if(Rx_Buffer[0] == 'T'){
									CLCD_Display(&LCD1, "XOA THANH CONG", "");
									memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
									break;
								}
							}
							exitmenu = 0;
							break;
						default:
							backrm = 0;
							break;
						}
					}
				}
				CLCD_Display(&LCD1, "    THEM FACE", "=>  XOA FACE");
				break;
			case 2:
				checkface();
				CDC_Transmit_FS("Exit  ", 6);
				CLCD_Display(&LCD1, "    XOA FACE", "=>  TRA FACE");
				break;
			default:
				exitmenu = 0;
				break;
			}
		}
	}
	CLCD_Clear(&LCD1);
}

void adduid(uint8_t key)
{
	setaddress();
	CLCD_Display(&LCD1, "QUET THE", "=>  BACK ");
	while (exitmenu)
	{
		if (TM_MFRC522_Check(IDCard) == MI_OK)
		{
			swipesuccess();
			if (CheckListUID(IDCard) == 0)
			{
				IDCard[5] = key;
				Flash_Write_Array(AddressUID, IDCard, 6);
				AddressUID += 8;
				resetflash();
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "THANH CONG");
				HAL_Delay(1000);
				return;
			}
			else
			{
				CLCD_Display(&LCD1, "THE DA TON TAI", "");
				HAL_Delay(1000);
				CLCD_Display(&LCD1, "QUET THE", "=>  BACK ");
			}
		}
		if (checkbuton(MENU_GPIO_Port, MENU_Pin) == 1)
		{
			return;
		}
	}
}
void checkthe(void)
{
	exitmenu = 30;
	CLCD_Display(&LCD1, "QUET THE", "=>  BACK");
	while (exitmenu )
	{
		if (TM_MFRC522_Check(IDCard) == MI_OK)
		{
			swipesuccess();
			if (CheckListUID(IDCard) == 0)
			{
				CLCD_Display(&LCD1, "THE CHUA THEM", "");
				HAL_Delay(1000);
				CLCD_Display(&LCD1, "QUET THE", "=>  BACK");
				HAL_Delay(1000);
			}
			else
			{
				uint8_t key = CheckListUID(IDCard);
				uint8_t key2 = key & 0x0f;
				uint8_t key1 = key >> 4;
				CLCD_Clear(&LCD1);
				switch (key1)
				{
				case 1:
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "THE NGUOI LON");
					break;
				default:
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "THE TRE EM");
					break;
				}
				switch (key2)
				{
				case 1:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "THE 1");
					break;
				case 2:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "THE 2");
					break;
				case 3:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "THE 3");
					break;
				default:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "THE 4");
					break;
				}
				HAL_Delay(1000);
				CLCD_Display(&LCD1, "QUET THE", "=>  BACK");
			}
		}
		if (checkbuton(MENU_GPIO_Port, MENU_Pin) == 1)
		{
			return;
		}
	}
}
uint32_t CheckKey(uint8_t key)
{
	uint32_t pt = StartAddressUID;
	while (Flash_Read_Byte(pt + 5) != 0xFF)
	{
		if(Flash_Read_2Byte(pt + 6) == 0xFFFF){
			if (*(uint8_t *)(pt + 5) == key)
				return pt;
		}
		pt = pt + 8;
	}
	return 0;
}
void removeuid(uint32_t addressrm)
{
	Flash_Write_2Byte(addressrm + 6, 0x0000);
}
void startadd(void)
{
	CLCD_Display(&LCD1, "MOI QUET THE", "THE NGUOI LON");
	setaddress();
	while (1)
		{
			if (TM_MFRC522_Check(IDCard) == MI_OK)
			{
				swipesuccess();
				if (CheckListUID(IDCard) == 0)
				{
					IDCard[5] = 0x11;
					Flash_Write_Array(AddressUID, IDCard, 6);
					AddressUID += 8;
					break;
				}
				else
				{
					CLCD_Clear(&LCD1);
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "THE DA TON TAI");
					HAL_Delay(1000);
					CLCD_Display(&LCD1, "MOI QUET THE", "THE NGUOI LON");
				}
			}
		}
	CLCD_Display(&LCD1, "THEM THANH CONG", "THE NGUOI LON");
	HAL_Delay(1000);
	CLCD_Clear(&LCD1);
}
void setaddress(void){
	uint32_t pt = StartAddressUID;
	while (Flash_Read_Byte(pt + 5) != 0xFF)
	{
		pt = pt + 8;
	}
	AddressUID = pt;
}


void remoall(){
	uint32_t pt = StartAddressUID;
	while(Flash_Read_8Byte(pt) != 0xFFFFFFFFFFFFFFFF){
		Flash_Erase(pt);
		pt = pt + 0x400;
		if(pt == 0x800FC00)
			break;
	}
}
void resetflash(void){
	if(AddressUID == 0x800FC00){
		uint32_t pt = StartAddressUID;
		uint8_t uidcard[8][6];
		uint8_t k = 0;
		while(pt != 0x800FC00){
			if(Flash_Read_2Byte(pt + 6) == 0xFFFF){
				for(uint8_t i = 0; i < 6; i++){
					uidcard[k][i] = Flash_Read_Byte(pt+i);
				}
				k++;
			}

			pt += 8;
		}
		remoall();
		pt = StartAddressUID;
		for(uint8_t i = 0; i < k; i++ ){
			Flash_Write_Array(pt, uidcard[i], 6);
			pt += 8;
		}
	}
}

void addface(uint8_t key)
{
	sprintf(Tx_Buffer , "Add.%2d", key );
	CDC_Transmit_FS(Tx_Buffer, 6);
	CLCD_Display(&LCD1, "WAITING....", "");
	exitmenu = 60;
	while(exitmenu != 0){
		if(Rx_Buffer[0] == 'T'){
			CLCD_Display(&LCD1, "THEM THANH CONG", "");
			break;
		}
		else if(Rx_Buffer[0] == 'F'){
			CLCD_Display(&LCD1, "FACE DA TON TAI", "");
			break;
		}
	}
	memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
}
void removeface(uint8_t key)
{
	sprintf(Tx_Buffer , "Rem.%2d", key );
	CDC_Transmit_FS(Tx_Buffer, 6);
	CLCD_Display(&LCD1, "WAITING....", "");
	exitmenu = 60;
	while(exitmenu != 0){
		if(Rx_Buffer[0] == 'T'){
			CLCD_Display(&LCD1, "XOA THANH CONG", "");
			break;
		}
		else if(Rx_Buffer[0] == 'F'){
			CLCD_Display(&LCD1, "FACE CHUA THEM", "");
			break;
		}
	}
	memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
}
uint8_t checkfaceid(uint8_t key){
	sprintf(Tx_Buffer , "Che.%2d", key );
	CDC_Transmit_FS(Tx_Buffer, 6);
	while(Rx_Buffer[0] ==0){
		continue;
	}
	CLCD_Display(&LCD1, Rx_Buffer, "");
	HAL_Delay(1000);
	if(Rx_Buffer[0] == '0'){
		return 0;
	}
	return key;

}

void checkface(void)
{
	CDC_Transmit_FS("Che.00", 6);
	exitmenu = 60;
	CLCD_Display(&LCD1, "QUET FACE", "=>  BACK");
	while (exitmenu )
	{
		if (Rx_Buffer[0] != 0)
		{

			if (Rx_Buffer[0] == 'F')
			{
				CLCD_Display(&LCD1, "FACE CHUA THEM", "");
				HAL_Delay(1000);
				CLCD_Display(&LCD1, "QUET FACE", "=>  BACK");
				HAL_Delay(1000);
			}
			else
			{
				uint8_t key = (Rx_Buffer[5] -48)*10 + (Rx_Buffer[6] -48) ;
				uint8_t key2 = key & 0x0f;
				uint8_t key1 = key >> 4;
				CLCD_Clear(&LCD1);
				switch (key1)
				{
				case 1:
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "FACE NGUOI LON");
					break;
				default:
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "FACE TRE EM");
					break;
				}
				switch (key2)
				{
				case 1:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "FACE 1");
					break;
				case 2:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "FACE 2");
					break;
				case 3:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "FACE 3");
					break;
				default:
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "FACE 4");
					break;
				}
				HAL_Delay(2000);
				CLCD_Display(&LCD1, "QUET FACE", "=>  BACK");
			}
			memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
		}
		if (checkbuton(MENU_GPIO_Port, MENU_Pin) == 1)
		{
			break;
		}
	}
	CDC_Transmit_FS("Exit  ", 6);
}
