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

/* Begin typedef declarations */

/* Represents the SLIP special byte codes */
typedef enum SlipByte {
  /* Packet end code */
  SLIP_END = (uint8_t)0xC0,
  /* Escape indicator */
  SLIP_ESC = (uint8_t)0xDB,
  /* Transposed ESC code for END */
  SLIP_ESC_END = (uint8_t)0xDC,
  /* Transposed ESC code for ESC */
  SLIP_ESC_ESC = (uint8_t)0xDD,
} SlipByte;

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
typedef struct __attribute__((packed)) SlipHeader {
    /* The length of the payload in bytes */
    uint16_t length;
    /* The CRC-CCITT-FALSE of the payload */
    uint16_t crc;
    /* The command code */
    uint8_t cmd;
    /* The packet ID */
    uint16_t id;
} SlipHeader;

typedef struct SlipPacket {
    /* The header of the packet */
    SlipHeader header;
    /* The data payload of the packet */
    uint8_t* payload;
} SlipPacket;

/* Begin function prototype declarations */

static void slip_send_packet(const uint8_t* data, uint16_t data_len, uint8_t cmd, void (*send_byte)(uint8_t));
static uint16_t crc16_ccitt_false(const uint8_t* data, uint16_t len);

static void slip_receive_packet(uint8_t input_byte, SlipPacket* decoded_packet, uint8_t (*read_byte)(void));

/* Begin inline function declarations */
