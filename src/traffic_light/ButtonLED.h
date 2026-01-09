#ifndef BUTTON_LED_H
#define BUTTON_LED_H

#include "Button.h"
#include "LEDController.h"

/**
 * ButtonLED - Button with integrated LED feedback
 *
 * Extends Button class by adding LED control capabilities.
 * The LED can be controlled independently from button state.
 */
class ButtonLED : public Button {
public:
    /**
     * Constructor
     * @param buttonPin GPIO pin for the button
     * @param ledPin GPIO pin for the LED
     * @param debounceDelay Debounce delay in milliseconds (default: 50ms)
     */
    ButtonLED(uint8_t buttonPin, uint8_t ledPin, uint16_t debounceDelay = 50);

    /**
     * Initialize button and LED
     * Must be called in setup()
     */
    void begin();

    /**
     * Update button and LED states
     * Must be called every loop() iteration
     */
    void update();

    /**
     * Direct LED control
     * @param state true = ON, false = OFF
     */
    void setLED(bool state);

    /**
     * Trigger a single flash
     * @param duration Flash duration in milliseconds (default: 250ms)
     */
    void flash(unsigned long duration = 250);

    /**
     * Start continuous blinking
     * @param period Full period (ON + OFF) in milliseconds (default: 500ms)
     */
    void startBlink(unsigned long period = 500);

    /**
     * Stop blinking
     */
    void stopBlink();

    /**
     * Get current LED state
     * @return true if ON, false if OFF
     */
    bool getLEDState() const;

private:
    LEDController ledController;
};

#endif // BUTTON_LED_H
