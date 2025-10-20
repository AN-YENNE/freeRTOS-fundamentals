#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

void Task1(void *pvParameters)
{
    (void) pvParameters;
    for (;;)
    {
        printf("Hello from Task 1!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // 1 second
    }
}

void Task2(void *pvParameters)
{
    (void) pvParameters;
    for (;;)
    {
        printf("Hello from Task 2!\n");
        vTaskDelay(pdMS_TO_TICKS(500));  // 0.5 second
    }
}

int main(void)
{
    printf("Starting FreeRTOS demo on PC...\n");

    xTaskCreate(Task1, "Task1", 1000, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 1000, NULL, 1, NULL);

    vTaskStartScheduler();

    // Should never reach here
    for (;;);
}
