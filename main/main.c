#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_storage.h"
#include "wifi_manager.h"
#include "web_server.h"

static const char *TAG = "APP";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting ESP32 WiFi Manager");

    ESP_ERROR_CHECK(nvs_storage_init());
    ESP_LOGI(TAG, "NVS storage initialized");

    ESP_ERROR_CHECK(wifi_manager_init());
    ESP_LOGI(TAG, "WiFi manager initialized");

    ESP_ERROR_CHECK(wifi_manager_start());
    ESP_LOGI(TAG, "WiFi operations started");

    ESP_ERROR_CHECK(web_server_start());
    ESP_LOGI(TAG, "Web server started");

    ESP_LOGI(TAG, "ESP32 WiFi Manager is running");

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));
        ESP_LOGI(TAG, "System running normally");
    }
}
