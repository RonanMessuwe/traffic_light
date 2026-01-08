#pragma once

// ========================================
// CONFIGURATION MATÉRIELLE
// ========================================

#define USE_7_SEGMENT_DISPLAY 1

// Pins des lampes
#define RED_LAMP_PIN 2
#define ORANGE_LAMP_PIN 3
#define GREEN_LAMP_PIN 4

// Bouton de mode
#define MODE_BUTTON_PIN 8
#define DEBOUNCE_MS 50

// Afficheur 7 segments (CD4511)
#define CD4511_A_PIN 9
#define CD4511_B_PIN 10
#define CD4511_C_PIN 11
#define CD4511_D_PIN 12

// ========================================
// CONFIGURATION MÉTIER (Durées)
// ========================================
// Référence : IISR 6ème partie - Feux tricolores permanents

// Durées réglementaires
#define RED_DURATION_MS    120000  // 2 minutes
#define GREEN_DURATION_MS    6000  // 6 secondes (minimum réglementaire)
#define ORANGE_DURATION_MS   3000  // 3 secondes (obligatoire)
#define UK_RED_ORANGE_MS     3000  // Séquence UK : rouge + orange

// Durées animations
#define BLINK_DURATION_MS  500
#define CHASE_STEP_MS      500