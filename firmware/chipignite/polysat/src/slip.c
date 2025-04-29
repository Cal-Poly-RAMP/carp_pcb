/**
 * @file slip.c
 * @brief Serial Line Internet Protocol (SLIP) implementation source
 *
 * Provides functions to encode and decode SLIP packets in loose accordance with RFC 1055.
 */

#include "slip.h"
#include <string.h>
#include <stdlib.h>

/* Each time a packet is sent/received, increment the packet count. */
static uint16_t packet_count = 0;

/** @brief Encode and send one SLIP packet
 *
 * Serializes the packet (cmd, id, payload_len, payload), then SLIP-encodes
 * the serialized data into the output buffer, adding framing END bytes.
 *
 * @param data Pointer to the data to encode.
 * @param data_len Length of the data to encode.
 * @param cmd Command code.
 * @param send_byte A function to send a byte to the output stream.
 */
static void slip_send_packet(const uint8_t* data, uint16_t data_len, slip_cmd_t cmd, void (*send_byte)(uint8_t)) {
  /* Flush buffer of any line noise */
  send_byte(SLIP_END);

  /* Populate header fields */
  slip_header_t hdr;
  hdr.length = (uint16_t)data_len;
  hdr.crc = crc16_ccitt_false(data, data_len);
  hdr.cmd = (slip_cmd_t)cmd;
  hdr.id = packet_count;

  /* Write header to buffer */
  uint8_t* buffer = (uint8_t*)&hdr;
  for (uint16_t i = 0; i < sizeof(hdr); i++) { send_byte(buffer[i]); }

  /* SLIP-encode the payload */
  for (uint16_t i = 0; i < data_len; i++) {
    uint8_t c = data[i];
    if (c == SLIP_END) {
      send_byte(SLIP_ESC);
      send_byte(SLIP_ESC_END);
    } else if (c == SLIP_ESC) {
      send_byte(SLIP_ESC);
      send_byte(SLIP_ESC_ESC);
    } else {
      send_byte(c);
    }
  }
  send_byte(SLIP_END);
}

/** @brief Compute a CRC-16/CCITT-FALSE checksum
 *
 * Cyclic Redundancy Check (CRC) is checksum algorithm used to detect errors in data transmissions.
 *
 * CRC-16/CCITT-FALSE is a Consultative Committee for International Telephony and Telegraphy (CCITT) 16-bit CRC-variant
 * with a polynomial of 0x1021, an initial value of 0xFFFF, and no final XOR value.
 *
 * @param data Pointer to the data to encode.
 * @param len Length of the data to encode.
 */
static uint16_t crc16_ccitt_false(const uint8_t* data, uint16_t len) {
  uint16_t crc = 0xFFFF;
  for (uint16_t i = 0; i < len; i++) {
    crc ^= (uint16_t)data[i] << 8;
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (crc & 0x8000) crc = (crc << 1) ^ 0x1021;
      else crc <<= 1;
    }
  }
  return crc;
}

/**
 * @brief Processes an incoming byte stream for SLIP decoding.
 *
 * @param input_byte The incoming byte to process.
 * @param read_byte A function to read a byte from the input stream.
 */
static void slip_receive_packet(uint8_t input_byte, slip_packet_t* decoded_packet, uint8_t (*read_byte)(void)) {
  if (!decoded_packet || !read_byte) { return; }

  /* Read header fields */
  decoded_packet->header.length = read_byte() | (read_byte() << 8);
  decoded_packet->header.crc = read_byte() | (read_byte() << 8);
  decoded_packet->header.cmd = read_byte();
  decoded_packet->header.id = read_byte() | (read_byte() << 8);

  /* Read payload */
  if (decoded_packet->payload != NULL) {
    free(decoded_packet->payload);
    decoded_packet->payload = NULL;
  }
  decoded_packet->payload = (uint8_t*)malloc((sizeof(uint8_t) * decoded_packet->header.length));
  if (decoded_packet->payload == NULL) {
    return;
  }
  for (uint16_t i = 0; i < decoded_packet->header.length; i++) {
    uint8_t c = read_byte();
    if (c == SLIP_END) {
      decoded_packet->payload[i] = SLIP_END;
    } else if (c == SLIP_ESC) {
      decoded_packet->payload[i] = SLIP_ESC;
    } else {
      decoded_packet->payload[i] = c;
    }
  }
}
