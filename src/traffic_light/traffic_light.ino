#include "Config.h"
#include "TrafficLight.h"
#include "TrafficState.h"
#include "Button.h"

#if USE_7_SEGMENT_DISPLAY
#include "SevenSegmentBCDDisplay.h"
#else
#include "NoDisplay.h"
#endif

TrafficLight trafficLight(RED_LAMP_PIN, ORANGE_LAMP_PIN, GREEN_LAMP_PIN);
TrafficState trafficState;
Button modeButton(MODE_BUTTON_PIN, DEBOUNCE_MS);

#if USE_7_SEGMENT_DISPLAY
uint8_t bcdPins[4] = { CD4511_A_PIN, CD4511_B_PIN, CD4511_C_PIN, CD4511_D_PIN };  // A B C D
SevenSegmentBCDDisplay display(bcdPins);
#else
NoDisplay display;
#endif

void setup() {
  modeButton.begin();
  trafficLight.begin();
  display.begin();

  trafficState.setMode(0);  // Index of first mode
}

void loop() {
  modeButton.update();

  if (modeButton.wasPressed()) {
    trafficState.nextMode();
  }

  trafficState.update();
  trafficLight.apply(trafficState.current());

#if USE_7_SEGMENT_DISPLAY
  // Display current mode (1 to 8)
  display.show(trafficState.mode() + 1);
#endif
}
