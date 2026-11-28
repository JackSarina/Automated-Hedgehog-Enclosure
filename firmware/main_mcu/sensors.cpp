#include "Sensors.h"


int lastMicState = LOW;
unsigned long lastSoundTime = 0;
const unsigned long soundCooldown = 1000;

//Bring in variables from main.cpp
extern unsigned long lastWeightCheckTime;
extern const unsigned long weightCheckInterval;
extern unsigned long lastDetection;
extern const unsigned long debounceDelay;
extern int currentZone;
extern bool served;
extern float smoothed;
extern float threshold_grams;
extern float hall_thresh;
extern volatile unsigned long hall_last_interrupt_time;
extern volatile int hallCount;
extern const byte temp_pin;
extern const byte microphone_pinD;

static bool gateOpen = false;
static unsigned long gateOpenedAt = 0;
const unsigned long gateOpenDuration = 2000UL;

void handleSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("SERVO_MOVE:") && !gateOpen) {
      int targetDegrees = constrain(command.substring(11).toInt(), 0, 180);
      gateServo.write(targetDegrees);
      gateOpen = true;
      gateOpenedAt = millis();
    }
  }
}

void handleGate() {
  if (gateOpen && millis() - gateOpenedAt >= gateOpenDuration) {
    gateServo.write(0);
    gateOpen = false;
    Serial.println("ACK: FOOD_DISPENSED");  // ACK now means it actually finished
  }
}
void handleWeightTelemetry() {
  if (millis() - lastWeightCheckTime >= weightCheckInterval) {
    lastWeightCheckTime = millis();

if (scale.is_ready()) {
  float raw = scale.get_units(1);
  smoothed = 0.8 * smoothed + 0.2 * raw;
}

    // Broadcast the weight cleanly so the Pi's Python script can parse it
    Serial.print("WEIGHT:");
    Serial.println(smoothed, 1);
  }
}
void handleHallRPM() {
  static unsigned long lastHallCheck = 0;
  if (millis() - lastHallCheck >= 1000UL) {
    lastHallCheck = millis();

    // Safely grab the count and reset it
    noInterrupts();
    int rotations = hallCount;
    hallCount = 0;
    interrupts();

    // Print RPM to Serial for the Pi
    Serial.print("RPM: ");
    Serial.println(rotations * 60); // assuming 1 pulse per rotation
  }
}
void handleIrRowLogic() {
  static int lastIrState = HIGH;  // HIGH = beam clear, LOW = beam broken
  unsigned long currentMillis = millis();

  int irState = digitalRead(ir_1);

  // Falling edge = beam just got broken, with debounce
  if (irState == LOW && lastIrState == HIGH &&
      (currentMillis - lastDetection >= debounceDelay)) {

    if (currentZone == 1) {
      currentZone = 2;
      Serial.println("TRANSIT: 1_TO_2");
    } else {
      currentZone = 1;
      Serial.println("TRANSIT: 2_TO_1");
    }
    lastDetection = currentMillis;
  }

  lastIrState = irState;
}
void hallISR() {
  unsigned long current_time = millis();
  if (current_time - hall_last_interrupt_time > 10) { // Debounce for 10 ms
    hallCount++;
    hall_last_interrupt_time = current_time;
  }
}
void handleMicrophone(){
    
 unsigned long currentMillis = millis();
    
    int currentMicState = digitalRead(microphone_pinD);

    // Check for a rising edge trigger (sound detected) with a cooldown
    if (currentMicState == HIGH && lastMicState == LOW && (currentMillis - lastSoundTime >= soundCooldown)) {
        lastSoundTime = currentMillis;
        Serial.println("EVENT:SOUND_DETECTED");
    }

    lastMicState = currentMicState;
}