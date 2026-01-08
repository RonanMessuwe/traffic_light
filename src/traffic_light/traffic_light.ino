#include "Config.h"
#include "TrafficLight.h"
#include "TrafficState.h"

#if USE_7_SEGMENT_DISPLAY
#include "SevenSegmentBCDDisplay.h"
#else
#include "NoDisplay.h"
#endif

// See the following document for timing specifications:
// FRENCH ROAD SIGNALING REGULATION (IISR)
// Part 6: Permanent traffic lights
// https://equipementsdelaroute.cerema.fr/IMG/pdf/iisr_6epartie_vc_20220613_cle2a3ec5.pdf

TrafficLight trafficLight(RED_LAMP_PIN, ORANGE_LAMP_PIN, GREEN_LAMP_PIN);
TrafficState trafficState;

#if USE_7_SEGMENT_DISPLAY
uint8_t bcdPins[4] = { CD4511_A_PIN, CD4511_B_PIN, CD4511_C_PIN, CD4511_D_PIN };  // A B C D
SevenSegmentBCDDisplay display(bcdPins);
#else
NoDisplay display;
#endif

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  buttonState = digitalRead(MODE_BUTTON_PIN);  // Read actual state in case button is already pressed
  lastButtonState = buttonState;               // Synchronize

  trafficLight.begin();
  display.begin();

  trafficState.setMode(0);  // Index of first mode
}

void loop() {
  handleButton();

  trafficState.update();
  trafficLight.apply(trafficState.current());

#if USE_7_SEGMENT_DISPLAY
  // Display current mode (1 to 8)
  display.show(trafficState.mode() + 1);
#endif
}

void handleButton() {
  int reading = digitalRead(MODE_BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // If at least DEBOUNCE_MS elapsed since last state change
  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        trafficState.nextMode();
      }
    }
  }

  lastButtonState = reading;
}
