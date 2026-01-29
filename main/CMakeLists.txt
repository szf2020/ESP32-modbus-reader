idf_component_register(SRCS "main.c" "wifi_manager.c" "web_server.c" "nvs_storage.c"
                       "modbus_protocol.c" "modbus_devices.c" "modbus_manager.c"
                     INCLUDE_DIRS "."
                     EMBED_FILES "html/index.html" "html/style.css" "html/script.js"
                     "html/modbus.html" "html/dashboard.html" "html/modbus.js")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-error=format" "-Wformat-security")
