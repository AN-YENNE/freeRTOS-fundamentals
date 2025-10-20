// File: main.c
// Description:
// Demonstrates FreeRTOS task priorities and dynamic priority change in the Windows simulator.
// - Low priority task: prints every 1 second.
// - Medium priority task: prints every 500 ms.
// - High priority task: runs 5 times at highest priority, then lowers its priority to lowest.

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// Task handles for reference (not strictly required here)
TaskHandle_t lowTaskHandle = NULL;
TaskHandle_t medTaskHandle = NULL;
TaskHandle_t highTaskHandle = NULL;

// -----------------------------------------------------------------------------
// Low Priority Task: runs every 1 second
// -----------------------------------------------------------------------------
void low_priority_task(void *pvParameters)
{
    (void)pvParameters;
    while (1)
    {
        printf("Low Priority Task running every 1 second\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay
    }
}

// -----------------------------------------------------------------------------
// Medium Priority Task: runs every 500 ms
// -----------------------------------------------------------------------------
void medium_priority_task(void *pvParameters)
{
    (void)pvParameters;
    while (1)
    {
        printf("Medium Priority Task running every 500 ms\n");
        vTaskDelay(pdMS_TO_TICKS(500)); // 500 ms delay
    }
}

// -----------------------------------------------------------------------------
// High Priority Task:
// Runs 5 iterations at high priority, then lowers its own priority to low.
// -----------------------------------------------------------------------------
void high_priority_task(void *pvParameters)
{
    (void)pvParameters;

    for (int i = 1; i <= 5; i++)
    {
        printf("High Priority Task iteration %d\n", i);
        vTaskDelay(pdMS_TO_TICKS(500)); // Simulate work with 500 ms delay
    }

    printf("High Priority Task lowering its priority to lowest...\n");
    vTaskPrioritySet(NULL, 1); // Change own priority to 1 (lowest)

    while (1)
    {
        printf("High Priority Task (now low priority) still running...\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Runs less often now
    }
}

// -----------------------------------------------------------------------------
// Main entry point for FreeRTOS Windows simulator
// -----------------------------------------------------------------------------
int main(void)
{
    // Create Low Priority Task with priority 1
    xTaskCreate(low_priority_task, "LowPriorityTask", configMINIMAL_STACK_SIZE, NULL, 1, &lowTaskHandle);

    // Create Medium Priority Task with priority 2
    xTaskCreate(medium_priority_task, "MediumPriorityTask", configMINIMAL_STACK_SIZE, NULL, 2, &medTaskHandle);

    // Create High Priority Task with priority 3
    xTaskCreate(high_priority_task, "HighPriorityTask", configMINIMAL_STACK_SIZE, NULL, 3, &highTaskHandle);

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here if scheduler is running correctly
    printf("Scheduler stopped unexpectedly.\n");
    return 0;
}
