#include "Config.h"
#include "TrafficLight.h"
#include "TrafficState.h"

#if USE_7_SEGMENT_DISPLAY
#include "SevenSegmentBCDDisplay.h"
#else
#include "NoDisplay.h"
#endif

// Voir le document suivant pour les temps :
// INSTRUCTION INTERMINISTÉRIELLE SUR LA SIGNALISATION ROUTIÈRE
// 6ème PARTIE : Feux de circulation permanents
// https://equipementsdelaroute.cerema.fr/IMG/pdf/iisr_6epartie_vc_20220613_cle2a3ec5.pdf

TrafficLight trafficLight(RED_LAMP_PIN, ORANGE_LAMP_PIN, GREEN_LAMP_PIN);
TrafficState trafficState;

#if USE_7_SEGMENT_DISPLAY
uint8_t bcdPins[4] = { CD4511_A_PIN, CD4511_B_PIN, CD4511_C_PIN, CD4511_D_PIN };  // A B C D
SevenSegmentBCDDisplay display(bcdPins);
#else
NoDisplay display;
#endif

int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);

  trafficLight.begin();
  display.begin();

  trafficState.setMode(0);  // Mode 1 au démarrage
}

void loop() {
  handleButton();

  trafficState.update();
  trafficLight.apply(trafficState.current());

#if USE_7_SEGMENT_DISPLAY
  // Affiche le mode courant (1 à 8)
  display.show(trafficState.mode() + 1);
#endif
}

void handleButton() {
  int reading = digitalRead(MODE_BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // S'il s'est écoulé au moins DEBOUNCE_MS depuis le dernier changement d'état
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
