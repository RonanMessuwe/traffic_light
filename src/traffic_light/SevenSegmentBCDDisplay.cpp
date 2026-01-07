#include "SevenSegmentBCDDisplay.h"

SevenSegmentBCDDisplay::SevenSegmentBCDDisplay(const uint8_t pins[4])
  : useLatch(false) {
  for (int i = 0; i < 4; i++) bcdPins[i] = pins[i];
}

SevenSegmentBCDDisplay::SevenSegmentBCDDisplay(
  const uint8_t pins[4],
  uint8_t lePin
) : latchPin(lePin), useLatch(true) {
  for (int i = 0; i < 4; i++) bcdPins[i] = pins[i];
}

void SevenSegmentBCDDisplay::begin() {
  for (int i = 0; i < 4; i++) {
    pinMode(bcdPins[i], OUTPUT);
  }
  if (useLatch) pinMode(latchPin, OUTPUT);
}

void SevenSegmentBCDDisplay::writeBCD(uint8_t value) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(bcdPins[i], (value >> i) & 0x01);
  }
}

void SevenSegmentBCDDisplay::show(int value) {
  if (value < 0 || value > 9) return;

  if (useLatch) digitalWrite(latchPin, LOW);
  writeBCD(value);
  if (useLatch) digitalWrite(latchPin, HIGH);
}