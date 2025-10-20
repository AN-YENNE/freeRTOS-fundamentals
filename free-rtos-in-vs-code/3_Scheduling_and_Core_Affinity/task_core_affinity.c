// File: main/task_core_affinity.c
// Description:
// This FreeRTOS example demonstrates creating tasks with and without CPU core affinity on ESP32.
// One task is unpinned and may run on either core. Another is pinned to Core 1 only.

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ============================================================================
// Task: Unpinned (can run on either core)
// ============================================================================
void task_unpinned(void *pvParameters)
{
    while (1)
    {
        printf("Unpinned Task running on Core %d\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

// ============================================================================
// Task: Pinned to Core 1
// ============================================================================
void task_pinned_core1(void *pvParameters)
{
    while (1)
    {
        printf("Pinned Task running on Core %d\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

// ============================================================================
// Application entry point for ESP32
// ============================================================================
void app_main(void)
{
    // Create an unpinned task (runs on any core)
    xTaskCreate(
        task_unpinned,
        "Unpinned Task",
        2048,
        NULL,
        5,
        NULL
    );

    // Create a task pinned specifically to Core 1
    xTaskCreatePinnedToCore(
        task_pinned_core1,
        "Pinned Task Core1",
        2048,
        NULL,
        5,
        NULL,
        1 // Core 1
    );
}
