#pragma once

class IDisplay {
  public:
    virtual void begin() = 0;
    virtual void show(uint8_t value) = 0;
};
