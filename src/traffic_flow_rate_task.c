/*
 * traffic_flow_rate_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#include "traffic_flow_rate_task.h"

void vTrafficFlowRateTask(void *pvParameters) {
	uint16_t adcValue = 0;

	while(1) {

		// Discard existing traffic flow rate value from queue
		xQueueReceive(xTrafficFlowRateQueueHandle, &adcValue, QUEUE_OP_TIMEOUT);

		// Read potentiometer value
		adcValue = read_adc();

		// Send potentiometer reading to traffic flow rate queue
		if (xQueueSend(xTrafficFlowRateQueueHandle, &adcValue, QUEUE_OP_TIMEOUT)) {
			printf("[Traffic Flow Rate Task] Sent traffic flow rate to queue.\n");
		} else {
			printf("[Traffic Flow Rate Task] Failed to send traffic flow rate to queue.\n");
		}

		vTaskDelay(0);
	}
}
