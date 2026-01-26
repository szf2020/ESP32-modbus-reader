#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "esp_err.h"
#include "wifi_manager.h"

esp_err_t web_server_start(void);
esp_err_t web_server_stop(void);

#endif
