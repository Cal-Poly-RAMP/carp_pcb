/**
 * @file slip.h
 * @brief Serial Line Internet Protocol (SLIP) implementation header
 *
 * Provides functions to encode and decode SLIP packets in loose accordance with RFC 1055.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Define maximum payload length for static allocation
#define SLIP_MAX_PAYLOAD_LEN 256

/* Begin typedef declarations */

/* Represents the SLIP special byte codes */
typedef enum slip_byte_t {
  /* Packet end code */
  SLIP_END = (uint8_t)0xC0,
  /* Escape indicator */
  SLIP_ESC = (uint8_t)0xDB,
  /* Transposed ESC code for END */
  SLIP_ESC_END = (uint8_t)0xDC,
  /* Transposed ESC code for ESC */
  SLIP_ESC_ESC = (uint8_t)0xDD,
} slip_byte_t;

/* Represents the supported SLIP command codes */
typedef enum slip_cmd_t {
  /* Data command */
  SLIP_CMD_DATA = 0x01,
  /* Acknowledgment command */
  SLIP_CMD_ACK = 0x02,
  /* Negative acknowledgment command */
  SLIP_CMD_NACK = 0x03,
  /* End of transmission command */
  SLIP_CMD_EOT = 0x04,
} slip_cmd_t;

/* Represents a SLIP packet header (stored in big-endian/network-order) */
typedef struct __attribute__((packed)) slip_header_t {
    /* The length of the payload in bytes */
    uint16_t length;
    /* The CRC-CCITT-FALSE of the payload */
    uint16_t crc;
    /* The command code */
    slip_cmd_t cmd;
    /* The packet ID */
    uint16_t id;
} slip_header_t;

typedef struct slip_packet_t {
    /* The header of the packet */
    slip_header_t header;
    /* The data payload of the packet */
    uint8_t payload[SLIP_MAX_PAYLOAD_LEN]; // Static buffer for payload
} slip_packet_t;

/* Begin function prototype declarations */

static void slip_send_packet(const uint8_t* data, uint16_t data_len, slip_cmd_t cmd, void (*send_byte)(uint8_t));
static uint16_t crc16_ccitt_false(const uint8_t* data, uint16_t len);

static void slip_receive_packet(uint8_t input_byte, slip_packet_t* decoded_packet, uint8_t (*read_byte)(void));

/* Begin inline function declarations */
