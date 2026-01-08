#pragma once
#include "stdint.h"

struct Step {
  bool red;
  bool orange;
  bool green;
  unsigned long durationMs;  // 0 = infinite
};

struct Mode {
  const Step* steps;
  uint8_t stepCount;
};

class TrafficState {
  private:
    uint8_t currentMode;
    uint8_t currentStep;
    unsigned long stepStart;

  public:
    TrafficState();
    void setMode(uint8_t mode);
    void nextMode();
    void update();
    const Step& current() const;
    uint8_t mode() const;
};
