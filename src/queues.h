/*
 * queues.h
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#ifndef QUEUES_H_
#define QUEUES_H_

#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"

#define QUEUE_LENGTH 1
#define QUEUE_OP_TIMEOUT 1000

xQueueHandle xTrafficFlowRateQueueHandle;
xQueueHandle xTrafficQueueHandle;
xQueueHandle xTrafficLightStateQueueHandle;

#endif /* QUEUES_H_ */
