/*
 * traffic_light_state_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#include "traffic_light_state_task.h"

void vTrafficLightStateTask(void *pvParameters) {
	uint16_t trafficFlowRate;
	uint16_t trafficLightLength = BASE_LIGHT_LENGTH;
	uint8_t currentTrafficLightState = RED_LIGHT;
//
	while (1) {
		// Get traffic flow rate value from queue and store it locally
		if (xQueueReceive(xTrafficFlowRateQueueHandle, &trafficFlowRate, QUEUE_OP_TIMEOUT)) {
			printf("[Traffic Light State Task] Received traffic flow rate from queue.\n");

			// Set light
			switch (currentTrafficLightState) {
				case RED_LIGHT:
					currentTrafficLightState = GREEN_LIGHT;
					trafficLightLength = (1 + ((float) (trafficFlowRate / 3940))) * BASE_LIGHT_LENGTH;
					break;
				case YELLOW_LIGHT:
					currentTrafficLightState = RED_LIGHT;
					trafficLightLength = (1 + ((float) (trafficFlowRate / 3940))) * BASE_LIGHT_LENGTH;
					break;
				case GREEN_LIGHT:
					currentTrafficLightState = YELLOW_LIGHT;
					trafficLightLength = BASE_LIGHT_LENGTH;
			}

			trafficLightLength = pdMS_TO_TICKS(trafficLightLength);
			vEnableLED(currentTrafficLightState);

			// Put the value back on the queue -_-
			if (xQueueSend(xTrafficFlowRateQueueHandle, &trafficFlowRate, QUEUE_OP_TIMEOUT)) {
				printf("[Traffic Light State Task] Sent traffic flow rate to queue.\n");
			} else {
				printf("[Traffic Light State Task] Failed to send traffic flow rate to queue.\n");
			}
		} else {
			printf("[Traffic Light State Task] Failed to received traffic flow rate from queue.\n");
		}
		vTaskDelay(trafficLightLength);
	}
}
