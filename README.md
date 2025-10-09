# FreeRTOS Task Examples for STM32

This repository contains a series of practical **FreeRTOS task management examples** designed for STM32 microcontrollers. Each example demonstrates core FreeRTOS concepts such as task creation, parameter passing, priority management, suspension, resumption, deletion, and more.

---

## Contents

| Example                     | Description                                                     |
| --------------------------- | --------------------------------------------------------------- |
| `task_creation`             | Basic creation of two tasks with task profilers                 |
| `task_creation_with_output` | Toggling GPIO pin (LED) and UART print in separate tasks        |
| `task_parameters`           | Passing parameters to a shared task function                    |
| `task_priority`             | Task priority assignment and usage of `vTaskDelay` for yielding |
| `change_task_priority`      | Dynamically changing the priority of a task                     |
| `read_task_priority`        | Reading the priority of a task at runtime                       |
| `suspend_task`              | Suspending a task based on a threshold                          |
| `resume_task`               | Resuming a suspended task after a certain threshold             |
| `delete_task`               | Deleting a task after reaching a runtime condition              |

---

## Prerequisites

* STM32 microcontroller development board (e.g., STM32F4 series)
* STM32CubeMX and STM32CubeIDE (or equivalent toolchain)
* FreeRTOS library integrated in your project
* UART configured for debugging output (usually USART2)
* Basic familiarity with embedded C and FreeRTOS API

---

## Getting Started

1. Clone the repository

2. Open the project in STM32CubeIDE or your preferred IDE.

3. Build and flash the example onto your STM32 board.

4. Open a serial terminal at the configured baud rate to observe UART outputs.

5. Experiment by modifying thresholds, priorities, and task parameters.

---

## Summary of Key FreeRTOS APIs Covered

* `xTaskCreate()` — Create tasks
* `vTaskStartScheduler()` — Start the RTOS scheduler
* `vTaskPrioritySet()` — Change task priority
* `uxTaskPriorityGet()` — Read task priority
* `vTaskSuspend()` — Suspend a task
* `vTaskResume()` — Resume a suspended task
* `vTaskDelete()` — Delete a task

---

## Contribution

Feel free to fork this repository, add more examples, or improve existing ones! Pull requests and issues are welcome.

---

## Acknowledgments

* FreeRTOS official documentation and community for their excellent resources.
* STM32CubeMX and STM32CubeIDE for easing STM32 development.

---
