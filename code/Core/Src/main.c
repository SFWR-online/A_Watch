/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "u8g2.h"
#include "allmath.h"
#include "allcontrol.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int time[7]={2022,6,26,0,0,0};
int time_set_pos[7][2]={{41,20},{62,20},{83,20},{32,62},{90,62},{114,62}};
int time_set[7];
int page=1;
int switch_page=0;
int set_time_pos=0;
int music_pos=0;
int battery=0;
u8g2_t u8g2;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void init(){
	u8g2Init(&u8g2);
	//display_page_init(u8g2);
	u8g2_ClearDisplay(&u8g2);
	HAL_TIM_Base_Start_IT(&htim6);
	fresh_bat(battery,u8g2);
}
void page1(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
	}
	display_page_time(time,u8g2);
	u8g2_SendBuffer(&u8g2);
}
void page2(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
		u8g2_DrawXBM(&u8g2,48,5,32,32,set_pic);
		u8g2_SetFont(&u8g2,u8g2_font_t0_14_mf);
		u8g2_DrawStr(&u8g2,38,50,"Set Time");
		u8g2_SendBuffer(&u8g2);
	}
	if(button_sure()){
		page=21;
		switch_page=1;
	}
}
void page3(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
		u8g2_DrawXBM(&u8g2,48,5,32,32,tem_pic);
		u8g2_SetFont(&u8g2,u8g2_font_t0_14_mf);
		u8g2_DrawStr(&u8g2,43,50,"E Data");
		u8g2_SendBuffer(&u8g2);
	}
	if(button_sure()){
		page=31;
		switch_page=1;
	}
}
void page4(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
		u8g2_DrawXBM(&u8g2,48,5,32,32,card_pic);
		u8g2_SetFont(&u8g2,u8g2_font_t0_14_mf);
		u8g2_DrawStr(&u8g2,45,50,"Card");
		u8g2_SendBuffer(&u8g2);
	}
	if(button_sure()){
		page=41;
		switch_page=1;
	}
}
void page5(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
		u8g2_DrawXBM(&u8g2,48,5,32,32,music_pic);
		u8g2_SetFont(&u8g2,u8g2_font_t0_14_mf);
		u8g2_DrawStr(&u8g2,45,50,"Music");
		u8g2_SendBuffer(&u8g2);
	}
	if(button_sure()){
		page=51;
		switch_page=1;
	}
}
void page2_1(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
		evaluate_array(time_set,time,6);
		set_time_pos=0;
		display_page_time(time_set,u8g2);
		u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);
		//u8g2_DrawGlyph(&u8g2,time_set_pos[0][0],time_set_pos[0][1],0xe12b);
		u8g2_DrawGlyph(&u8g2,time_set_pos[set_time_pos][0],time_set_pos[set_time_pos][1],0xe12b);
		u8g2_SendBuffer(&u8g2);
	}
	if(button_sure()){
		evaluate_array(time,time_set,6);
		page=2;
		switch_page=1;
	}
	if(button_return()){
		page=2;
		switch_page=1;
	}
	if(button_turn()){
		set_time_pos=(set_time_pos+1)%6;
		u8g2_ClearBuffer(&u8g2);
		display_page_time(time_set,u8g2);
		u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);
		u8g2_DrawGlyph(&u8g2,time_set_pos[set_time_pos][0],time_set_pos[set_time_pos][1],0xe12b);
		fresh_bat(battery,u8g2);
	}
	if(button_other1()){
		modify_time(time_set,set_time_pos,1);
		display_page_time(time_set,u8g2);
		u8g2_SendBuffer(&u8g2);
	}
}
void page3_1(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
	}
	if(button_return()){
		page=3;
		switch_page=1;
	}
}
void page4_1(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		fresh_bat(battery,u8g2);
		switch_page=0;
		play_card(u8g2,time[3]+time[4]+time[5]);
	}
	if(button_return()){
		page=4;
		switch_page=1;
	}
}
void page5_1(){
	if(switch_page){
		u8g2_ClearDisplay(&u8g2);
		switch_page=0;
		music_pos=1;
		display_page_music(u8g2,music_pos);
		fresh_bat(battery,u8g2);
	}
	if(button_return()){
		page=5;
		switch_page=1;
	}
	if(button_sure()){
		display_music(music_pos);
	}
	if(button_turn()){
		music_pos=(music_pos==5)?1:(music_pos+1);
		fresh_bat(battery,u8g2);
		display_page_music(u8g2,music_pos);
		fresh_bat(battery,u8g2);
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  init();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(button_turn()&&page<10){
		  page=page%5+1;
		  switch_page=1;
	  }
	  switch(page){
	  	 case 1:page1();break;
	  	  case 2:page2();break;
	  	  case 3:page3();break;
	  	  case 4:page4();break;
	  	  case 5:page5();break;
	  	  //case 6:page5();break;
	  	  //case 7:page5();break;
	  	  //case 8:page5();break;
	  	  case 21:page2_1();break;
	  	  case 31:page3_1();break;
	  	  case 41:page4_1();break;
	  	  case 51:page5_1();break;


	  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM6)
		{
		time[5]++;
		next_time(time);
	    }

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
