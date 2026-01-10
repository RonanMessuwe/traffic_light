#include <Arduino.h>
#include "Button.h"

Button::Button(uint8_t buttonPin, uint16_t debounceDelay)
  : pin(buttonPin),
    debounceMs(debounceDelay),
    currentState(HIGH),
    lastReading(HIGH),
    lastDebounceTime(0),
    pressedFlag(false) {}

void Button::begin() {
  pinMode(pin, INPUT_PULLUP);

  // Read initial state to avoid false trigger
  currentState = digitalRead(pin);
  lastReading = currentState;
}

void Button::update() {
  uint8_t reading = digitalRead(pin);

  // Reset debounce timer on state change
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  // If stable for debounce duration
  if ((millis() - lastDebounceTime) > debounceMs) {
    // If state actually changed
    if (reading != currentState) {
      currentState = reading;

      // Detect falling edge (button pressed)
      if (currentState == LOW) {
        pressedFlag = true;
      }
    }
  }

  lastReading = reading;
}

bool Button::wasPressed() {
  if (pressedFlag) {
    pressedFlag = false;  // Consume the event
    return true;
  }
  return false;
}

bool Button::isPressed() const {
  return currentState == LOW;
}
