#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

/**
 * LEDController - Manages a single LED with flash and blink capabilities
 *
 * This class encapsulates all LED control logic:
 * - Direct on/off control
 * - Single flash (configurable duration)
 * - Continuous blinking (configurable period)
 */
class LEDController {
public:
    /**
     * Default constructor (for array initialization)
     */
    LEDController();

    /**
     * Constructor
     * @param pin GPIO pin for the LED
     */
    LEDController(uint8_t pin);

    /**
     * Initialize the pin as OUTPUT
     * Must be called in setup()
     */
    void begin();

    /**
     * Update LED state (handles timing)
     * Must be called every loop() iteration
     */
    void update();

    /**
     * Direct LED control
     * @param state true = ON, false = OFF
     */
    void set(bool state);

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
    bool getState() const;

private:
    uint8_t pin;

    // Flash state
    bool isFlashing;
    unsigned long flashStartTime;
    unsigned long flashDuration;

    // Blink state
    bool isBlinking;
    unsigned long blinkPeriod;
    unsigned long lastBlinkToggle;
    bool blinkState;

    // Current LED state
    bool currentState;

    /**
     * Write state to physical pin
     * @param state State to write
     */
    void writePin(bool state);
};

#endif // LED_CONTROLLER_H
