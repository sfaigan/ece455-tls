/*
 * traffic_light_state_task.h
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#ifndef TRAFFIC_LIGHT_STATE_TASK_H_
#define TRAFFIC_LIGHT_STATE_TASK_H_

#include <stdint.h>
#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/task.h"
#include "led.h"
#include "queues.h"

#define RED_LIGHT 0
#define YELLOW_LIGHT 1
#define GREEN_LIGHT 2

#define BASE_LIGHT_LENGTH 5000
#define YELLOW_LIGHT_TIME 2000

void vTrafficLightStateTask();

#endif /* TRAFFIC_LIGHT_STATE_TASK_H_ */
