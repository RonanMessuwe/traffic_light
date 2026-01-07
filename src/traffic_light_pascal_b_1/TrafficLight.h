#pragma once
#include "TrafficState.h"

enum class LightColor {
  RED,
  ORANGE,
  GREEN
};

class TrafficLight {
  private:
    int redPin;
    int orangePin;
    int greenPin;

  public:
    TrafficLight(int r, int o, int g);
    void begin();
    void set(LightColor color);
    void apply(const Step& step);
};
