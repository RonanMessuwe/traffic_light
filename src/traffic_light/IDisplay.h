#pragma once

class IDisplay {
  public:
    virtual ~IDisplay() = default; // Permet de détruire la classe fille SevenSegmentBCDDisplay si on détruit la classe parente IDisplay.
    virtual void begin() = 0;
    virtual void show(uint8_t value) = 0;
};
