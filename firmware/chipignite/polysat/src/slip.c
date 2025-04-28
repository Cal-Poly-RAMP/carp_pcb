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
/* Used to decode incoming packets. Since there is only one data stream,
 * there is only one decoder. */
static SlipDecoder* decoder = NULL;

// SLIP-encode a buffer, calling send_byte() for each output byte

static void slip_encode_packet(const uint8_t* buf, uint16_t len, void (*send_byte)(uint8_t)) {}

/** @brief Encode and send one SLIP packet
 *
 * Serializes the packet (cmd, id, payload_len, payload), then SLIP-encodes
 * the serialized data into the output buffer, adding framing END bytes.
 *
 * @param data Pointer to the data to encode.
 * @param data_len Length of the data to encode.
 * @param cmd Command code.
 * @param send_byte Send a byte to the output stream.
 */
static void slip_send_packet(const uint8_t* data, uint16_t data_len, uint8_t cmd, void (*send_byte)(uint8_t)) {
  /* Flush buffer of any line noise */
  send_byte(SLIP_END);

  /* Populate header fields */
  SlipHeader hdr;
  hdr.length = (uint16_t)data_len;
  hdr.crc = crc16_ccitt_false(data, data_len);
  hdr.cmd = cmd;
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

// Compute CRC-CCITT-FALSE (poly 0x1021, init 0xFFFF, no final XOR)
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
 * @brief Initializes the SLIP decoder state.
 */
void slip_decoder_init() {
  decoder = (SlipDecoder*)malloc(sizeof(SlipDecoder));
  if (!decoder) { return; }
  decoder->buffer = (uint8_t*)malloc(sizeof(uint8_t) * SLIP_DECODER_BUFFER_SIZE);
  if (!decoder->buffer) {
    free(decoder);
    return;
  }
  decoder->buffer_size = SLIP_DECODER_BUFFER_SIZE;
  decoder->buffer_index = 0;
  decoder->escape_next = false;
}

/**
 * @brief Resets the SLIP decoder state.
 */
void slip_decoder_reset(SlipDecoder* decoder) {
  decoder->buffer_index = 0;
  decoder->escape_next = false;
}

/**
 * @brief Resizes the SLIP decoder buffer.
 */
void slip_decoder_resize(uint16_t new_size) {
  decoder->buffer = (uint8_t*)realloc(decoder->buffer, new_size);
  if (!decoder->buffer) { return; }
  decoder->buffer_size = new_size;
}

