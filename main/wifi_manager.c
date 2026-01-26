#include "wifi_manager.h"
#include "nvs_storage.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "string.h"

static const char *TAG = "WIFI_MANAGER";

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define MAX_RETRY_ATTEMPTS 5

static EventGroupHandle_t s_wifi_event_group;
static esp_netif_t *sta_netif = NULL;
static esp_netif_t *ap_netif = NULL;
static int s_retry_num = 0;
static wifi_connection_mode_t current_mode = WIFI_CONNECTION_MODE_NOT_INITIALIZED;
static wifi_status_t wifi_status;

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                              int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG, "WiFi station started");
        esp_wifi_connect();
        current_mode = WIFI_CONNECTION_MODE_CONNECTING;
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < MAX_RETRY_ATTEMPTS) {
            ESP_LOGI(TAG, "Retry connecting to AP (attempt %d/%d)", s_retry_num + 1, MAX_RETRY_ATTEMPTS);
            esp_wifi_connect();
            s_retry_num++;
        } else {
            ESP_LOGE(TAG, "Failed to connect to AP");
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
            current_mode = WIFI_CONNECTION_MODE_NOT_INITIALIZED;
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        current_mode = WIFI_CONNECTION_MODE_CONNECTED;
        
        snprintf(wifi_status.ip_address, sizeof(wifi_status.ip_address), IPSTR, IP2STR(&event->ip_info.ip));
        wifi_status.rssi = 0;
        wifi_status.is_connected = true;
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_START) {
        ESP_LOGI(TAG, "WiFi AP started");
        current_mode = WIFI_CONNECTION_MODE_AP;
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI(TAG, "Station "MACSTR" joined, AID=%d", MAC2STR(event->mac), event->aid);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        ESP_LOGI(TAG, "Station "MACSTR" left, AID=%d", MAC2STR(event->mac), event->aid);
    }
}

esp_err_t wifi_manager_init(void)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                       ESP_EVENT_ANY_ID,
                                                       &wifi_event_handler,
                                                       NULL,
                                                       NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                       IP_EVENT_STA_GOT_IP,
                                                       &wifi_event_handler,
                                                       NULL,
                                                       NULL));

    memset(&wifi_status, 0, sizeof(wifi_status));
    wifi_status.mode = WIFI_CONNECTION_MODE_NOT_INITIALIZED;
    wifi_status.is_connected = false;

    ESP_LOGI(TAG, "WiFi manager initialized");
    return ESP_OK;
}

esp_err_t wifi_manager_start(void)
{
    char ssid[WIFI_SSID_MAX_LEN] = {0};
    char password[WIFI_PASSWORD_MAX_LEN] = {0};

    if (nvs_has_credentials()) {
        ESP_LOGI(TAG, "Credentials found in NVS, connecting to WiFi");
        if (nvs_load_wifi_credentials(ssid, password) == ESP_OK) {
            wifi_manager_connect_sta(ssid, password);
            return ESP_OK;
        }
    }

    ESP_LOGI(TAG, "No credentials found, starting AP mode");
    return wifi_manager_start_ap();
}

esp_err_t wifi_manager_connect_sta(const char *ssid, const char *password)
{
    ESP_LOGI(TAG, "Connecting to SSID: %s", ssid);

    if (sta_netif == NULL) {
        sta_netif = esp_netif_create_default_wifi_sta();
    }

    if (ap_netif != NULL) {
        esp_netif_destroy(ap_netif);
        ap_netif = NULL;
    }

    wifi_config_t wifi_config = {0};
    strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    s_retry_num = 0;
    strncpy(wifi_status.ssid, ssid, sizeof(wifi_status.ssid) - 1);

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           pdMS_TO_TICKS(30000));

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "Connected to SSID: %s", ssid);
        return ESP_OK;
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGE(TAG, "Failed to connect to SSID: %s", ssid);
        return ESP_FAIL;
    } else {
        ESP_LOGE(TAG, "Connection timeout");
        return ESP_ERR_TIMEOUT;
    }
}

esp_err_t wifi_manager_start_ap(void)
{
    ESP_LOGI(TAG, "Starting AP mode");

    if (ap_netif == NULL) {
        ap_netif = esp_netif_create_default_wifi_ap();
    }

    if (sta_netif != NULL) {
        esp_netif_destroy(sta_netif);
        sta_netif = NULL;
    }

    wifi_config_t wifi_config = {
        .ap = {
            .ssid_len = strlen(AP_SSID),
            .channel = AP_CHANNEL,
            .max_connection = AP_MAX_CONNECTIONS,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    strncpy((char *)wifi_config.ap.ssid, AP_SSID, sizeof(wifi_config.ap.ssid) - 1);
    strncpy((char *)wifi_config.ap.password, AP_PASSWORD, sizeof(wifi_config.ap.password) - 1);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    strncpy(wifi_status.ip_address, "192.168.4.1", sizeof(wifi_status.ip_address) - 1);
    strncpy(wifi_status.ssid, AP_SSID, sizeof(wifi_status.ssid) - 1);
    wifi_status.mode = WIFI_MODE_AP;
    wifi_status.is_connected = false;
    wifi_status.rssi = 0;

    ESP_LOGI(TAG, "AP mode started. SSID: %s, IP: 192.168.4.1", AP_SSID);
    return ESP_OK;
}

esp_err_t wifi_manager_get_status(wifi_status_t *status)
{
    if (status == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    memcpy(status, &wifi_status, sizeof(wifi_status_t));
    return ESP_OK;
}

void wifi_manager_clear_credentials(void)
{
    nvs_clear_wifi_credentials();
    ESP_LOGI(TAG, "Credentials cleared, restarting in AP mode");
    esp_restart();
}
