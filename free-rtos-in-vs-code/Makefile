CC = gcc
CFLAGS = -I. -IFreeRTOS-Kernel/include -IFreeRTOS-Kernel/portable/MSVC-MingW -Wall -Wextra
SRC = main.c \
      FreeRTOS-Kernel/list.c \
      FreeRTOS-Kernel/queue.c \
      FreeRTOS-Kernel/tasks.c \
      FreeRTOS-Kernel/timers.c \
      FreeRTOS-Kernel/portable/MemMang/heap_3.c \
      FreeRTOS-Kernel/portable/MSVC-MingW/port.c

TARGET = freertos_demo

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET).exe
