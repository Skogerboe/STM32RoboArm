/*
 * Joystick.h
 *
 *  Created on: Sep 19, 2026
 *      Author: Tyson
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include "Utilities.h"

#define JoyVCC		3
#define VRXY_RES	4096
#define	JoyMiddle	JoyVCC / 2
#define JoyLeftDown	0
#define JoyRightUp	JoyVCC
#define	ServoPWM_MIN	800
#define ServoPWM_MAX	2200

void VRX_Init(void);
void VRY_Init(void);
void JoySW_Init(void);
void Joystick_Init(void);

#endif /* INC_JOYSTICK_H_ */
