#include <Arduino.h>
#include <Servo.h>
#include <HX711.h>
#include "Sensors.h"

//Pin Definitions
const byte hall_pin = 2; // pin for hall sensor (has to be 2!!)
const byte servo_pin = 5; // pin for servo motor
const byte load_cell_dout = 3; // pin for HX711 data output
const byte load_cell_sck = 4; // pin for HX711 clock
const byte microphone_pinD = 13;
const byte microphone_pinA = A0;
const byte ir_1 = 10;

//Hardware Objects
HX711 scale;
Servo gateServo;

//Variables & timing
float calibration_factor = 1962; // Adjust this value to calibrate the load cell
float threshold_grams = 50.0; // Threshold for load cell in grams
float hall_thresh = 100.0; // threshold for hall sensor


unsigned long lastWeightCheckTime = 0UL;
const unsigned long weightCheckInterval = 1000UL; // Check weight every 1 second

unsigned long lastDetection = 0UL;
const unsigned long debounceDelay = 1000UL;


int currentZone = 1;
bool served = false;
float smoothed = 0.0;

// Intterupt Service Routine for Hall Sensor
volatile unsigned long hall_last_interrupt_time = 0;
volatile int hallCount = 0;


void setup() {
  Serial.begin(115200);

  // Pin Modes
  pinMode(ir_1, INPUT_PULLUP);
  pinMode(hall_pin, INPUT_PULLUP);
  pinMode(microphone_pinD, INPUT);
  pinMode(microphone_pinA, INPUT);
  pinMode(load_cell_dout, INPUT);
  pinMode(load_cell_sck, OUTPUT);
  pinMode(servo_pin, OUTPUT);

  //Attach Interrupt for Hall Sensor
  attachInterrupt(digitalPinToInterrupt(hall_pin), hallISR, FALLING);

  // Initialize Load Cell
  scale.begin(load_cell_dout, load_cell_sck);
  scale.set_scale(calibration_factor);
  scale.tare(); // Reset the scale to 0

  // Initialize Servo
  gateServo.attach(servo_pin);
  gateServo.write(0); // Start with the gate closed
  delay(500); // Allow time for the servo to reach the position

  lastWeightCheckTime = millis();

}

void loop() {
  handleSerialCommands();
  handleGate();
  handleIrRowLogic();
  handleHallRPM();
  handleWeightTelemetry();
  handleMicrophone();
  
}
