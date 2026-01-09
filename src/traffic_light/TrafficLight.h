#pragma once
#include "TrafficState.h"

class TrafficLight {
  private:
    int redPin;
    int orangePin;
    int greenPin;

  public:
    TrafficLight(int r, int o, int g);
    void begin();
    void apply(const Step& step);
    void allOff();
};
