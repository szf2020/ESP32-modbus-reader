#ifndef MODBUS_PROTOCOL_H
#define MODBUS_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#define MODBUS_MAX_DATA_LEN 128
#define MODBUS_MAX_FRAME_LEN 256

typedef enum {
    MODBUS_FC_READ_COILS = 0x01,
    MODBUS_FC_READ_DISCRETE_INPUTS = 0x02,
    MODBUS_FC_READ_HOLDING_REGISTERS = 0x03,
    MODBUS_FC_READ_INPUT_REGISTERS = 0x04,
    MODBUS_FC_WRITE_SINGLE_COIL = 0x05,
    MODBUS_FC_WRITE_SINGLE_REGISTER = 0x06,
    MODBUS_FC_WRITE_MULTIPLE_COILS = 0x0F,
    MODBUS_FC_WRITE_MULTIPLE_REGISTERS = 0x10
} modbus_function_code_t;

typedef enum {
    MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,
    MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS = 0x02,
    MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE = 0x03,
    MODBUS_EXCEPTION_SERVER_DEVICE_FAILURE = 0x04,
    MODBUS_EXCEPTION_ACKNOWLEDGE = 0x05,
    MODBUS_EXCEPTION_SERVER_DEVICE_BUSY = 0x06,
    MODBUS_EXCEPTION_MEMORY_PARITY_ERROR = 0x08,
    MODBUS_EXCEPTION_GATEWAY_PATH_UNAVAILABLE = 0x0A,
    MODBUS_EXCEPTION_GATEWAY_TARGET_DEVICE_FAILED = 0x0B
} modbus_exception_code_t;

typedef struct {
    uint8_t device_id;
    uint8_t function;
    uint16_t address;
    uint16_t quantity;
    uint8_t *data;
    uint16_t data_len;
    uint16_t crc;
} modbus_request_t;

typedef struct {
    uint8_t device_id;
    uint8_t function;
    uint8_t byte_count;
    uint8_t data[MODBUS_MAX_DATA_LEN];
    uint16_t crc;
    uint8_t exception_code;
    bool is_exception;
} modbus_response_t;

typedef struct {
    uint8_t *data;
    uint16_t len;
    uint16_t crc;
} modbus_frame_t;

uint16_t modbus_calculate_crc(const uint8_t *data, uint16_t length);
bool modbus_validate_crc(const uint8_t *data, uint16_t length);

esp_err_t modbus_build_request(uint8_t device_id, uint8_t function, 
                              uint16_t address, uint16_t quantity,
                              const uint8_t *data, uint16_t data_len,
                              uint8_t *frame, uint16_t *frame_len);

esp_err_t modbus_parse_response(const uint8_t *frame, uint16_t frame_len,
                               modbus_response_t *response);

esp_err_t modbus_build_exception_response(uint8_t device_id, uint8_t function,
                                        uint8_t exception_code,
                                        uint8_t *frame, uint16_t *frame_len);

const char* modbus_exception_to_string(uint8_t exception_code);
const char* modbus_function_to_string(uint8_t function_code);

#endif