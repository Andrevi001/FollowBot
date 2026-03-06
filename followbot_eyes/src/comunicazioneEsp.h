#include <SerialTransfer.h>

struct __attribute__((packed)) Dati {
  int8_t header;
  int8_t pan_sum;
  int8_t tilt_sum;
  uint8_t distance;
} dati;