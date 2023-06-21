/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "state.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

enum Status states;
uint8_t IDCard[MFRC522_MAX_LEN];
int8_t Rx_Buffer[128];
uint8_t exitmenu = 255;
uint8_t buton = 1;
uint8_t statustask = 0;
CLCD_Name LCD1;
uint32_t AddressUID = StartAddressUID;
uint8_t PassWord[8]; // = {0,0,0,0,0,0,0,0} ;
uint32_t delayloa = 100;
char str[20];
char Tx_Buffer[6];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */





void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(states == Free)
		buton = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	if(exitmenu > 0)
		exitmenu --;
	else exitmenu = 0;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

	TM_MFRC522_Init();

	CLCD_4BIT_Init(&LCD1, 16, 2, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin,
				   D4_GPIO_Port, D4_Pin, D5_GPIO_Port, D5_Pin,
				   D6_GPIO_Port, D6_Pin, D7_GPIO_Port, D7_Pin);
	states = Free;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//	writepassword();
	HAL_TIM_Base_Start_IT(&htim2);
	if (checkcountUID() == 0)
	{
		startadd();
	}
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		CLCD_SetCursor(&LCD1, 0, 0);
		CLCD_WriteString(&LCD1, " MOI QUET THE ");
		if(buton == 0){
			states = Menu;
		}else if(TM_MFRC522_Check(IDCard) == MI_OK){
			states = CardID;
		}else if(Rx_Buffer[0] != 0){
			states = FaceID;
		}
		statemachineupdate(&states);
		HAL_Delay(1000);
//		if (buton == 0)
//		{
//			statustask = 1;
//			HAL_NVIC_DisableIRQ(MENU_EXTI_IRQn);
//			Set_Pin_Input(MENU_GPIO_Port, MENU_Pin);
//			exitmenu = 15;
//			CLCD_SetCursor(&LCD1, 0, 1);
//			CLCD_WriteString(&LCD1, "THE NGUOI LON");
//			uint8_t key = 0;
//			uint8_t stat ;
//			while (exitmenu )
//			{
//				if (TM_MFRC522_Check(IDCard) == MI_OK)
//				{
//					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
//					HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 1);
//					HAL_Delay(delayloa);
//					HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 0);
//					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
//					key = CheckListUID(IDCard);
//					key = key >> 4;
//					break;
//				}
//				stat = checkbuton(MENU_GPIO_Port, MENU_Pin);
//				switch(stat){
//				case 0:
//					break;
//				case 3:
//					password();
//					key = 99;
//					exitmenu = 0;
//					break;
//				default :
//					key = 2;
//					exitmenu = 0;
//					break;
//				}
//			}
//			switch (key){
//			case 1:
//				seclectmenu();
//				break;
//			case 99:
//				break;
//			default:
//				CLCD_Clear(&LCD1);
//				CLCD_SetCursor(&LCD1, 0, 0);
//				CLCD_WriteString(&LCD1, "      SAI ");
//				CLCD_SetCursor(&LCD1, 0, 1);
//				CLCD_WriteString(&LCD1, "KHONG CO QUYEN");
//				HAL_Delay(1000);
//				CLCD_Clear(&LCD1);
//				break;
//			}
//			buton = 1;
//			Set_Pin_IT(MENU_GPIO_Port, MENU_GPIO_Port);
//			statustask = 0;
//		}
//		if (TM_MFRC522_Check(IDCard) == MI_OK)
//		{
//			sprintf(str, "ID: 0x%02X%02X%02X%02X%02X", IDCard[0], IDCard[1], IDCard[2], IDCard[3], IDCard[4]);
//			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
//			HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 1);
//			HAL_Delay(delayloa);
//			HAL_GPIO_WritePin(LOA_GPIO_Port, LOA_Pin, 0);
//			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
//			if (CheckListUID(IDCard) != 0)
//			{
//				HAL_GPIO_WritePin(KHOA_GPIO_Port, KHOA_Pin, 1);
//				CLCD_Clear(&LCD1);
//				CLCD_SetCursor(&LCD1, 0, 0);
//				CLCD_WriteString(&LCD1, "    WELCOME");
//				CLCD_SetCursor(&LCD1, 0, 1);
//				CLCD_WriteString(&LCD1,str);
//				HAL_Delay(5000);
//				HAL_GPIO_WritePin(KHOA_GPIO_Port, KHOA_Pin, 0);
//			}
//			else
//			{
//				CLCD_Clear(&LCD1);
//				CLCD_SetCursor(&LCD1, 0, 0);
//				CLCD_WriteString(&LCD1, "   THE SAI");
//				CLCD_SetCursor(&LCD1, 0, 1);
//				CLCD_WriteString(&LCD1, str);
//				HAL_Delay(5000);
//			}
//
//			CLCD_Clear(&LCD1);
//			CLCD_SetCursor(&LCD1, 0, 0);
//			CLCD_WriteString(&LCD1, " MOI QUET THE ");
//		}
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 35999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CS_Pin|QR_Pin|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LOA_Pin|KHOA_Pin|LED_Pin|D7_Pin
                          |D6_Pin|D5_Pin|D4_Pin|EN_Pin
                          |RW_Pin|RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_Pin QR_Pin PA15 */
  GPIO_InitStruct.Pin = CS_Pin|QR_Pin|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LOA_Pin KHOA_Pin LED_Pin D7_Pin
                           D6_Pin D5_Pin D4_Pin EN_Pin
                           RW_Pin RS_Pin */
  GPIO_InitStruct.Pin = LOA_Pin|KHOA_Pin|LED_Pin|D7_Pin
                          |D6_Pin|D5_Pin|D4_Pin|EN_Pin
                          |RW_Pin|RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SELECCT_Pin */
  GPIO_InitStruct.Pin = SELECCT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SELECCT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MENU_Pin */
  GPIO_InitStruct.Pin = MENU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MENU_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */








/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
