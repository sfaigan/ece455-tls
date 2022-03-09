/*
 * traffic_generator_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#include "traffic_generator_task.h"

void vTrafficGeneratorTask(void *pvParameters) {
	uint32_t traffic = 0;
	uint16_t trafficFlowRate;
	uint8_t newCarGap;

	while(1) {
		if (xQueueReceive(xTrafficFlowRateQueueHandle, &trafficFlowRate, QUEUE_OP_TIMEOUT)) {
			printf("[Traffic Generator Task] Received traffic flow rate from queue.\n");
			newCarGap = MAX_CAR_GAP - trafficFlowRate / 788;

			// Put the value back on the queue -_-
			if (xQueueSend(xTrafficFlowRateQueueHandle, &trafficFlowRate, QUEUE_OP_TIMEOUT)) {
				printf("[Traffic Generator Task] Sent traffic flow rate to queue.\n");
			} else {
				printf("[Traffic Generator Task] Failed to send traffic flow rate to queue.\n");
			}

			if (xQueueReceive(xTrafficQueueHandle, &traffic, QUEUE_OP_TIMEOUT)) {
				printf("[Traffic Generator Task] Received traffic from queue.\n");

				if (are_n_bits_free(traffic, NEW_CAR_BIT-1, newCarGap)) {
					printf("[Traffic Generator Task] Gap is large enough. Adding new car.\n");
					traffic = set_nth_bit(traffic, NEW_CAR_BIT);
				} else {
					printf("[Traffic Generator Task] Gap is not large enough to add new car.\n");
				}

				if (xQueueSend(xTrafficQueueHandle, &traffic, QUEUE_OP_TIMEOUT)) {
					printf("[Traffic Generator Task] Sent traffic to queue.\n");
				} else {
					printf("[Traffic Generator Task] Failed to send traffic to queue.\n");
				}
			} else {
				printf("[Traffic Generator Task] Failed to receive traffic from queue.\n");
			}
		} else {
			printf("[Traffic Generator Task] Failed to received traffic flow rate from queue.\n");
		}
		vTaskDelay(150);
	}
}
