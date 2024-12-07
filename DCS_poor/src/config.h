#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// constant firmware
#define baud_rate 9600
#define serial_delay 10 // 10 ms di delay post serial reading

#define temp_limit 23 // oltre 23 gradi si abilita un pin

// Analog Input
#define sLux A0 //PIN A0 

// Digital Output
#define GREEN A0 // PIN A0

// Type of MODE
#define wifi 0
#define cablata 1
#define manuale 2


#define MODE (wifi)


