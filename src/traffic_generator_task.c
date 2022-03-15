/*
 * traffic_generator_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Shea and Darian
 */

#include "traffic_generator_task.h"

void vTrafficGeneratorTask( void *pvParameters )
{
	uint32_t ulTraffic = 0;
	uint16_t usTrafficFlowRate;
	uint8_t ucNewCarGap;

	while( 1 )
	{
		if ( xQueueReceive( xTrafficFlowRateQueueHandle, &usTrafficFlowRate, QUEUE_OP_TIMEOUT ) )
		{
			printf("[Traffic Generator Task] Received traffic flow rate from queue.\n");
			ucNewCarGap = MAX_CAR_GAP - usTrafficFlowRate / 788;

			/* Put the value back on the queue -_- */
			if ( xQueueSend( xTrafficFlowRateQueueHandle, &usTrafficFlowRate, QUEUE_OP_TIMEOUT ) )
			{
				printf("[Traffic Generator Task] Sent traffic flow rate to queue.\n");
			}
			else
			{
				printf("[Traffic Generator Task] Failed to send traffic flow rate to queue.\n");
			}

			if ( xQueueReceive( xTrafficQueueHandle, &ulTraffic, QUEUE_OP_TIMEOUT ) )
			{
				printf("[Traffic Generator Task] Received traffic from queue.\n");

				if ( ucAreNBitsFree( ulTraffic, NEW_CAR_BIT-1, ucNewCarGap ) )
				{
					printf("[Traffic Generator Task] Gap is large enough. Adding new car.\n");
					ulTraffic = ulSetNthBit( ulTraffic, NEW_CAR_BIT );
				}
				else
				{
					printf("[Traffic Generator Task] Gap is not large enough to add new car.\n");
				}

				if ( xQueueSend( xTrafficQueueHandle, &ulTraffic, QUEUE_OP_TIMEOUT ) )
				{
					printf("[Traffic Generator Task] Sent traffic to queue.\n");
				}
				else
				{
					printf("[Traffic Generator Task] Failed to send traffic to queue.\n");
				}
			}
			else
			{
				printf("[Traffic Generator Task] Failed to receive traffic from queue.\n");
			}
		}
		else
		{
			printf("[Traffic Generator Task] Failed to received traffic flow rate from queue.\n");
		}

		vTaskDelay( 150 );
	}
}
