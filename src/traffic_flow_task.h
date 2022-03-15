/*
 * traffic_flow_task.h
 *
 *  Created on: Mar 1, 2022
 *      Author: Shea and Darian
 */

#ifndef TRAFFIC_FLOW_TASK_H_
#define TRAFFIC_FLOW_TASK_H_

/* Includes */
#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/task.h"
#include "bits.h"
#include "led.h"
#include "queues.h"
#include "shift_register.h"

/* Macros */
#define LANE_CAPACITY 19

/* Function declarations */
void vTrafficFlowTask( void *pvParameters );

#endif /* TRAFFIC_FLOW_TASK_H_ */
