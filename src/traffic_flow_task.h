/*
 * traffic_flow_task.h
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#ifndef TRAFFIC_FLOW_TASK_H_
#define TRAFFIC_FLOW_TASK_H_

#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/task.h"
#include "bits.h"
#include "led.h"
#include "queues.h"
#include "shift_register.h"

void vTrafficFlowTask(void *pvParameters);

#endif /* TRAFFIC_FLOW_TASK_H_ */
