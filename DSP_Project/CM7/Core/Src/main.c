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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

#include "DSP_TransferFunction.h"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define FFT_LENGTH	1000
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim7;

/* Definitions for Sine2 */
osThreadId_t Sine2Handle;
const osThreadAttr_t Sine2_attributes = {
  .name = "Sine2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Sine10 */
osThreadId_t Sine10Handle;
const osThreadAttr_t Sine10_attributes = {
  .name = "Sine10",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Sum */
osThreadId_t SumHandle;
const osThreadAttr_t Sum_attributes = {
  .name = "Sum",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
DSP_TF_tst DSP_ContinuousTFSine2_st;
DSP_TF_tst DSP_DiscreteTFSine2_st;

DSP_TF_tst DSP_ContinuousTFSine10_st;
DSP_TF_tst DSP_DiscreteTFSine10_st;

DSP_TF_tst DSP_LPFilterP_st;
DSP_TF_tst DSP_LPFilterZ_st;


float outputSine21 = 0.0;
float outputSine22 = 0.0;


float outputSine101 = 0.0;
float outputSum1 = 0.0;

float DSP_FilteredSignal_f = 0.0;

DSP_Return_ten Return;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM7_Init(void);
void Sine2Function(void *argument);
void Sine10Function(void *argument);
void SumFunction(void *argument);

/* USER CODE BEGIN PFP */

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
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
/* USER CODE END Boot_Mode_Sequence_0 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */

/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */

/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */

	/*Sine wave*/

  DSP_ContinuousTFSine2_st.num.degree = 2;
  DSP_ContinuousTFSine2_st.num.coef[0] = 0.0;
  DSP_ContinuousTFSine2_st.num.coef[1] = 0.0;
  DSP_ContinuousTFSine2_st.num.coef[2] = -1.0;

  DSP_ContinuousTFSine2_st.denom.degree = 2;
  DSP_ContinuousTFSine2_st.denom.coef[0] = (double)(16.0)*M_PI*M_PI;//157.9;
  DSP_ContinuousTFSine2_st.denom.coef[1] = 0.0;
  DSP_ContinuousTFSine2_st.denom.coef[2] = 1.0;
  Return = DSP_C2D(DSP_ContinuousTFSine2_st, &DSP_DiscreteTFSine2_st, DSP_Tustin);
	DSP_vGenerateSignal(&DSP_DiscreteTFSine2_st);
	DSP_vSetInput(&DSP_DiscreteTFSine2_st, 1.0);


	/*Low pass filte*/
  DSP_LPFilterP_st.num.degree = 0;
  DSP_LPFilterP_st.num.coef[0] = 1.0;

  DSP_LPFilterP_st.denom.degree = 1;
  DSP_LPFilterP_st.denom.coef[0] = 1.0;
  DSP_LPFilterP_st.denom.coef[1] = 0.032;

  Return = DSP_C2D(DSP_LPFilterP_st, &DSP_LPFilterZ_st, DSP_Tustin);
	DSP_vGenerateSignal(&DSP_LPFilterZ_st);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Sine2 */
  Sine2Handle = osThreadNew(Sine2Function, NULL, &Sine2_attributes);

  /* creation of Sine10 */
  Sine10Handle = osThreadNew(Sine10Function, NULL, &Sine10_attributes);

  /* creation of Sum */
  SumHandle = osThreadNew(SumFunction, NULL, &Sum_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 4096;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 639;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/* USER CODE BEGIN 4 */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	outputSine2 = DSP_fRecurringEquationRoutine(&DSP_DiscreteTFSine2_st);
//	outputSine10 = DSP_fRecurringEquationRoutine(&DSP_DiscreteTFSine10_st);
//	outputSum = outputSine2 + outputSine10;
//}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_Sine2Function */
/**
 * @brief  Function implementing the Sine2 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Sine2Function */
void Sine2Function(void *argument)
{
  /* USER CODE BEGIN 5 */
	float t = 0.0;
	/* Infinite loop */
	for(;;)
	{
		outputSine21 = sin(2*M_PI*2*t - M_PI/2.0);
		//outputSine22 = DSP_fRecurringEquationRoutine(&DSP_DiscreteTFSine2_st);
		t = t + 0.001;
		osDelay(1);
	}
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Sine10Function */
/**
 * @brief Function implementing the Sine10 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Sine10Function */
void Sine10Function(void *argument)
{
  /* USER CODE BEGIN Sine10Function */
	float t = 0.0;

	/* Infinite loop */
	for(;;)
	{
		outputSine101 = sin(2*M_PI*50*t- M_PI/2.0);
		//outputSine102 = DSP_fRecurringEquationRoutine(&DSP_DiscreteTFSine10_st);
		t = t + 0.001;

		osDelay(1);
	}
  /* USER CODE END Sine10Function */
}

/* USER CODE BEGIN Header_SumFunction */
/**
 * @brief Function implementing the Sum thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_SumFunction */
void SumFunction(void *argument)
{
  /* USER CODE BEGIN SumFunction */
	/* Infinite loop */
	for(;;)
	{
		outputSum1 = outputSine21 + outputSine101;
		//outputSum2 = outputSine22 + outputSine102;
		DSP_vSetInput(&DSP_LPFilterZ_st, outputSum1);

		osDelay(1);
	}
  /* USER CODE END SumFunction */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
