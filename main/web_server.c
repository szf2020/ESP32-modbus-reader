#include "web_server.h"
#include "nvs_storage.h"
#include "wifi_manager.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "cJSON.h"
#include <string.h>

extern const char index_html_start[] asm("_binary_index_html_start");
extern const char index_html_end[] asm("_binary_index_html_end");
extern const char style_css_start[] asm("_binary_style_css_start");
extern const char style_css_end[] asm("_binary_style_css_end");
extern const char script_js_start[] asm("_binary_script_js_start");
extern const char script_js_end[] asm("_binary_script_js_end");

static const char *TAG = "WEB_SERVER";
static httpd_handle_t server = NULL;

static esp_err_t get_root_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Serving index.html");
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, index_html_start, index_html_end - index_html_start);
    return ESP_OK;
}

static esp_err_t get_css_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Serving style.css");
    httpd_resp_set_type(req, "text/css");
    httpd_resp_send(req, style_css_start, style_css_end - style_css_start);
    return ESP_OK;
}

static esp_err_t get_js_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Serving script.js");
    httpd_resp_set_type(req, "application/javascript");
    httpd_resp_send(req, script_js_start, script_js_end - script_js_start);
    return ESP_OK;
}

static esp_err_t get_status_handler(httpd_req_t *req)
{
    wifi_status_t status;
    wifi_manager_get_status(&status);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "connected", status.is_connected);
    cJSON_AddStringToObject(root, "mode", status.mode == WIFI_CONNECTION_MODE_AP ? "AP" : "STA");
    cJSON_AddStringToObject(root, "ip", status.ip_address);
    cJSON_AddStringToObject(root, "ssid", status.ssid);
    cJSON_AddNumberToObject(root, "rssi", status.rssi);

    char *json_str = cJSON_PrintUnformatted(root);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, json_str, strlen(json_str));

    free(json_str);
    cJSON_Delete(root);

    ESP_LOGI(TAG, "Status sent: %s", json_str);
    return ESP_OK;
}

static esp_err_t post_save_handler(httpd_req_t *req)
{
    char buf[256];
    int ret = httpd_req_recv(req, buf, sizeof(buf));
    if (ret <= 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Failed to receive data");
        return ESP_FAIL;
    }
    buf[ret] = '\0';

    ESP_LOGI(TAG, "Received credentials: %s", buf);

    char ssid[WIFI_SSID_MAX_LEN] = {0};
    char password[WIFI_PASSWORD_MAX_LEN] = {0};

    char *ssid_ptr = strstr(buf, "ssid=");
    char *pass_ptr = strstr(buf, "password=");

    if (ssid_ptr && pass_ptr) {
        sscanf(ssid_ptr, "ssid=%32[^&]", ssid);
        sscanf(pass_ptr, "password=%64s", password);

        ESP_LOGI(TAG, "Saving SSID: %s", ssid);

        if (nvs_save_wifi_credentials(ssid, password) == ESP_OK) {
            httpd_resp_set_type(req, "text/html");
            httpd_resp_send(req, "Credentials saved. Rebooting...", strlen("Credentials saved. Rebooting..."));
            
            vTaskDelay(pdMS_TO_TICKS(2000));
            esp_restart();
            return ESP_OK;
        } else {
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to save credentials");
            return ESP_FAIL;
        }
    }

    httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid data format");
    return ESP_FAIL;
}

static esp_err_t post_clear_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Clearing credentials");
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "Credentials cleared. Rebooting...", strlen("Credentials cleared. Rebooting..."));

    vTaskDelay(pdMS_TO_TICKS(2000));
    wifi_manager_clear_credentials();
    return ESP_OK;
}

static const httpd_uri_t uri_handlers[] = {
    {
        .uri = "/",
        .method = HTTP_GET,
        .handler = get_root_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/style.css",
        .method = HTTP_GET,
        .handler = get_css_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/script.js",
        .method = HTTP_GET,
        .handler = get_js_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/status",
        .method = HTTP_GET,
        .handler = get_status_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/save",
        .method = HTTP_POST,
        .handler = post_save_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/clear",
        .method = HTTP_POST,
        .handler = post_clear_handler,
        .user_ctx = NULL
    }
};

esp_err_t web_server_start(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    ESP_LOGI(TAG, "Starting HTTP server on port %d", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        for (size_t i = 0; i < sizeof(uri_handlers) / sizeof(uri_handlers[0]); i++) {
            if (httpd_register_uri_handler(server, &uri_handlers[i]) != ESP_OK) {
                ESP_LOGE(TAG, "Failed to register URI handler: %s", uri_handlers[i].uri);
                return ESP_FAIL;
            }
        }
        ESP_LOGI(TAG, "HTTP server started successfully");
        return ESP_OK;
    }

    ESP_LOGE(TAG, "Failed to start HTTP server");
    return ESP_FAIL;
}

esp_err_t web_server_stop(void)
{
    if (server) {
        httpd_stop(server);
        server = NULL;
        ESP_LOGI(TAG, "HTTP server stopped");
    }
    return ESP_OK;
}
