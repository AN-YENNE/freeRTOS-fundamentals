// File: main.c
// Description:
// Demonstrates task creation and deletion using the FreeRTOS Windows simulator.
// - hello_task prints a counter and self-deletes after 5 iterations.
// - control_task deletes hello_task after 3 seconds (if it's still running), then deletes itself.

#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

// Handle for the hello_task so it can be deleted by another task
TaskHandle_t helloTaskHandle = NULL;

// -----------------------------------------------------------------------------
// Task: hello_task
// - Prints a counter every second
// - Deletes itself after 5 iterations
// -----------------------------------------------------------------------------
void hello_task(void *pvParameters)
{
    int counter = 0;

    while (1)
    {
        printf("Hello Task running, counter = %d\n", counter++);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second

        if (counter >= 5)
        {
            printf("Hello Task deleting itself...\n");
            vTaskDelete(NULL); // Delete this task
        }
    }
}

// -----------------------------------------------------------------------------
// Task: control_task
// - Waits for 3 seconds
// - Deletes hello_task if it's still running
// - Deletes itself
// -----------------------------------------------------------------------------
void control_task(void *pvParameters)
{
    printf("Control Task started. Waiting 3 seconds...\n");
    vTaskDelay(pdMS_TO_TICKS(3000)); // Wait 3 seconds

    if (helloTaskHandle != NULL)
    {
        printf("Control Task deleting Hello Task...\n");
        vTaskDelete(helloTaskHandle);
        helloTaskHandle = NULL;
    }

    printf("Control Task deleting itself...\n");
    vTaskDelete(NULL); // Delete this task
}

// -----------------------------------------------------------------------------
// Main entry point (for FreeRTOS Windows port)
// -----------------------------------------------------------------------------
int main(void)
{
    // Create the Hello Task (with higher priority)
    xTaskCreate(
        hello_task,         // Task function
        "Hello Task",       // Name
        configMINIMAL_STACK_SIZE, // Stack size
        NULL,               // Parameters
        2,                  // Priority
        &helloTaskHandle    // Task handle
    );

    // Create the Control Task (lower priority)
    xTaskCreate(
        control_task,
        "Control Task",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // If all is well, this line should never be reached
    printf("Scheduler ended unexpectedly.\n");
    return 0;
}
