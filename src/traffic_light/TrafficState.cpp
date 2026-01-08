#include "Arduino.h"
#include "TrafficState.h"
#include "Config.h"

// ===== Light state constants =====
const Step RED_LIGHT    = { true,  false, false, 0 };
const Step ORANGE_LIGHT = { false, true,  false, 0 };
const Step GREEN_LIGHT  = { false, false, true,  0 };
const Step RED_ORANGE   = { true,  true,  false, 0 };
const Step ALL_LIGHTS   = { true,  true,  true,  0 };
const Step LIGHTS_OFF   = { false, false, false, 0 };

// Helper to create a Step with custom duration
inline Step withDuration(const Step& base, unsigned long durationMs) {
  return { base.red, base.orange, base.green, durationMs };
}

// ===== MODE 1: FR / US =====
const Step MODE_FR_US[] = {
  withDuration(RED_LIGHT,    RED_DURATION_MS),
  withDuration(GREEN_LIGHT,  GREEN_DURATION_MS),
  withDuration(ORANGE_LIGHT, ORANGE_DURATION_MS)
};

// ===== MODE 2: UK =====
const Step MODE_UK[] = {
  withDuration(RED_LIGHT,    RED_DURATION_MS),
  withDuration(RED_ORANGE,   UK_RED_ORANGE_MS),
  withDuration(GREEN_LIGHT,  GREEN_DURATION_MS),
  withDuration(ORANGE_LIGHT, ORANGE_DURATION_MS)
};

// ===== MODE 3: BLINKING ORANGE =====
const Step MODE_ORANGE_BLINK[] = {
  withDuration(ORANGE_LIGHT, BLINK_DURATION_MS),
  withDuration(LIGHTS_OFF,   BLINK_DURATION_MS)
};

// ===== MODE 4: FIXED RED =====
const Step MODE_RED_FIXED[] = {
  RED_LIGHT
};

// ===== MODE 5: FIXED ORANGE =====
const Step MODE_ORANGE_FIXED[] = {
  ORANGE_LIGHT
};

// ===== MODE 6: FIXED GREEN =====
const Step MODE_GREEN_FIXED[] = {
  GREEN_LIGHT
};

// ===== MODE 7: ALL LIGHTS ON =====
const Step MODE_ALL_ON[] = {
  ALL_LIGHTS
};

// ===== MODE 8: CHASE SEQUENCE =====
const Step MODE_CHASE[] = {
  withDuration(RED_LIGHT,    CHASE_STEP_MS),
  withDuration(ORANGE_LIGHT, CHASE_STEP_MS),
  withDuration(GREEN_LIGHT,  CHASE_STEP_MS),
  withDuration(ORANGE_LIGHT, CHASE_STEP_MS)
};

const Mode MODES[] = {
  { MODE_FR_US,        3 },
  { MODE_UK,           4 },
  { MODE_ORANGE_BLINK, 2 },
  { MODE_RED_FIXED,    1 },
  { MODE_ORANGE_FIXED, 1 },
  { MODE_GREEN_FIXED,  1 },
  { MODE_ALL_ON,       1 },
  { MODE_CHASE,        4 }
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
