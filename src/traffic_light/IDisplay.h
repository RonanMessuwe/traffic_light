#pragma once

class IDisplay {
  public:
    virtual void begin() = 0;
    virtual void show(int value) = 0;
};
