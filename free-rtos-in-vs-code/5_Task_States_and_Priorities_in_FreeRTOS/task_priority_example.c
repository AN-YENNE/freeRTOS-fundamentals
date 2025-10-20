// File: main.c
// Description:
// Demonstrates FreeRTOS task priorities using the Windows simulator.
// - task_low: runs every 1 second with lower priority
// - task_high: runs every 0.5 seconds with higher priority

#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

// -----------------------------------------------------------------------------
// Task: task_low
// - Low-priority task that runs every 1 second
// -----------------------------------------------------------------------------
void task_low(void *pvParameters)
{
    while (1)
    {
        printf("Low-priority task running\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

// -----------------------------------------------------------------------------
// Task: task_high
// - High-priority task that runs every 0.5 seconds
// -----------------------------------------------------------------------------
void task_high(void *pvParameters)
{
    while (1)
    {
        printf("High-priority task running\n");
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 0.5 seconds
    }
}

// -----------------------------------------------------------------------------
// Main entry point for FreeRTOS Windows simulator
// -----------------------------------------------------------------------------
int main(void)
{
    // Create low-priority task
    xTaskCreate(
        task_low,
        "Low Priority Task",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,   // Lower priority
        NULL
    );

    // Create high-priority task
    xTaskCreate(
        task_high,
        "High Priority Task",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,   // Higher priority
        NULL
    );

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // This line should never run
    printf("Scheduler stopped unexpectedly.\n");
    return 0;
}
