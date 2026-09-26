/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
UART_HandleTypeDef huart2;

/* Definitions for TaskCarro1 */
osThreadId_t TaskCarro1Handle;
const osThreadAttr_t TaskCarro1_attributes = {
  .name = "TaskCarro1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskCarro2 */
osThreadId_t TaskCarro2Handle;
const osThreadAttr_t TaskCarro2_attributes = {
  .name = "TaskCarro2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskCarro3 */
osThreadId_t TaskCarro3Handle;
const osThreadAttr_t TaskCarro3_attributes = {
  .name = "TaskCarro3",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskCarro4 */
osThreadId_t TaskCarro4Handle;
const osThreadAttr_t TaskCarro4_attributes = {
  .name = "TaskCarro4",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskCarro5 */
osThreadId_t TaskCarro5Handle;
const osThreadAttr_t TaskCarro5_attributes = {
  .name = "TaskCarro5",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for vagasHandle */
osSemaphoreId_t vagasHandleHandle;
const osSemaphoreAttr_t vagasHandle_attributes = {
  .name = "vagasHandle"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartTaskCarro1(void *argument);
void StartTaskCarro2(void *argument);
void StartTaskCarro3(void *argument);
void StartTaskCarro4(void *argument);
void StartTTaskCarro5(void *argument);

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of vagasHandle */
  vagasHandleHandle = osSemaphoreNew(1, 1, &vagasHandle_attributes);

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
  /* creation of TaskCarro1 */
  TaskCarro1Handle = osThreadNew(StartTaskCarro1, NULL, &TaskCarro1_attributes);

  /* creation of TaskCarro2 */
  TaskCarro2Handle = osThreadNew(StartTaskCarro2, NULL, &TaskCarro2_attributes);

  /* creation of TaskCarro3 */
  TaskCarro3Handle = osThreadNew(StartTaskCarro3, NULL, &TaskCarro3_attributes);

  /* creation of TaskCarro4 */
  TaskCarro4Handle = osThreadNew(StartTaskCarro4, NULL, &TaskCarro4_attributes);

  /* creation of TaskCarro5 */
  TaskCarro5Handle = osThreadNew(StartTTaskCarro5, NULL, &TaskCarro5_attributes);

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
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTaskCarro1 */
/**
  * @brief  Function implementing the TaskCarro1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskCarro1 */
void StartTaskCarro1(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {

	    char msg1[] = "[CARRO 1] Entrando no estacionamento...\r\n";
	    char msg2[] = "[CARRO 1] Consegui entrar !! Vou permanecer\r\n";
	    char msg3[] = "[CARRO 1] Vou embora agora !!!\r\n";

	    for(;;)
	    {

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg1, sizeof(msg1) - 1, 1000);

	      osSemaphoreAcquire(vagasHandleHandle, osWaitForever);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg2, sizeof(msg2) - 1, 1000);
	      osDelay(3000);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg3, sizeof(msg3) - 1, 1000);

	      osSemaphoreRelease(vagasHandleHandle);
	      osDelay(4000);
	    }
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTaskCarro2 */
/**
* @brief Function implementing the TaskCarro2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskCarro2 */
void StartTaskCarro2(void *argument)
{
  /* USER CODE BEGIN StartTaskCarro2 */
  /* Infinite loop */
  for(;;)
  {

	    char msg1[] = "[CARRO 2] Entrando no estacionamento...\r\n";
	    char msg2[] = "[CARRO 2] Consegui entrar !! Vou permanecer\r\n";
	    char msg3[] = "[CARRO 2] Vou embora agora !!!\r\n";

	    for(;;)
	    {

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg1, sizeof(msg1) - 1, 1000);

	      osSemaphoreAcquire(vagasHandleHandle, osWaitForever);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg2, sizeof(msg2) - 1, 1000);
	      osDelay(3000);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg3, sizeof(msg3) - 1, 1000);

	      osSemaphoreRelease(vagasHandleHandle);
	      osDelay(4000);
	    }
  }
  /* USER CODE END StartTaskCarro2 */
}

/* USER CODE BEGIN Header_StartTaskCarro3 */
/**
* @brief Function implementing the TaskCarro3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskCarro3 */
void StartTaskCarro3(void *argument)
{
  /* USER CODE BEGIN StartTaskCarro3 */
  /* Infinite loop */
  for(;;)
  {

	    char msg1[] = "[CARRO 3] Entrando no estacionamento...\r\n";
	    char msg2[] = "[CARRO 3] Consegui entrar !! Vou permanecer\r\n";
	    char msg3[] = "[CARRO 3] Vou embora agora !!!\r\n";

	    for(;;)
	    {

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg1, sizeof(msg1) - 1, 1000);

	      osSemaphoreAcquire(vagasHandleHandle, osWaitForever);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg2, sizeof(msg2) - 1, 1000);
	      osDelay(3000);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg3, sizeof(msg3) - 1, 1000);

	      osSemaphoreRelease(vagasHandleHandle);
	      osDelay(4000);
	    }

  }
  /* USER CODE END StartTaskCarro3 */
}

/* USER CODE BEGIN Header_StartTaskCarro4 */
/**
* @brief Function implementing the TaskCarro4 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskCarro4 */
void StartTaskCarro4(void *argument)
{
  /* USER CODE BEGIN StartTaskCarro4 */
  /* Infinite loop */
  for(;;)
  {

	    char msg1[] = "[CARRO 4] Entrando no estacionamento...\r\n";
	    char msg2[] = "[CARRO 4] Consegui entrar !! Vou permanecer\r\n";
	    char msg3[] = "[CARRO 4] Vou embora agora !!!\r\n";

	    for(;;)
	    {

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg1, sizeof(msg1) - 1, 1000);

	      osSemaphoreAcquire(vagasHandleHandle, osWaitForever);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg2, sizeof(msg2) - 1, 1000);
	      osDelay(3000);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg3, sizeof(msg3) - 1, 1000);

	      osSemaphoreRelease(vagasHandleHandle);
	      osDelay(4000);
	    }
  }
  /* USER CODE END StartTaskCarro4 */
}

/* USER CODE BEGIN Header_StartTTaskCarro5 */
/**
* @brief Function implementing the TaskCarro5 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTTaskCarro5 */
void StartTTaskCarro5(void *argument)
{
  /* USER CODE BEGIN StartTTaskCarro5 */
  /* Infinite loop */
  for(;;)
  {

	    char msg1[] = "[CARRO 5] Entrando no estacionamento...\r\n";
	    char msg2[] = "[CARRO 5] Consegui entrar !! Vou permanecer\r\n";
	    char msg3[] = "[CARRO 5] Vou embora agora !!!\r\n";

	    for(;;)
	    {

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg1, sizeof(msg1) - 1, 1000);

	      osSemaphoreAcquire(vagasHandleHandle, osWaitForever);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg2, sizeof(msg2) - 1, 1000);
	      osDelay(3000);

	      HAL_UART_Transmit(&huart2, (uint8_t*)msg3, sizeof(msg3) - 1, 1000);

	      osSemaphoreRelease(vagasHandleHandle);
	      osDelay(4000);
	    }
  }
  /* USER CODE END StartTTaskCarro5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
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
#ifdef USE_FULL_ASSERT
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
