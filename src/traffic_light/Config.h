#pragma once

// ========================================
// HARDWARE CONFIGURATION
// ========================================

#define USE_7_SEGMENT_DISPLAY 1

// Lamp pins
#define RED_LAMP_PIN 2
#define ORANGE_LAMP_PIN 3
#define GREEN_LAMP_PIN 4

// Mode button
#define MODE_BUTTON_PIN 8
#define MODE_BUTTON_LED_PIN 13  // LED integrated in the mode button
#define DEBOUNCE_MS 50
#define MODE_BUTTON_FLASH_DURATION_MS 250  // Flash duration on mode change

// 7-segment display (CD4511)
#define CD4511_A_PIN 9
#define CD4511_B_PIN 10
#define CD4511_C_PIN 11
#define CD4511_D_PIN 12

// ========================================
// BUSINESS CONFIGURATION (Durations)
// ========================================
// Reference: IISR Part 6 - Permanent traffic lights

// Regulatory durations
#define RED_DURATION_MS    120000  // 2 minutes
#define GREEN_DURATION_MS    6000  // 6 seconds (regulatory minimum)
#define ORANGE_DURATION_MS   3000  // 3 seconds (mandatory)
#define UK_RED_ORANGE_MS     3000  // UK sequence: red + orange

// Animation durations
#define BLINK_DURATION_MS  500
#define CHASE_STEP_MS      500