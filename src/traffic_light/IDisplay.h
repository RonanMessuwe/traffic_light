#pragma once

class IDisplay {
  public:
    virtual ~IDisplay() = default;  // Allows proper destruction of derived classes when deleting through base pointer
    virtual void begin() = 0;
    virtual void show(uint8_t value) = 0;
};
