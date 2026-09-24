#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "Utilities.h"
#include "Joystick.h"
#include "Servos.h"

ADC_HandleTypeDef hadc1;

volatile int buttonclicks = 0;

void SystemClock_Config(void);
static void MX_ADC1_Init(void);

void EXTI2_IRQHandler(void)
{
	/*
	 * Check whether EXTI2 caused the interrupt
	 */
	if (EXTI->PR & (1U << 2))
	{
		/*
		 * Clear pending flag
		 */
		EXTI->PR = (1U << 2);

		/*
		 * Button was pressed
		 */
		buttonclicks = 1;
	}
}

//uint16_t ADC1_Read_PC0(void)
//{
//
//}

uint16_t ADC1_Read_PC1(void)
{
    /* Start conversion */
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* Wait for conversion to finish */
    while (!(ADC1->SR && ADC_SR_EOC))
    {
    }

    /* Return 12-bit ADC result */
    return (uint16_t)ADC1->DR;
}

int main(void)
{
	int buttonclickold = 0;
	float VRX_V, VRY_V, ServoX_V, ServoY_V;

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  SystemClock_Config();
  Clocks_Init();

  //Disable Interrupts

  Joystick_Init();
  Servos_Init();

  //Enable Interrupts


  while (1)
  {
	  //VRY_V = ADC_Read_PC0();
	  VRX_V = (float)ADC1_Read_PC1() * JoyVCC / VRXY_RES;
	  ServoX_V= (VRX_V * (ServoPWM_MAX - ServoPWM_MIN) / JoyVCC) + (ServoPWM_MAX - ServoPWM_MIN);
	  TIM3->CCR3 = (uint32_t)ServoX_V;

	  if(buttonclicks > 0)
	  {
		  buttonclicks = 0;
		  buttonclickold += 1;
		  GPIOD->ODR ^= (1U << 13);
	  }
  }
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
