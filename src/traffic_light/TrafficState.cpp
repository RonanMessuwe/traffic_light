#include "Arduino.h"
#include "TrafficState.h"
#include "Config.h"

// ===== Light state constants (compile-time constants) =====
constexpr Step RED_LIGHT    = { true,  false, false, 0 };
constexpr Step ORANGE_LIGHT = { false, true,  false, 0 };
constexpr Step GREEN_LIGHT  = { false, false, true,  0 };
constexpr Step RED_ORANGE   = { true,  true,  false, 0 };
constexpr Step ALL_LIGHTS   = { true,  true,  true,  0 };
constexpr Step LIGHTS_OFF   = { false, false, false, 0 };

// Helper to create a Step with custom duration (compile-time)
constexpr Step withDuration(const Step& base, unsigned long durationMs) {
  return { base.red, base.orange, base.green, durationMs };
}

// ===== MODE DEFINITIONS (stored in FLASH) =====

// MODE 1: FR / US
const Step MODE_FR_US[] PROGMEM = {
  withDuration(RED_LIGHT,    RED_DURATION_MS),
  withDuration(GREEN_LIGHT,  GREEN_DURATION_MS),
  withDuration(ORANGE_LIGHT, ORANGE_DURATION_MS)
};

// MODE 2: UK
const Step MODE_UK[] PROGMEM = {
  withDuration(RED_LIGHT,    RED_DURATION_MS),
  withDuration(RED_ORANGE,   UK_RED_ORANGE_MS),
  withDuration(GREEN_LIGHT,  GREEN_DURATION_MS),
  withDuration(ORANGE_LIGHT, ORANGE_DURATION_MS)
};

// MODE 3: BLINKING ORANGE
const Step MODE_ORANGE_BLINK[] PROGMEM = {
  withDuration(ORANGE_LIGHT, BLINK_DURATION_MS),
  withDuration(LIGHTS_OFF,   BLINK_DURATION_MS)
};

// MODE 4: FIXED RED
const Step MODE_RED_FIXED[] PROGMEM = {
  RED_LIGHT
};

// MODE 5: FIXED ORANGE
const Step MODE_ORANGE_FIXED[] PROGMEM = {
  ORANGE_LIGHT
};

// MODE 6: FIXED GREEN
const Step MODE_GREEN_FIXED[] PROGMEM = {
  GREEN_LIGHT
};

// MODE 7: ALL LIGHTS ON
const Step MODE_ALL_ON[] PROGMEM = {
  ALL_LIGHTS
};

// MODE 8: CHASE SEQUENCE
const Step MODE_CHASE[] PROGMEM = {
  withDuration(RED_LIGHT,    CHASE_STEP_MS),
  withDuration(ORANGE_LIGHT, CHASE_STEP_MS),
  withDuration(GREEN_LIGHT,  CHASE_STEP_MS),
  withDuration(ORANGE_LIGHT, CHASE_STEP_MS)
};

const Mode MODES[] PROGMEM = {
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
  // Read Mode structure from PROGMEM
  Mode currentModeData;
  memcpy_P(&currentModeData, &MODES[currentMode], sizeof(Mode));

  // Read Step from PROGMEM
  Step step;
  memcpy_P(&step, &currentModeData.steps[currentStep], sizeof(Step));

  if (step.durationMs == 0) return;

  if (millis() - stepStart >= step.durationMs) {
    currentStep = (currentStep + 1) % currentModeData.stepCount;
    stepStart = millis();
  }
}

const Step& TrafficState::current() const {
  // Read Mode structure from PROGMEM
  Mode currentModeData;
  memcpy_P(&currentModeData, &MODES[currentMode], sizeof(Mode));

  // Read Step from PROGMEM and store in cache
  static Step stepCache;
  memcpy_P(&stepCache, &currentModeData.steps[currentStep], sizeof(Step));

  return stepCache;
}

uint8_t TrafficState::mode() const {
  return currentMode;
}
