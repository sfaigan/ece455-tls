/*
 * traffic_generator_task.h
 *
 *  Created on: Mar 1, 2022
 *      Author: Shea and Darian
 */

#ifndef TRAFFIC_GENERATOR_TASK_H_
#define TRAFFIC_GENERATOR_TASK_H_

/* Includes */
#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/task.h"
#include "bits.h"
#include "queues.h"

/* Macros */
#define NEW_CAR_BIT 19
#define MAX_CAR_GAP 5

/* Function declarations */
void vTrafficGeneratorTask(void *pvParameters);

#endif /* TRAFFIC_GENERATOR_TASK_H_ */
