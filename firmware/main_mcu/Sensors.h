#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Servo.h>
#include <HX711.h>

// --- Global Hardware Objects ---
extern HX711 scale;
extern Servo gateServo;

// --- Global Pins & Configuration Variables ---
extern const byte ir_1;
extern const byte microphone_pinD;
extern const unsigned long debounceDelay;
extern const unsigned long weightCheckInterval;
extern long unsigned lastWeightCheckTime;

// --- Function Prototypes ---
void hallISR();
void handleGate();
void handleSerialCommands();
void handleIrRowLogic();
void handleHallRPM();
void handleWeightTelemetry();
void handleMicrophone();

#endif