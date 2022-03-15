/*
 * traffic_light_state_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Shea and Darian
 */

#include "traffic_light_state_task.h"

void vTrafficLightStateTask( void *pvParameters ) {
	uint16_t usTrafficFlowRate;
	uint16_t usTrafficLightLength = BASE_LIGHT_TIME;
	uint8_t ucCurrentTrafficLightState;

	while ( 1 ) {
		/* Get traffic flow rate value from queue and store it locally */
		if ( xQueueReceive( xTrafficFlowRateQueueHandle, &usTrafficFlowRate, QUEUE_OP_TIMEOUT ) )
		{
			printf("[Traffic Light State Task] Received traffic flow rate from queue.\n");

			if ( xQueueReceive( xTrafficLightStateQueueHandle, &ucCurrentTrafficLightState, QUEUE_OP_TIMEOUT ) )
			{
				printf("[Traffic Light State Task] Received traffic light state from queue.\n");

				/* Set light */
				switch ( ucCurrentTrafficLightState )
				{
					case RED_LIGHT:
						ucCurrentTrafficLightState = GREEN_LIGHT;
						usTrafficLightLength = (1 + ((float) (usTrafficFlowRate / 3940))) * BASE_LIGHT_TIME;
						break;
					case YELLOW_LIGHT:
						ucCurrentTrafficLightState = RED_LIGHT;
						usTrafficLightLength = MAX_LIGHT_TIME - (((float) (usTrafficFlowRate / 3940)) * BASE_LIGHT_TIME);
						break;
					case GREEN_LIGHT:
						ucCurrentTrafficLightState = YELLOW_LIGHT;
						usTrafficLightLength = YELLOW_LIGHT_TIME;
				}

				usTrafficLightLength = pdMS_TO_TICKS( usTrafficLightLength );
				vEnableLED( ucCurrentTrafficLightState );

				if ( xQueueSend( xTrafficLightStateQueueHandle, &ucCurrentTrafficLightState, QUEUE_OP_TIMEOUT ) )
				{
					printf("[Traffic Light State Task] Sent traffic light state to queue.\n");
				}
				else
				{
					printf("[Traffic Light State Task] Failed to send traffic light state to queue.\n");
				}
			}
			else
			{
				printf("[Traffic Light State Task] Failed to receive traffic light state to queue.\n");
			}

			/* Put the value back on the queue */
			if ( xQueueSend( xTrafficFlowRateQueueHandle, &usTrafficFlowRate, QUEUE_OP_TIMEOUT ) )
			{
				printf("[Traffic Light State Task] Sent traffic flow rate to queue.\n");
			}
			else
			{
				printf("[Traffic Light State Task] Failed to send traffic flow rate to queue.\n");
			}
		}
		else
		{
			printf("[Traffic Light State Task] Failed to receive traffic flow rate from queue.\n");
		}

		vTaskDelay( usTrafficLightLength );
	}
}
