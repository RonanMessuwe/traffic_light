#pragma once

#include <stdint.h>

// ========================================
// HARDWARE CONFIGURATION
// ========================================

// Compilation conditional flag (must be #define for preprocessor #if)
#define USE_7_SEGMENT_DISPLAY 1

// Lamp pins
constexpr uint8_t RED_LAMP_PIN = 2;
constexpr uint8_t ORANGE_LAMP_PIN = 3;
constexpr uint8_t GREEN_LAMP_PIN = 4;

// Mode button
constexpr uint8_t MODE_BUTTON_PIN = 8;
constexpr uint8_t MODE_BUTTON_LED_PIN = 13;  // LED integrated in the mode button
constexpr uint16_t DEBOUNCE_MS = 50;
constexpr uint16_t MODE_BUTTON_FLASH_DURATION_MS = 250;  // Flash duration on mode change

// 7-segment display (CD4511)
constexpr uint8_t CD4511_A_PIN = 9;
constexpr uint8_t CD4511_B_PIN = 10;
constexpr uint8_t CD4511_C_PIN = 11;
constexpr uint8_t CD4511_D_PIN = 12;

// ========================================
// BUSINESS CONFIGURATION (Durations)
// ========================================
// Reference: IISR Part 6 - Permanent traffic lights

// Regulatory durations
constexpr unsigned long RED_DURATION_MS = 120000;  // 2 minutes
constexpr unsigned long GREEN_DURATION_MS = 6000;  // 6 seconds (regulatory minimum)
constexpr unsigned long ORANGE_DURATION_MS = 3000;  // 3 seconds (mandatory)
constexpr unsigned long UK_RED_ORANGE_MS = 3000;  // UK sequence: red + orange

// Animation durations
constexpr unsigned long BLINK_DURATION_MS = 500;
constexpr unsigned long CHASE_STEP_MS = 500;