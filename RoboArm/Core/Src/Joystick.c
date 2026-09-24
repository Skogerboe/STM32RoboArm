/*
 * Joystick.c
 *
 *  Created on: Sep 19, 2026
 *      Author: Tyson
 */

#include <stdint.h>
#include "Joystick.h"


void VRX_Init(void)
{
	GPIOC->MODER &= ~(0x3 << 2);
	GPIOC->MODER |=  (0x3 << 2);

	GPIOC->PUPDR &= ~(0x3 << 2);

	ADC->CCR &= ~(0x3<< 16);
	ADC->CCR |=  (0x1 << 16);

	ADC1->CR1 &= ~(0x3 << 24);	// ADC result 0-4095

	ADC1->CR2 &= ~(0x1 << 1);

	ADC1->SQR3 &= ~(0x1F << 0);
	ADC1->SQR3 |=  (11U << 0);		// Set to Channel 11

	ADC1->SQR1 &= ~(0xF << 20);		// 1 conversion on channel

	ADC1->SMPR1 &= ~(0x7 << 3);
	ADC1->SMPR1 |=  (0x4 << 3);		// Sample rate to 100

	ADC1->CR2 |= ADC_CR2_ADON;		// Enables the ADC
}

void VRY_Init(void)
{

}

void JoySW_Init(void)
{
	GPIOC->MODER &= ~(0x3 << 4);
	GPIOC->PUPDR &= ~(0x3 << 4);
	GPIOC->PUPDR |= (0x1 << 4);

	GPIOD->MODER &= ~(0x3 << 26);
	GPIOD->MODER |= (0x1 << 26);
	GPIOD->ODR |= (1U << 13);

	SYSCFG->EXTICR[0] &= ~(0xF << 8);	// Map RC2 input to EXTI2 external interrupt
	SYSCFG->EXTICR[0] |= (0x2 << 8);

	EXTI->RTSR &= ~(0x1 << 2);		//Set to falling edge trigger
	EXTI->FTSR |=  (0x1 << 2);		//Set to falling edge trigger

	EXTI->PR = (0x1 << 2);	//Clear Pending interrupts

	EXTI->IMR |= (0x1 << 2);	//Unmask EXTI2

	NVIC->IP[EXTI2_IRQn] = (0x5 << 4);	//Set priority to 5

	NVIC->ISER[0] = (0x1 << EXTI2_IRQn);	//Enable interrupts in NVIC

}

void Joystick_Init(void)
{

	VRX_Init();
	VRY_Init();
	JoySW_Init();
}
