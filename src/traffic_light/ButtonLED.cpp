#include "ButtonLED.h"

ButtonLED::ButtonLED(uint8_t buttonPin, uint8_t ledPin, uint16_t debounceDelay)
    : Button(buttonPin, debounceDelay), ledController(ledPin) {
}

void ButtonLED::begin() {
    Button::begin();
    ledController.begin();
}

void ButtonLED::update() {
    Button::update();
    ledController.update();
}

void ButtonLED::setLED(bool state) {
    ledController.set(state);
}

void ButtonLED::flash(unsigned long duration) {
    ledController.flash(duration);
}

void ButtonLED::startBlink(unsigned long period) {
    ledController.startBlink(period);
}

void ButtonLED::stopBlink() {
    ledController.stopBlink();
}

bool ButtonLED::getLEDState() const {
    return ledController.getState();
}
