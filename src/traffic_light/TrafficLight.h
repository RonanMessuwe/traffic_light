#pragma once
#include "TrafficState.h"

class TrafficLight {
  private:
    uint8_t redPin;
    uint8_t orangePin;
    uint8_t greenPin;

  public:
    TrafficLight(uint8_t r, uint8_t o, uint8_t g);
    void begin();
    void apply(const Step& step);
};
