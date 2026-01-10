#pragma once
#include <stdint.h>

class Button {
  private:
    uint8_t pin;
    uint16_t debounceMs;

    uint8_t currentState;
    uint8_t lastReading;
    unsigned long lastDebounceTime;

    bool pressedFlag;  // Flag to detect a new press

  public:
    // Constructor
    Button(uint8_t buttonPin, uint16_t debounceDelay = 50);

    // Initialize the button (call in setup)
    void begin();

    // Update button state (call in loop)
    void update();

    // Check if button was pressed (consumes the event)
    bool wasPressed();

    // Get current state (non-destructive read)
    bool isPressed() const;
};
