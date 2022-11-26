#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define RL1 GPIO_NUM_23
#define RL2 GPIO_NUM_25
#define RL3 GPIO_NUM_22
#define RL4 GPIO_NUM_21
#define RL5 GPIO_NUM_4
#define TAG "main"

static void gpio_task_RL(void* arg)
{
    for (;;) {
        gpio_set_level(RL1, 1);
        gpio_set_level(RL2, 1);
        gpio_set_level(RL3, 1);
        gpio_set_level(RL4, 1);
        vTaskDelay(2000 / portTICK_RATE_MS);
        gpio_set_level(RL1, 0);
        gpio_set_level(RL2, 0);
        gpio_set_level(RL3, 0);
        gpio_set_level(RL4, 0);
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}
static void gpio_task_RL5(void* arg)
{
    for (;;) {
        gpio_set_level(RL5, 1);
        vTaskDelay(550 / portTICK_RATE_MS);
        gpio_set_level(RL5, 0);
        vTaskDelay(550 / portTICK_RATE_MS);
    }
}
void app_main(void)
{
    int a = 6;
    // cấu hình chân ra 
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE, // không cho phép ngắt 
        .mode = GPIO_MODE_OUTPUT, // cấu hình output
        .pin_bit_mask = (1ULL << RL1) 
                        | (1ULL << RL2)
                        | (1ULL << RL3)
                        | (1ULL << RL4)
                        | (1ULL << RL5),
    };
    gpio_config(&io_conf);
    xTaskCreate(gpio_task_RL, "gpio_task_RL", 2048, NULL, 1, NULL);
    xTaskCreate(gpio_task_RL5, "gpio_task_RL5", 2048, NULL, 1, NULL);
    while (1)
    {
        ESP_LOGI(TAG, "Nguyen Trung Thao %d", a);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}