// File: main.c
// Description:
// Compare FreeRTOS vTaskDelay (relative delay) vs vTaskDelayUntil (absolute periodic delay).
// Runs two tasks that print system uptime every 1 second, showing timing drift difference.

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// -----------------------------------------------------------------------------
// Task using vTaskDelay - relative delay, may accumulate timing drift
// -----------------------------------------------------------------------------
void task_delay(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        // Print current uptime in milliseconds
        printf("vTaskDelay: %lu ms\n", (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        // Delay for 1000 ms relative to current time (may drift)
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// -----------------------------------------------------------------------------
// Task using vTaskDelayUntil - absolute delay, maintains stable periodicity
// -----------------------------------------------------------------------------
void task_delay_until(void *pvParameters)
{
    (void)pvParameters;

    // Initialize last wake time to current tick count
    TickType_t last_wake_time = xTaskGetTickCount();

    while (1)
    {
        // Print current uptime in milliseconds
        printf("vTaskDelayUntil: %lu ms\n", (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        // Delay until next 1000 ms period relative to last wake time (minimizes drift)
        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(1000));
    }
}

// -----------------------------------------------------------------------------
// Main entry point for FreeRTOS Windows simulator
// -----------------------------------------------------------------------------
int main(void)
{
    // Create task with relative delay (priority 2)
    xTaskCreate(task_delay, "TaskDelay", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    // Create task with absolute delay (priority 2)
    xTaskCreate(task_delay_until, "TaskDelayUntil", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here if scheduler is running
    printf("Scheduler stopped unexpectedly.\n");
    return 0;
}
