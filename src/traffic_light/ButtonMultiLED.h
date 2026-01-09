#ifndef BUTTON_MULTI_LED_H
#define BUTTON_MULTI_LED_H

#include "Button.h"
#include "LEDController.h"

/**
 * ButtonMultiLED - Button with multiple integrated LEDs
 *
 * Extends Button class by adding control for multiple LEDs.
 * Each LED can be controlled independently.
 * Supports special multi-LED patterns like chase effect.
 */
class ButtonMultiLED : public Button {
public:
    /**
     * Constructor
     * @param buttonPin GPIO pin for the button
     * @param ledPins Array of GPIO pins for the LEDs
     * @param ledCount Number of LEDs
     * @param debounceDelay Debounce delay in milliseconds (default: 50ms)
     */
    ButtonMultiLED(uint8_t buttonPin, const uint8_t* ledPins, uint8_t ledCount, uint16_t debounceDelay = 50);

    /**
     * Destructor - cleanup dynamically allocated memory
     */
    ~ButtonMultiLED();

    /**
     * Initialize button and all LEDs
     * Must be called in setup()
     */
    void begin();

    /**
     * Update button and all LED states
     * Must be called every loop() iteration
     */
    void update();

    // Individual LED control

    /**
     * Control a specific LED
     * @param index LED index (0 to ledCount-1)
     * @param state true = ON, false = OFF
     */
    void setLED(uint8_t index, bool state);

    /**
     * Turn on a specific LED and turn off all others (exclusive mode)
     * @param index LED index to turn on (0 to ledCount-1)
     */
    void setExclusiveLED(uint8_t index);

    /**
     * Trigger a flash on a specific LED
     * @param index LED index (0 to ledCount-1)
     * @param duration Flash duration in milliseconds (default: 250ms)
     */
    void flash(uint8_t index, unsigned long duration = 250);

    /**
     * Start blinking a specific LED
     * @param index LED index (0 to ledCount-1)
     * @param period Full period (ON + OFF) in milliseconds (default: 500ms)
     */
    void startBlink(uint8_t index, unsigned long period = 500);

    /**
     * Stop blinking a specific LED
     * @param index LED index (0 to ledCount-1)
     */
    void stopBlink(uint8_t index);

    /**
     * Get state of a specific LED
     * @param index LED index (0 to ledCount-1)
     * @return true if ON, false if OFF
     */
    bool getLEDState(uint8_t index) const;

    // Group control

    /**
     * Control all LEDs at once
     * @param state true = ON, false = OFF
     */
    void setAllLEDs(bool state);

    /**
     * Flash all LEDs simultaneously
     * @param duration Flash duration in milliseconds (default: 250ms)
     */
    void flashAll(unsigned long duration = 250);

    /**
     * Stop all blinking LEDs
     */
    void stopAllBlink();

    // Multi-LED patterns

    /**
     * Start chase effect (LEDs light up sequentially in a loop)
     * @param stepDuration Time each LED stays on in milliseconds (default: 200ms)
     */
    void startChase(unsigned long stepDuration = 200);

    /**
     * Stop chase effect
     */
    void stopChase();

    /**
     * Get number of LEDs
     * @return LED count
     */
    uint8_t getLEDCount() const;

private:
    LEDController** leds;
    uint8_t ledCount;

    // Chase state
    bool isChasing;
    unsigned long chaseStepDuration;
    unsigned long lastChaseStep;
    uint8_t currentChaseIndex;

    /**
     * Update chase effect
     */
    void updateChase();
};

#endif // BUTTON_MULTI_LED_H
