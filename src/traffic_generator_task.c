/*
 * traffic_generator_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

static void traffic_generator_task( void *pvParameters ) {
	uint32_t traffic = 0;
	uint16_t trafficLightState;
	uint16_t trafficFlowRate;
	uint8_t = newCarGap;

	while(1) {
		if (xQueueReceive(xTrafficFlowRateQueueHandle, &trafficFlowRate, QUEUE_OP_TIMEOUT)) {
			printf("[Traffic Generator Task] Received traffic flow rate from queue.\n");
			newCarGap = 5 - traffic_flow_rate / 788;

			// if bits 18 to (18 - newCarGap) are open
				// set bit 19 to 1

			// Put the value back on the queue -_-
			if (xQueueSend(xTrafficFlowRateQueueHandle, &trafficFlowRate, QUEUE_OP_TIMEOUT)) {
				printf("[Traffic Generator Task] Sent traffic flow rate to queue.\n");
			} else {
				printf("[Traffic Generator Task] Failed to send traffic flow rate to queue.\n");
			}
		} else {
			printf("[Traffic Generator Task] Failed to received traffic flow rate from queue.\n");
		}
		vTaskDelay(0);
	}
}
