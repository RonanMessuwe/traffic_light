#include "LEDController.h"

LEDController::LEDController(uint8_t pin)
    : pin(pin),
      isFlashing(false),
      flashStartTime(0),
      flashDuration(0),
      isBlinking(false),
      blinkPeriod(0),
      lastBlinkToggle(0),
      blinkState(false),
      currentState(false) {
}

void LEDController::begin() {
    pinMode(pin, OUTPUT);
    writePin(false);
}

void LEDController::update() {
    // Handle flash timing
    if (isFlashing) {
        if (millis() - flashStartTime >= flashDuration) {
            isFlashing = false;
            writePin(false);
        }
    }

    // Handle blink timing
    if (isBlinking && !isFlashing) {
        unsigned long now = millis();
        if (now - lastBlinkToggle >= blinkPeriod / 2) {
            blinkState = !blinkState;
            writePin(blinkState);
            lastBlinkToggle = now;
        }
    }
}

void LEDController::set(bool state) {
    // Stop any ongoing effects
    isFlashing = false;
    isBlinking = false;
    writePin(state);
}

void LEDController::flash(unsigned long duration) {
    // Stop blinking if active
    isBlinking = false;

    // Start flash
    isFlashing = true;
    flashStartTime = millis();
    flashDuration = duration;
    writePin(true);
}

void LEDController::startBlink(unsigned long period) {
    // Stop flash if active
    isFlashing = false;

    // Start blinking
    isBlinking = true;
    blinkPeriod = period;
    blinkState = true;
    lastBlinkToggle = millis();
    writePin(true);
}

void LEDController::stopBlink() {
    isBlinking = false;
    writePin(false);
}

bool LEDController::getState() const {
    return currentState;
}

void LEDController::writePin(bool state) {
    currentState = state;
    digitalWrite(pin, state ? HIGH : LOW);
}
