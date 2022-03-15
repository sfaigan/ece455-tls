/*
 * traffic_flow_task.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Shea and Darian
 */

#include "traffic_flow_task.h"

void vTrafficFlowTask( void *pvParameters )
{
    uint32_t ulTraffic = 0;
    uint32_t ulPreStopLineTrafficAndNewCar;
    uint32_t ulNewPreStopLineTraffic;
    uint32_t ulPostStopLineTraffic;
    uint8_t ucTrafficLightState;

    while( 1 )
    {
        if ( xQueueReceive( xTrafficLightStateQueueHandle, &ucTrafficLightState, QUEUE_OP_TIMEOUT ) )
        {
            printf("[Traffic Flow Task] Received traffic light state from queue.\n");

            if ( xQueueReceive( xTrafficQueueHandle, &ulTraffic, QUEUE_OP_TIMEOUT ) )
            {
                printf("[Traffic Flow Task] Received traffic from queue.\n");

                if ( ucTrafficLightState == GREEN_LIGHT )
                {
                    ulTraffic >>= 1;
                }
                else
                {
                    /* Light is red or yellow */
                    ulPreStopLineTrafficAndNewCar = ulGetBitsInRange( ulTraffic, 11, LANE_CAPACITY );
                    ulNewPreStopLineTraffic = 0;
                    ulPostStopLineTraffic = ulGetBitsInRange( ulTraffic, 0, 10 );

                    /* Set car at intersection if it's there */
                    if ( ucGetNthBit( ulPreStopLineTrafficAndNewCar, 11 ) )
                    {
                        ulNewPreStopLineTraffic = ulSetNthBit( ulNewPreStopLineTraffic, 11 );
                    }

                    /* Iterate through pre-stopline traffic, starting at second rightmost position */
                    /* because car at intersection will never shift if light is red or yellow */
                    for ( uint8_t ucCounter = 12; ucCounter <= LANE_CAPACITY; ucCounter++ )
                    {
                        /* If space is full */
                        if ( ucGetNthBit( ulPreStopLineTrafficAndNewCar, ucCounter ) )
                        {
                            if ( ucGetNthBit( ulNewPreStopLineTraffic, ucCounter - 1 ) )
                            {
                                /* If space to the right is full, don't move the car */
                                ulNewPreStopLineTraffic = ulSetNthBit( ulNewPreStopLineTraffic, ucCounter );
                            }
                            else
                            {
                                /* If space to the right is empty, move the car to the right */
                                ulNewPreStopLineTraffic = ulSetNthBit( ulNewPreStopLineTraffic, ucCounter - 1 );
                            }
                        }
                    }

                    ulPostStopLineTraffic >>= 1;

                    ulTraffic &= 0;
                    ulTraffic |= ulNewPreStopLineTraffic | ulPostStopLineTraffic;
                }

                if ( xQueueSend( xTrafficQueueHandle, &ulTraffic, QUEUE_OP_TIMEOUT ) )
                {
                    printf("[Traffic Flow Task] Sent traffic to queue. Updating shift register.\n");
                    vSetShiftRegister( ulTraffic, LANE_CAPACITY );
                }
                else
                {
                    printf("[Traffic Flow Task] Failed to send traffic to queue.\n");
                }
            }
            else
            {
                printf("[Traffic Flow Task] Failed to receive traffic from queue.\n");
            }

            /* Put the value back on the queue */
            if ( xQueueSend( xTrafficLightStateQueueHandle, &ucTrafficLightState, QUEUE_OP_TIMEOUT ) )
            {
                printf("[Traffic Flow Task] Sent traffic light state to queue.\n");
            } else {
                printf("[Traffic Flow Task] Failed to send traffic light state to queue.\n");
            }
        }
        else
        {
            printf("[Traffic Flow Task] Failed to received traffic light state from queue.\n");
        }
        vTaskDelay(1000);
    }
}
