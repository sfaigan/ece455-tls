/*
 * traffic_generator_task.h
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#ifndef TRAFFIC_GENERATOR_TASK_H_
#define TRAFFIC_GENERATOR_TASK_H_

#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/task.h"
#include "bits.h"
#include "queues.h"

#define NEW_CAR_BIT 19 // indexed from 0
#define MAX_CAR_GAP 5

void vTrafficGeneratorTask(void *pvParameters);

#endif /* TRAFFIC_GENERATOR_TASK_H_ */
