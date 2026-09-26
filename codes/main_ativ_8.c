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
#include <string.h>

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

/* Definitions for TaskSensor */
osThreadId_t TaskSensorHandle;
const osThreadAttr_t TaskSensor_attributes = {
  .name = "TaskSensor",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskProcessamen */
osThreadId_t TaskProcessamenHandle;
const osThreadAttr_t TaskProcessamen_attributes = {
  .name = "TaskProcessamen",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for TaskSupervisao */
osThreadId_t TaskSupervisaoHandle;
const osThreadAttr_t TaskSupervisao_attributes = {
  .name = "TaskSupervisao",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskLog */
osThreadId_t TaskLogHandle;
const osThreadAttr_t TaskLog_attributes = {
  .name = "TaskLog",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskAlarme */
osThreadId_t TaskAlarmeHandle;
const osThreadAttr_t TaskAlarme_attributes = {
  .name = "TaskAlarme",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for uartMutexHandle */
osMutexId_t uartMutexHandleHandle;
const osMutexAttr_t uartMutexHandle_attributes = {
  .name = "uartMutexHandle"
};
/* Definitions for sensorSemHandle */
osSemaphoreId_t sensorSemHandleHandle;
const osSemaphoreAttr_t sensorSemHandle_attributes = {
  .name = "sensorSemHandle"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartTaskSensor(void *argument);
void StartTaskProcessamento(void *argument);
void StartTaskSupervisao(void *argument);
void StartTaskLog(void *argument);
void StartTaskAlarme(void *argument);

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
  /* Create the mutex(es) */
  /* creation of uartMutexHandle */
  uartMutexHandleHandle = osMutexNew(&uartMutexHandle_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of sensorSemHandle */
  sensorSemHandleHandle = osSemaphoreNew(1, 1, &sensorSemHandle_attributes);

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
  /* creation of TaskSensor */
  TaskSensorHandle = osThreadNew(StartTaskSensor, NULL, &TaskSensor_attributes);

  /* creation of TaskProcessamen */
  TaskProcessamenHandle = osThreadNew(StartTaskProcessamento, NULL, &TaskProcessamen_attributes);

  /* creation of TaskSupervisao */
  TaskSupervisaoHandle = osThreadNew(StartTaskSupervisao, NULL, &TaskSupervisao_attributes);

  /* creation of TaskLog */
  TaskLogHandle = osThreadNew(StartTaskLog, NULL, &TaskLog_attributes);

  /* creation of TaskAlarme */
  TaskAlarmeHandle = osThreadNew(StartTaskAlarme, NULL, &TaskAlarme_attributes);

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

/* USER CODE BEGIN Header_StartTaskSensor */
/**
  * @brief  Function implementing the TaskSensor thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskSensor */
void StartTaskSensor(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(3000);

    osSemaphoreRelease(sensorSemHandleHandle);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTaskProcessamento */
/**
* @brief Function implementing the TaskProcessamen thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskProcessamento */
void StartTaskProcessamento(void *argument)
{
  /* USER CODE BEGIN StartTaskProcessamento */
  /* Infinite loop */

	char *msg = "[PROCESSO] Peca detectada e processada!\r\n";
	  for(;;) {
	    osSemaphoreAcquire(sensorSemHandleHandle, osWaitForever); // Fica dormindo até a peça chegar

	    osMutexAcquire(uartMutexHandleHandle, osWaitForever);
	    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 100);
	    osMutexRelease(uartMutexHandleHandle);
	  }}

  /* USER CODE END StartTaskProcessamento */


/* USER CODE BEGIN Header_StartTaskSupervisao */
/**
* @brief Function implementing the TaskSupervisao thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskSupervisao */
void StartTaskSupervisao(void *argument)
{
  /* USER CODE BEGIN StartTaskSupervisao */
  /* Infinite loop */
	char *msg = "[SUPERVISAO] Sistema operando normalmente...\r\n";
	  for(;;) {
	    osDelay(5000); // Checa a cada 5 segundos
	   // osMutexAcquire(uartMutexHandleHandle, osWaitForever);
	    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 100);
	    osMutexRelease(uartMutexHandleHandle);
	  } for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskSupervisao */
}

/* USER CODE BEGIN Header_StartTaskLog */
/**
* @brief Function implementing the TaskLog thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskLog */
void StartTaskLog(void *argument)
{
  /* USER CODE BEGIN StartTaskLog */
  /* Infinite loop */
	char *msg = "[LOG] Salvando historico no SD...\r\n";
	  for(;;) {
	    osDelay(7000); // Faz o log a cada 7 segundos
	   // osMutexAcquire(uartMutexHandleHandle, osWaitForever);
	    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 100);
	    osMutexRelease(uartMutexHandleHandle);
	  }
  /* USER CODE END StartTaskLog */
}

/* USER CODE BEGIN Header_StartTaskAlarme */
/**
* @brief Function implementing the TaskAlarme thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskAlarme */
void StartTaskAlarme(void *argument)
{
  /* USER CODE BEGIN StartTaskAlarme */
  /* Infinite loop */
  for(;;)
  {
	  char *msg_alerta = "[ALARME] ATENCAO! Verificando sensores criticos.\r\n";
	    char *msg_falha = "[ALARME] UART OCUPADA! TRATANDO LOCALMENTE.\r\n";
	    for(;;) {
	      osDelay(4000); // Dispara a cada 4 segundos

	      // O Alarme NÃO PODE travar. Timeout = 100ms
	      if (osMutexAcquire(uartMutexHandleHandle, 100) == osOK) {
	          HAL_UART_Transmit(&huart2, (uint8_t*)msg_alerta, strlen(msg_alerta), 100);
	          osMutexRelease(uartMutexHandleHandle);
	      } else {
	          // Se não conseguiu avisar no PC, ligaria um LED ou buzina localmente
	          HAL_UART_Transmit(&huart2, (uint8_t*)msg_falha, strlen(msg_falha), 100);
	      }
	    }
  }
  /* USER CODE END StartTaskAlarme */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2)
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
