idf_component_register(SRCS "main.c" "wifi_manager.c" "web_server.c" "nvs_storage.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES "html/index.html" "html/style.css" "html/script.js")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-error=format")
