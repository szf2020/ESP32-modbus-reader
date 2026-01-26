#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <stdbool.h>
#include "esp_err.h"
#include "esp_event.h"

#define AP_SSID "ESP32-Config"
#define AP_PASSWORD "config123"
#define AP_CHANNEL 1
#define AP_MAX_CONNECTIONS 4

typedef enum {
    WIFI_CONNECTION_MODE_NOT_INITIALIZED = 0,
    WIFI_CONNECTION_MODE_AP,
    WIFI_CONNECTION_MODE_STA,
    WIFI_CONNECTION_MODE_CONNECTING,
    WIFI_CONNECTION_MODE_CONNECTED
} wifi_connection_mode_t;

typedef struct {
    char ip_address[16];
    char ssid[33];
    int rssi;
    wifi_connection_mode_t mode;
    bool is_connected;
} wifi_status_t;

esp_err_t wifi_manager_init(void);
esp_err_t wifi_manager_start(void);
esp_err_t wifi_manager_connect_sta(const char *ssid, const char *password);
esp_err_t wifi_manager_start_ap(void);
esp_err_t wifi_manager_get_status(wifi_status_t *status);
void wifi_manager_clear_credentials(void);

#endif
