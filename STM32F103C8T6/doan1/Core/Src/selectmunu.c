/*
 * selectmunu.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

/*

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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 1 ");
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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 2 ");
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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 3 ");
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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 4 ");
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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 1 ");
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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 2 ");
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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 3 ");
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
											CLCD_Clear(&LCD1);
											CLCD_SetCursor(&LCD1, 0, 0);
											CLCD_WriteString(&LCD1, "  DA CO FACE 4 ");
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
										uint8_t rmquet = 1;
										while (rmquet)
										{
											if (TM_MFRC522_Check(IDCard) == MI_OK)
											{
												swipesuccess();
												if (CheckListUID(IDCard) != 0)
												{
													removeface(checkfaceid(CheckListUID(IDCard)));
													CLCD_Display(&LCD1, "XOA THANH CONG", "");
													HAL_Delay(1000);
													if (checkcountUID() == 0)
													{
														startadd();
														rmquet = 1;
														exitmenu = 0;
														return;
													}else{
														CLCD_Display(&LCD1, "QUET FACE", "=>  BACK ");
													}

												}
												else
												{
													CLCD_Clear(&LCD1);
													CLCD_SetCursor(&LCD1, 0, 0);
													CLCD_WriteString(&LCD1, "FACE CHUA THEM");
													HAL_Delay(1000);
													CLCD_Display(&LCD1, "QUET FACE", "=>  BACK ");
												}
											}
											if (checkbuton(MENU_GPIO_Port, MENU_Pin) == 1)
											{
												rmquet = 0;
											}
										}
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
				CLCD_Display(&LCD1, "    THEM FACE", "=>  XOA FACE");
				break;
			case 2:
				checkthe();
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

*/
