/*
 * traffic_flow_rate_task.h
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */


#ifndef TRAFFIC_FLOW_RATE_TASK_H_
#define TRAFFIC_FLOW_RATE_TASK_H_

#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/task.h"
#include "adc.h"
#include "queues.h"

void vTrafficFlowRateTask(void *pvParameters);

#endif /* TRAFFIC_FLOW_RATE_TASK_H_ */
