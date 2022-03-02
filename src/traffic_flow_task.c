/*
 * traffic_flow_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: sfaigan
 */

#include "traffic_flow_task.h"

void vTrafficFlowTask(void *pvParameters) {
	uint32_t traffic = 0;
	uint32_t preStopLineTrafficAndNewCar;
	uint32_t newPreStopLineTraffic;
	uint32_t postStopLineTraffic;
	uint8_t trafficLightState;

	while(1) {
		if (xQueueReceive(xTrafficLightStateQueueHandle, &trafficLightState, QUEUE_OP_TIMEOUT)) {
			printf("[Traffic Flow Task] Received traffic light state from queue.\n");

			if (xQueueReceive(xTrafficQueueHandle, &traffic, QUEUE_OP_TIMEOUT)) {
				printf("[Traffic Flow Task] Received traffic from queue.\n");

				if (trafficLightState == GREEN_LIGHT) {
					traffic >>= 1;
				} else {
					// Light is red or yellow
					preStopLineTrafficAndNewCar = get_bits_in_range(traffic, 11, LANE_CAPACITY);
					newPreStopLineTraffic = 0;
					postStopLineTraffic = get_bits_in_range(traffic, 0, 10);

					// Set car at intersection if it's there
					if (get_nth_bit(preStopLineTrafficAndNewCar, 11)) {
						newPreStopLineTraffic = set_nth_bit(newPreStopLineTraffic, 11);
					}

					// Iterate through pre-stopline traffic, starting at second rightmost position
					// because car at intersection will never shift if light is red or yellow
					for (int i = 12; i <= LANE_CAPACITY; i++) {
						// If space is full
						if (get_nth_bit(preStopLineTrafficAndNewCar, i)) {
							if (get_nth_bit(preStopLineTrafficAndNewCar, i-1)) {
								// If space to the right is full, don't move the car
								newPreStopLineTraffic = set_nth_bit(newPreStopLineTraffic, i);
							} else {
								// If space to the right is empty, move the car to the right
								newPreStopLineTraffic = set_nth_bit(newPreStopLineTraffic, i-1);
							}
						}
					}

					postStopLineTraffic >>= 1;

					traffic &= 0;
					traffic |= newPreStopLineTraffic | postStopLineTraffic;
				}

				if (xQueueSend(xTrafficQueueHandle, &traffic, QUEUE_OP_TIMEOUT)) {
					printf("[Traffic Flow Task] Sent traffic to queue. Updating shift register.\n");
					set_shift_register(traffic, LANE_CAPACITY);
				} else {
					printf("[Traffic Flow Task] Failed to send traffic to queue.\n");
				}
			} else {
				printf("[Traffic Flow Task] Failed to receive traffic from queue.\n");
			}

			// Put the value back on the queue -_-
			if (xQueueSend(xTrafficLightStateQueueHandle, &trafficLightState, QUEUE_OP_TIMEOUT)) {
				printf("[Traffic Flow Task] Sent traffic light state to queue.\n");
			} else {
				printf("[Traffic Flow Task] Failed to send traffic light state to queue.\n");
			}
		} else {
			printf("[Traffic Flow Task] Failed to received traffic light state from queue.\n");
		}
		vTaskDelay(1000);
	}
}
