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
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void show_number(unsigned number);
void choose_segment(bool segment1, bool segment2,bool segment3, bool segment4);

int __io_putchar(int ch){
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	 return ch;
}
unsigned TimerCnt=0;
unsigned number_to_show[4];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	static int counter=0;
    TimerCnt++;

	unsigned a=number_to_show[3];
	unsigned b=number_to_show[2];

	unsigned c=number_to_show[1];
	unsigned d=number_to_show[0];

	switch(counter){
	case 0:
		show_number(a);
		choose_segment(false, false ,false, true);
		break;
	case 1:
			show_number(b);
			choose_segment(false, false ,true, false);
			break;
	case 2:
			show_number(c);
			choose_segment(false, true ,false, false);
			break;
	case 3:
			show_number(d);
			choose_segment(true, false ,false, false);
			break;
	}
	counter++;
	counter%=4;


}
int getchar(void){
	uint8_t value;
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!= SET)
		return (-1);
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)== SET)
		HAL_UART_Receive(&huart2,&value,1,100);
	__io_putchar(value);
	return ((int) value);


}

void crude_counter(void){
	  for(unsigned i=0;i<=1000;i++){
		unsigned a= i % 10;
		unsigned b=(i%100-i%10)/10;
		unsigned c=(i%1000-i%100-i%10)/100;

		unsigned d=(i%10000-i%1000-i%100-i%10)/1000;

		for(int j=0;j<10;j++)
		{
		show_number(a);
		choose_segment(false, false ,false, true);
		HAL_Delay(1);

		show_number(b);
		choose_segment(false, false ,true, false);
		HAL_Delay(1);

		show_number(c);
		choose_segment(false, true ,false, false);
		HAL_Delay(1);
		show_number(d);
		choose_segment(true, false ,false, false);
		HAL_Delay(1);
		}
	  }
}

void shifting_numbers(unsigned delay_time){


	show_number(0);
	choose_segment(true,false,false,false);
	HAL_Delay(delay_time);

	show_number(1);

	choose_segment(false,true,false,false);
	HAL_Delay(delay_time);

	show_number(2);

	choose_segment(false,false,true,false);
	HAL_Delay(delay_time);

	show_number(3);
	choose_segment(false,false,false,true);
	HAL_Delay(delay_time);

	show_number(4);

	choose_segment(true,false,false,false);
	HAL_Delay(delay_time);

	show_number(5);

	choose_segment(false,true,false,false);
	HAL_Delay(delay_time);

	show_number(6);

	choose_segment(false,false,true,false);
	HAL_Delay(delay_time);

	show_number(7);
	choose_segment(false,false,false,true);
	HAL_Delay(delay_time);
	show_number(8);

	choose_segment(true,false,false,false);
	HAL_Delay(delay_time);

	show_number(9);

	choose_segment(false,true,false,false);
	HAL_Delay(delay_time);
}
void show_const(){
	unsigned delay_time=2;
	show_number(0);
	choose_segment(true,false,false,false);
	HAL_Delay(delay_time);

	show_number(1);

	choose_segment(false,true,false,false);
	HAL_Delay(delay_time);

	show_number(2);

	choose_segment(false,false,true,false);
	HAL_Delay(delay_time);

	show_number(3);
	choose_segment(false,false,false,true);
	HAL_Delay(delay_time);

}
void choose_segment(bool segment1, bool segment2,bool segment3, bool segment4){
	HAL_GPIO_WritePin(GPIOC, com1_Pin ,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, com2_Pin ,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, com3_Pin ,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, com4_Pin ,GPIO_PIN_SET);
	if (segment1){
	  HAL_GPIO_WritePin(GPIOC, com1_Pin ,GPIO_PIN_RESET);
	}
	if (segment2){
	  HAL_GPIO_WritePin(GPIOC, com2_Pin ,GPIO_PIN_RESET);
	}
	if (segment3){
	  HAL_GPIO_WritePin(GPIOC, com3_Pin ,GPIO_PIN_RESET);
	}
	if (segment4){
	  HAL_GPIO_WritePin(GPIOC, com4_Pin ,GPIO_PIN_RESET);
	}

}
void show_number(unsigned number){

		  switch(number)
		  {
		  case 0:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
		  case 1:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
		  case 2:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
		  case 3:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
		  case 4:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
	      break;
		  case 5:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
	      // 6
		  case 6:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
		  case 7:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
		  case 8:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);
		  break;
		  default:
			  HAL_GPIO_WritePin(GPIOC, segA_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segB_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segC_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segD_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segE_Pin ,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOC, segF_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segG_Pin ,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC, segDP_Pin ,GPIO_PIN_RESET);

		  }
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
  uint16_t ADCRes=0;
  int n=1251;
  uint16_t data[n];
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM9_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim1);


bool was_displayed=false;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//printf("%s %s \r \n ",__DATE__,__TIME__);
  while (1)
  {
	  number_to_show[3]=ADCRes%10;
	  number_to_show[2]=(ADCRes%100-ADCRes%10)/10;
	  number_to_show[1]=(ADCRes%1000-ADCRes%100)/100;
	  number_to_show[0]=(ADCRes%10000-ADCRes%1000)/1000;

	  if(getchar()==66){
		  for( int i=0;i<n;i++){
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		  ADCRes = HAL_ADC_GetValue(&hadc1); // 0-4095 == 0-3.3V
		  ADCRes = (uint16_t)(3.3 * (double)ADCRes / 4.095); // [mV]
		  HAL_Delay(4);
		  data[i]=ADCRes;
	      }
	  }

//	  if( !was_displayed){
//		  printf("%s\n","Data is ready, send 'A' to begin transmission");
//		  was_displayed=true;
//	  }


	  if(getchar()==65){
		  HAL_Delay(100);
		  for( int i=0;i<n;i++){
			  printf("%d \r\n",data[i]);
		  }
		  was_displayed=false;
	  }




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

 	 // all on

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
