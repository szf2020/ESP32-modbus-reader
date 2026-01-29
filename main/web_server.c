#include "web_server.h"
#include "nvs_storage.h"
#include "wifi_manager.h"
#include "modbus_devices.h"
#include "modbus_manager.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

extern const char index_html_start[] asm("_binary_index_html_start");
extern const char index_html_end[] asm("_binary_index_html_end");
extern const char style_css_start[] asm("_binary_style_css_start");
extern const char style_css_end[] asm("_binary_style_css_end");
extern const char script_js_start[] asm("_binary_script_js_start");
extern const char script_js_end[] asm("_binary_script_js_end");
extern const char modbus_html_start[] asm("_binary_modbus_html_start");
extern const char modbus_html_end[] asm("_binary_modbus_html_end");
extern const char dashboard_html_start[] asm("_binary_dashboard_html_start");
extern const char dashboard_html_end[] asm("_binary_dashboard_html_end");
extern const char modbus_js_start[] asm("_binary_modbus_js_start");
extern const char modbus_js_end[] asm("_binary_modbus_js_end");

static const char *TAG = "WEB_SERVER";
static httpd_handle_t server = NULL;

static char* extract_query_value(const char *query, const char *key)
{
    if (query == NULL || key == NULL) {
        return NULL;
    }
    
    const char *start = strstr(query, key);
    if (start == NULL) {
        return NULL;
    }
    
    start += strlen(key);
    if (*start != '=') {
        return NULL;
    }
    
    start++; 
    
    const char *end = strchr(start, '&');
    size_t len;
    
    if (end != NULL) {
        len = end - start;
    } else {
        len = strlen(start);
    }
    
    char *value = malloc(len + 1);
    if (value == NULL) {
        return NULL;
    }
    
    memcpy(value, start, len);
    value[len] = '\0';
    
    return value;
}

static esp_err_t get_static_file_handler(httpd_req_t *req)
{
    const char *uri = req->uri;
    const char *filename = NULL;
    const char *content_type = NULL;
    const char *file_start;
    const char *file_end;

    if (strcmp(uri, "/style.css") == 0) {
        filename = "style.css";
        content_type = "text/css";
        file_start = style_css_start;
        file_end = style_css_end;
    } else if (strcmp(uri, "/script.js") == 0) {
        filename = "script.js";
        content_type = "application/javascript";
        file_start = script_js_start;
        file_end = script_js_end;
    } else if (strcmp(uri, "/modbus.html") == 0) {
        filename = "modbus.html";
        content_type = "text/html";
        file_start = modbus_html_start;
        file_end = modbus_html_end;
    } else if (strcmp(uri, "/dashboard.html") == 0) {
        filename = "dashboard.html";
        content_type = "text/html";
        file_start = dashboard_html_start;
        file_end = dashboard_html_end;
    } else if (strcmp(uri, "/modbus.js") == 0) {
        filename = "modbus.js";
        content_type = "application/javascript";
        file_start = modbus_js_start;
        file_end = modbus_js_end;
    } else {
        httpd_resp_send_404(req);
        return ESP_OK;
    }

    httpd_resp_set_type(req, content_type);
    httpd_resp_send(req, file_start, file_end - file_start);

    ESP_LOGI(TAG, "Serving %s", filename);
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

    ESP_LOGI(TAG, "Status sent: %s", json_str);
    free(json_str);
    cJSON_Delete(root);

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



static esp_err_t api_get_devices_handler(httpd_req_t *req)
{
    modbus_device_t devices[MAX_MODBUS_DEVICES];
    uint8_t count = 0;
    esp_err_t err = modbus_list_devices(devices, &count);

    if (err != ESP_OK) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to get devices");
        return ESP_FAIL;
    }

    cJSON *root = cJSON_CreateArray();
    for (uint8_t i = 0; i < count; i++) {
        cJSON *device = cJSON_CreateObject();
        cJSON_AddNumberToObject(device, "device_id", devices[i].device_id);
        cJSON_AddStringToObject(device, "name", devices[i].name);
        cJSON_AddStringToObject(device, "description", devices[i].description);
        cJSON_AddNumberToObject(device, "poll_interval_ms", devices[i].poll_interval_ms);
        cJSON_AddNumberToObject(device, "baudrate", devices[i].baudrate);
        cJSON_AddNumberToObject(device, "enabled", devices[i].enabled);
        cJSON_AddNumberToObject(device, "status", devices[i].status);
        cJSON_AddNumberToObject(device, "last_error", devices[i].last_error);
        cJSON_AddNumberToObject(device, "poll_count", devices[i].poll_count);
        cJSON_AddNumberToObject(device, "error_count", devices[i].error_count);

        cJSON *registers = cJSON_CreateArray();
        for (uint8_t j = 0; j < devices[i].register_count; j++) {
            cJSON *reg = cJSON_CreateObject();
            cJSON_AddNumberToObject(reg, "address", devices[i].registers[j].address);
            cJSON_AddNumberToObject(reg, "type", devices[i].registers[j].type);
            cJSON_AddStringToObject(reg, "name", devices[i].registers[j].name);
            cJSON_AddStringToObject(reg, "unit", devices[i].registers[j].unit);
            cJSON_AddNumberToObject(reg, "scale", devices[i].registers[j].scale);
            cJSON_AddNumberToObject(reg, "offset", devices[i].registers[j].offset);
            cJSON_AddNumberToObject(reg, "writable", devices[i].registers[j].writable);
            cJSON_AddNumberToObject(reg, "last_value", devices[i].registers[j].last_value);
            cJSON_AddNumberToObject(reg, "last_update", devices[i].registers[j].last_update);
            cJSON_AddItemToArray(registers, reg);
        }
        cJSON_AddNumberToObject(device, "register_count", devices[i].register_count);
        cJSON_AddItemToObject(device, "registers", registers);
        cJSON_AddItemToArray(root, device);
    }

    char *json_str = cJSON_PrintUnformatted(root);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, json_str, strlen(json_str));

    free(json_str);
    cJSON_Delete(root);

    return ESP_OK;
}

static esp_err_t api_post_device_handler(httpd_req_t *req)
{
    char buf[512];
    int ret = httpd_req_recv(req, buf, sizeof(buf));
    if (ret <= 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Failed to receive data");
        return ESP_FAIL;
    }
    buf[ret] = '\0';

    cJSON *root = cJSON_Parse(buf);
    if (root == NULL) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    modbus_device_t device = {0};
    device.device_id = cJSON_GetObjectItem(root, "device_id")->valueint;
    strncpy(device.name, cJSON_GetObjectItem(root, "name")->valuestring, sizeof(device.name) - 1);
    
    cJSON *desc = cJSON_GetObjectItem(root, "description");
    if (desc && desc->valuestring) {
        strncpy(device.description, desc->valuestring, sizeof(device.description) - 1);
    }
    
    device.poll_interval_ms = cJSON_GetObjectItem(root, "poll_interval_ms")->valueint;
    device.baudrate = cJSON_GetObjectItem(root, "baudrate")->valueint;
    device.enabled = cJSON_GetObjectItem(root, "enabled")->type == cJSON_True;
    device.register_count = 0;

    esp_err_t err = modbus_add_device(&device);
    if (err == ESP_OK) {
        modbus_devices_save();
        httpd_resp_set_type(req, "application/json");
        httpd_resp_send(req, "{\"status\":\"ok\"}", 15);
    } else {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to add device");
    }

    cJSON_Delete(root);
    return err;
}

static esp_err_t api_delete_device_handler(httpd_req_t *req)
{
    char url_buf[100];
    char *device_id_str = NULL;

    if (httpd_req_get_url_query_str(req, url_buf, sizeof(url_buf)) == ESP_OK) {
        device_id_str = extract_query_value(url_buf, "device_id");
        if (device_id_str != NULL) {
            uint8_t device_id = atoi(device_id_str);
            free(device_id_str);
            
            esp_err_t err = modbus_remove_device(device_id);
            
            if (err == ESP_OK) {
                modbus_devices_save();
                httpd_resp_set_type(req, "application/json");
                httpd_resp_send(req, "{\"status\":\"ok\"}", 15);
                return ESP_OK;
            }
        }
    }

    httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid request");
    if (device_id_str) free(device_id_str);
    return ESP_FAIL;
}

static esp_err_t api_post_register_handler(httpd_req_t *req)
{
    char buf[512];
    int ret = httpd_req_recv(req, buf, sizeof(buf));
    if (ret <= 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Failed to receive data");
        return ESP_FAIL;
    }
    buf[ret] = '\0';

    cJSON *root = cJSON_Parse(buf);
    if (root == NULL) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    modbus_register_t reg = {0};
    reg.address = cJSON_GetObjectItem(root, "address")->valueint;
    reg.type = cJSON_GetObjectItem(root, "type")->valueint;
    strncpy(reg.name, cJSON_GetObjectItem(root, "name")->valuestring, sizeof(reg.name) - 1);
    
    cJSON *unit = cJSON_GetObjectItem(root, "unit");
    if (unit && unit->valuestring) {
        strncpy(reg.unit, unit->valuestring, sizeof(reg.unit) - 1);
    }
    
    reg.scale = cJSON_GetObjectItem(root, "scale")->valuedouble;
    reg.offset = cJSON_GetObjectItem(root, "offset")->valuedouble;
    reg.writable = cJSON_GetObjectItem(root, "writable")->type == cJSON_True;
    
    cJSON *desc = cJSON_GetObjectItem(root, "description");
    if (desc && desc->valuestring) {
        strncpy(reg.description, desc->valuestring, sizeof(reg.description) - 1);
    }

    uint8_t device_id = cJSON_GetObjectItem(root, "device_id")->valueint;
    esp_err_t err = modbus_add_register(device_id, &reg);
    
    if (err == ESP_OK) {
        modbus_devices_save();
        httpd_resp_set_type(req, "application/json");
        httpd_resp_send(req, "{\"status\":\"ok\"}", 15);
    } else {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to add register");
    }

    cJSON_Delete(root);
    return err;
}

static esp_err_t api_delete_register_handler(httpd_req_t *req)
{
    char url_buf[100];
    char *device_id_str = NULL;
    char *address_str = NULL;

    if (httpd_req_get_url_query_str(req, url_buf, sizeof(url_buf)) == ESP_OK) {
        device_id_str = extract_query_value(url_buf, "device_id");
        address_str = extract_query_value(url_buf, "address");
        
        if (device_id_str != NULL && address_str != NULL) {
            uint8_t device_id = atoi(device_id_str);
            uint16_t address = atoi(address_str);
            free(device_id_str);
            free(address_str);
            
            esp_err_t err = modbus_remove_register(device_id, address);
            
            if (err == ESP_OK) {
                modbus_devices_save();
                httpd_resp_set_type(req, "application/json");
                httpd_resp_send(req, "{\"status\":\"ok\"}", 15);
                return ESP_OK;
            }
        }
    }

    httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid request");
    if (device_id_str) free(device_id_str);
    if (address_str) free(address_str);
    return ESP_FAIL;
}

static esp_err_t api_post_write_handler(httpd_req_t *req)
{
    char url_buf[100];
    char *device_id_str = NULL;
    char *address_str = NULL;

    if (httpd_req_get_url_query_str(req, url_buf, sizeof(url_buf)) == ESP_OK) {
        device_id_str = extract_query_value(url_buf, "device_id");
        address_str = extract_query_value(url_buf, "address");
        
        if (device_id_str != NULL && address_str != NULL) {
            
            char buf[100];
            int ret = httpd_req_recv(req, buf, sizeof(buf));
            if (ret <= 0) {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Failed to receive data");
                if (device_id_str) free(device_id_str);
                if (address_str) free(address_str);
                return ESP_FAIL;
            }
            buf[ret] = '\0';

            cJSON *root = cJSON_Parse(buf);
            if (root == NULL) {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
                if (device_id_str) free(device_id_str);
                if (address_str) free(address_str);
                return ESP_FAIL;
            }

            uint8_t device_id = atoi(device_id_str);
            uint16_t address = atoi(address_str);
            cJSON *value_item = cJSON_GetObjectItem(root, "value");
            uint16_t value = (value_item && cJSON_IsNumber(value_item)) ? value_item->valueint : 0;

            free(device_id_str);
            free(address_str);

            modbus_result_t result = modbus_write_single_register(device_id, address, value);
            
            if (result == MODBUS_RESULT_OK) {
                modbus_update_register_value(device_id, address, value);
                httpd_resp_set_type(req, "application/json");
                httpd_resp_send(req, "{\"status\":\"ok\"}", 15);
                cJSON_Delete(root);
                return ESP_OK;
            } else {
                httpd_resp_set_type(req, "application/json");
                char response[100];
                snprintf(response, sizeof(response), "{\"status\":\"error\",\"message\":\"%s\"}", 
                         modbus_result_to_string(result));
                httpd_resp_send(req, response, strlen(response));
                cJSON_Delete(root);
                return ESP_OK;
            }
        }
    }

    httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid request");
    if (device_id_str) free(device_id_str);
    if (address_str) free(address_str);
    return ESP_FAIL;
}

static esp_err_t root_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Root handler called");
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, index_html_start, index_html_end - index_html_start);
    return ESP_OK;
}

static const httpd_uri_t uri_handlers[] = {
    {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/style.css",
        .method = HTTP_GET,
        .handler = get_static_file_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/script.js",
        .method = HTTP_GET,
        .handler = get_static_file_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/modbus.html",
        .method = HTTP_GET,
        .handler = get_static_file_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/dashboard.html",
        .method = HTTP_GET,
        .handler = get_static_file_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/modbus.js",
        .method = HTTP_GET,
        .handler = get_static_file_handler,
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
    },
    {
        .uri = "/api/modbus/devices",
        .method = HTTP_GET,
        .handler = api_get_devices_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/api/modbus/devices",
        .method = HTTP_POST,
        .handler = api_post_device_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/api/modbus/devices/*",
        .method = HTTP_DELETE,
        .handler = api_delete_device_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/api/modbus/registers",
        .method = HTTP_POST,
        .handler = api_post_register_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/api/modbus/devices/*/registers/*",
        .method = HTTP_DELETE,
        .handler = api_delete_register_handler,
        .user_ctx = NULL
    },
    {
        .uri = "/api/modbus/devices/*/write/*",
        .method = HTTP_POST,
        .handler = api_post_write_handler,
        .user_ctx = NULL
    }
};

esp_err_t web_server_start(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;

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
