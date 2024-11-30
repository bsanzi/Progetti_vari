#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

int baud_rate=9600;
const int sLux= A0; //PIN A0 AnalogInput

// Type of MODE
#define wifi 0
#define cablata 1
#define manuale 2

#ifndef MODE
#define MODE 0xFF
#endif

