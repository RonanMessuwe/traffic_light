#include "ButtonMultiLED.h"

ButtonMultiLED::ButtonMultiLED(uint8_t buttonPin, const uint8_t* pins, uint8_t count, uint16_t debounceDelay)
    : Button(buttonPin, debounceDelay),
      ledCount(count > MAX_LEDS ? MAX_LEDS : count),  // Clamp to MAX_LEDS
      isChasing(false),
      chaseStepDuration(0),
      lastChaseStep(0),
      currentChaseIndex(0) {

    // Store pins for initialization in begin()
    for (uint8_t i = 0; i < ledCount; i++) {
        ledPins[i] = pins[i];
    }
}

void ButtonMultiLED::begin() {
    Button::begin();

    // Initialize each LEDController with its pin
    for (uint8_t i = 0; i < ledCount; i++) {
        leds[i] = LEDController(ledPins[i]);
        leds[i].begin();
    }
}

void ButtonMultiLED::update() {
    Button::update();

    // Update chase effect first (if active)
    if (isChasing) {
        updateChase();
    }

    // Update all LEDs
    for (uint8_t i = 0; i < ledCount; i++) {
        leds[i].update();
    }
}

// Individual LED control

void ButtonMultiLED::setLED(uint8_t index, bool state) {
    if (index < ledCount) {
        // Stop chase if manual control is requested
        isChasing = false;
        leds[index].set(state);
    }
}

void ButtonMultiLED::setExclusiveLED(uint8_t index) {
    if (index < ledCount) {
        // Stop chase if active
        isChasing = false;

        // Turn off all LEDs, then turn on the selected one
        for (uint8_t i = 0; i < ledCount; i++) {
            leds[i].set(i == index);
        }
    }
}

void ButtonMultiLED::flash(uint8_t index, unsigned long duration) {
    if (index < ledCount) {
        // Stop chase if manual control is requested
        isChasing = false;
        leds[index].flash(duration);
    }
}

void ButtonMultiLED::startBlink(uint8_t index, unsigned long period) {
    if (index < ledCount) {
        // Stop chase if manual control is requested
        isChasing = false;
        leds[index].startBlink(period);
    }
}

void ButtonMultiLED::stopBlink(uint8_t index) {
    if (index < ledCount) {
        leds[index].stopBlink();
    }
}

bool ButtonMultiLED::getLEDState(uint8_t index) const {
    if (index < ledCount) {
        return leds[index].getState();
    }
    return false;
}

// Group control

void ButtonMultiLED::setAllLEDs(bool state) {
    // Stop chase
    isChasing = false;

    for (uint8_t i = 0; i < ledCount; i++) {
        leds[i].set(state);
    }
}

void ButtonMultiLED::flashAll(unsigned long duration) {
    // Stop chase
    isChasing = false;

    for (uint8_t i = 0; i < ledCount; i++) {
        leds[i].flash(duration);
    }
}

void ButtonMultiLED::stopAllBlink() {
    for (uint8_t i = 0; i < ledCount; i++) {
        leds[i].stopBlink();
    }
}

// Multi-LED patterns

void ButtonMultiLED::startChase(unsigned long stepDuration) {
    // Stop all individual effects
    stopAllBlink();
    setAllLEDs(false);

    // Start chase
    isChasing = true;
    chaseStepDuration = stepDuration;
    currentChaseIndex = 0;
    lastChaseStep = millis();

    // Light up first LED
    leds[0].set(true);
}

void ButtonMultiLED::stopChase() {
    isChasing = false;
    setAllLEDs(false);
}

void ButtonMultiLED::updateChase() {
    unsigned long now = millis();

    if (now - lastChaseStep >= chaseStepDuration) {
        // Turn off current LED
        leds[currentChaseIndex].set(false);

        // Move to next LED
        currentChaseIndex = (currentChaseIndex + 1) % ledCount;

        // Turn on next LED
        leds[currentChaseIndex].set(true);

        lastChaseStep = now;
    }
}

uint8_t ButtonMultiLED::getLEDCount() const {
    return ledCount;
}
