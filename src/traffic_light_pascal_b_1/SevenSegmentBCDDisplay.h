#pragma once
#include <Arduino.h>
#include "IDisplay.h"

// Seven Segment (Binary Coded Decimal) Display
class SevenSegmentBCDDisplay : public IDisplay {
  private:
    uint8_t bcdPins[4];   // A, B, C, D
    uint8_t latchPin;     // optionnel (LE)
    bool useLatch;

    void writeBCD(uint8_t value);

  public:
    SevenSegmentBCDDisplay(const uint8_t pins[4]);
    SevenSegmentBCDDisplay(const uint8_t pins[4], uint8_t lePin);

    void begin() override;
    void show(int value) override;
};
