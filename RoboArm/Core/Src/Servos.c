/*
 * Servos.c
 *
 *  Created on: Sep 20, 2026
 *      Author: Tyson
 */

#include <stdint.h>
#include <stdio.h>
#include "Servos.h"

void VRX_Servo_Init(void)
{
	// PB0 -> Alternate Function
	GPIOB->MODER &= ~(3U << 0);
	GPIOB->MODER |=  (2U << 0);

	// PB0 -> AF2 = TIM3_CH3
	GPIOB->AFR[0] &= ~(0xFU << 0);
	GPIOB->AFR[0] |=  (2U << 0);

	// Push-pull
	GPIOB->OTYPER &= ~(1U << 0);

	// High speed
	GPIOB->OSPEEDR &= ~(3U << 0);
	GPIOB->OSPEEDR |=  (2U << 0);

	// No pull-up/pull-down
	GPIOB->PUPDR &= ~(3U << 0);

	TIM3->CR1 = 0;

	TIM3->PSC = 15;

	TIM3->ARR = 19999;

	// PWM Mode 1
	TIM3->CCMR2 &= ~(7U << 4);
	TIM3->CCMR2 |=  (6U << 4);

	// Enable CCR3 preload
	TIM3->CCMR2 |= (1U << 3);

	TIM3->CCMR2 |= TIM_CCMR2_OC3PE;

	// Enable TIM3 CH3 output
	TIM3->CCER |= TIM_CCER_CC3E;

	// Initial servo position = 1.5 ms
	TIM3->CCR3 = 1500;

	// Enable ARR preload
	TIM3->CR1 |= TIM_CR1_ARPE;

	// Force update event
	TIM3->EGR |= TIM_EGR_UG;

	// Start TIM3
	TIM3->CR1 |= TIM_CR1_CEN;

}

void VRY_Servo_Init(void)
{

}

void Servos_Init(void)
{
	VRX_Servo_Init();
	VRY_Servo_Init();
}
