#include "Arduino.h"
#include "TrafficState.h"

// ===== MODE 1 : FR / US =====
const Step MODE_FR_US[] = {
  { true,  false, false, 120000 },
  { false, false, true,    6000 },
  { false, true,  false,   3000 }
};

// ===== MODE 2 : UK =====
const Step MODE_UK[] = {
  { true,  false, false, 120000 },
  { true,  true,  false,   3000 },
  { false, false, true,    6000 },
  { false, true,  false,   3000 }
};

// ===== MODE 3 : ORANGE CLIGNOTANT =====
const Step MODE_ORANGE_BLINK[] = {
  { false, true,  false, 500 },
  { false, false, false, 500 }
};

// ===== MODE 4 : ROUGE FIXE =====
const Step MODE_RED_FIXED[] = {
  { true, false, false, 0 }
};

// ===== MODE 5 : ORANGE FIXE =====
const Step MODE_ORANGE_FIXED[] = {
  { false, true, false, 0 }
};

// ===== MODE 6 : VERT FIXE =====
const Step MODE_GREEN_FIXED[] = {
  { false, false, true, 0 }
};

// ===== MODE 7 : TOUT ALLUMÉ =====
const Step MODE_ALL_ON[] = {
  { true, true, true, 0 }
};

// ===== MODE 8 : CHENILLARD =====
const Step MODE_CHENILLARD[] = {
  { true,  false, false, 500 },
  { false, true,  false, 500 },
  { false, false, true,  500 },
  { false, true,  false, 500 }
};

const Mode MODES[] = {
  { MODE_FR_US,        3 },
  { MODE_UK,           4 },
  { MODE_ORANGE_BLINK, 2 },
  { MODE_RED_FIXED,    1 },
  { MODE_ORANGE_FIXED, 1 },
  { MODE_GREEN_FIXED,  1 },
  { MODE_ALL_ON,       1 },
  { MODE_CHENILLARD,   4 }
};

#define MODE_COUNT 8

TrafficState::TrafficState() {
  currentMode = 0;
  currentStep = 0;
  stepStart = millis();
}

void TrafficState::setMode(uint8_t mode) {
  if (mode >= MODE_COUNT) return;
  currentMode = mode;
  currentStep = 0;
  stepStart = millis();
}

void TrafficState::nextMode() {
  currentMode = (currentMode + 1) % MODE_COUNT;
  currentStep = 0;
  stepStart = millis();
}

void TrafficState::update() {
  const Step& step = MODES[currentMode].steps[currentStep];

  if (step.durationMs == 0) return;

  if (millis() - stepStart >= step.durationMs) {
    currentStep =
      (currentStep + 1) % MODES[currentMode].stepCount;
    stepStart = millis();
  }
}

const Step& TrafficState::current() const {
  return MODES[currentMode].steps[currentStep];
}

uint8_t TrafficState::mode() const {
  return currentMode;
}
