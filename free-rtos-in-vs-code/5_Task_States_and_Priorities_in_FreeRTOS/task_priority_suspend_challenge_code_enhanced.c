// File: main.c
// Description:
// Demonstrates FreeRTOS task priorities and suspension on Windows simulator.
// - task_low: low priority, prints every 1 second, can be suspended/resumed.
// - task_high: high priority, prints every 0.5 seconds, suspends task_low periodically.

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// Handle for low priority task so high priority task can suspend/resume it
static TaskHandle_t lowTaskHandle = NULL;

// -----------------------------------------------------------------------------
// Low priority task: prints every 1 second
// -----------------------------------------------------------------------------
void task_low(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        printf("[LOW ] Running\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1 second
    }
}

// -----------------------------------------------------------------------------
// High priority task: prints every 0.5 seconds, suspends low task periodically
// -----------------------------------------------------------------------------
void task_high(void *pvParameters)
{
    (void)pvParameters;

    int iteration = 0;
    const TickType_t suspendDuration = pdMS_TO_TICKS(3000); // 3 seconds

    while (1)
    {
        printf("[HIGH] Running (iter=%d)\n", iteration);

        // Every 6 iterations (~3 seconds), suspend low task for 3 seconds
        if ((iteration % 6) == 0 && lowTaskHandle != NULL)
        {
            printf("[HIGH] Suspending LOW task for 3 seconds...\n");
            vTaskSuspend(lowTaskHandle);

            TickType_t startTick = xTaskGetTickCount();
            while ((xTaskGetTickCount() - startTick) < suspendDuration)
            {
                printf("[HIGH] LOW task is suspended...\n");
                vTaskDelay(pdMS_TO_TICKS(500));
            }

            printf("[HIGH] Resuming LOW task now.\n");
            vTaskResume(lowTaskHandle);
        }

        vTaskDelay(pdMS_TO_TICKS(500)); // Delay 0.5 seconds
        iteration++;
    }
}

// -----------------------------------------------------------------------------
// Main entry point for FreeRTOS Windows simulator
// -----------------------------------------------------------------------------
int main(void)
{
    // Create low priority task (priority 1)
    xTaskCreate(
        task_low,
        "Low Priority Task",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &lowTaskHandle
    );

    // Create high priority task (priority 3)
    xTaskCreate(
        task_high,
        "High Priority Task",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,
        NULL
    );

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    printf("Scheduler stopped unexpectedly.\n");
    return 0;
}
