/*
 * traffic_flow_rate_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Shea and Darian
 */

#include "traffic_flow_rate_task.h"

void vTrafficFlowRateTask( void *pvParameters )
{
	uint16_t usADCValue;

	while(1)
	{
		/* Discard existing traffic flow rate value from queue */
		if ( xQueueReceive( xTrafficFlowRateQueueHandle, &usADCValue, QUEUE_OP_TIMEOUT ) )
		{
			printf("[Traffic Flow Rate Task] Received traffic flow rate from queue.\n");

			/* Read potentiometer value and overwrite existing value */
			usADCValue = usReadADC();

			/* Send potentiometer reading to traffic flow rate queue */
			if ( xQueueSend( xTrafficFlowRateQueueHandle, &usADCValue, QUEUE_OP_TIMEOUT ) )
			{
				printf("[Traffic Flow Rate Task] Sent traffic flow rate to queue.\n");
			}
			else
			{
				printf("[Traffic Flow Rate Task] Failed to send traffic flow rate to queue.\n");
			}
		}
		else
		{
			printf("[Traffic Flow Rate Task] Failed to receive traffic flow rate from queue.\n");
		}
		vTaskDelay(500);
	}
}
