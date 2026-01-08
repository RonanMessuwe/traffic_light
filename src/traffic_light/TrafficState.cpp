#include "Arduino.h"
#include "TrafficState.h"

// ===== Constantes pour les états des lampes =====
const Step RED_LIGHT    = { true,  false, false, 0 };
const Step ORANGE_LIGHT = { false, true,  false, 0 };
const Step GREEN_LIGHT  = { false, false, true,  0 };
const Step RED_ORANGE   = { true,  true,  false, 0 };
const Step ALL_LIGHTS   = { true,  true,  true,  0 };
const Step LIGHTS_OFF   = { false, false, false, 0 };

// Helper pour créer un Step avec durée personnalisée
inline Step withDuration(const Step& base, unsigned long durationMs) {
  return { base.red, base.orange, base.green, durationMs };
}

// ===== MODE 1 : FR / US =====
const Step MODE_FR_US[] = {
  withDuration(RED_LIGHT,    120000),
  withDuration(GREEN_LIGHT,    6000),
  withDuration(ORANGE_LIGHT,   3000)
};

// ===== MODE 2 : UK =====
const Step MODE_UK[] = {
  withDuration(RED_LIGHT,    120000),
  withDuration(RED_ORANGE,     3000),
  withDuration(GREEN_LIGHT,    6000),
  withDuration(ORANGE_LIGHT,   3000)
};

// ===== MODE 3 : ORANGE CLIGNOTANT =====
const Step MODE_ORANGE_BLINK[] = {
  withDuration(ORANGE_LIGHT, 500),
  withDuration(LIGHTS_OFF,   500)
};

// ===== MODE 4 : ROUGE FIXE =====
const Step MODE_RED_FIXED[] = {
  RED_LIGHT
};

// ===== MODE 5 : ORANGE FIXE =====
const Step MODE_ORANGE_FIXED[] = {
  ORANGE_LIGHT
};

// ===== MODE 6 : VERT FIXE =====
const Step MODE_GREEN_FIXED[] = {
  GREEN_LIGHT
};

// ===== MODE 7 : TOUT ALLUMÉ =====
const Step MODE_ALL_ON[] = {
  ALL_LIGHTS
};

// ===== MODE 8 : CHENILLARD =====
const Step MODE_CHENILLARD[] = {
  withDuration(RED_LIGHT,    500),
  withDuration(ORANGE_LIGHT, 500),
  withDuration(GREEN_LIGHT,  500),
  withDuration(ORANGE_LIGHT, 500)
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
