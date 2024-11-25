//ESP32 and try it out now!
 

#include <BLEDevice.h>            // sets up BLE device constructs<font></font>
#include <BLEUtils.h>             // various BLE utilities for processing BLE data<font></font>
#include <BLEScan.h>              // contains BLE scanning functions<font></font>
#include <BLEAdvertisedDevice.h>  // contains BLE device characteristic data<font></font>



const int RED = 15;
const int YELLOW = 2;
const int GREEN = 4;
 

const int FAULT_ZONE = -65;
const int WARNING_ZONE = -72;
 

const int DEFAULT_RSSI = -150;
 

String my_beacon_address = "e5:31:d2:ed:02:8b";
 

void setup(){
pinMode(RED, OUTPUT);
pinMode(YELLOW, OUTPUT);
pinMode(GREEN, OUTPUT);
BLEDevice::init("");
Serial.begin(115200);
 

}
 

void loop(){
BLEScan* scan = BLEDevice::getScan();
scan-> setActiveScan(true);
BLEScanResults* results= scan->start(1);
int RSSI=DEFAULT_RSSI;
String name;
String address;
 

for(int i=0; i <results->getCount();i++){
 
  BLEAdvertisedDevice device=results->getDevice(i);
  address= device.getAddress().toString();
  if (address == my_beacon_address ) {
  int32_t rssi = device.getRSSI();
  name= device.getName();
    RSSI=rssi;
  }
}
 if (RSSI>FAULT_ZONE){
  digitalWrite(RED, RSSI>FAULT_ZONE ? HIGH:LOW);
  digitalWrite(YELLOW,LOW);
  digitalWrite(GREEN,LOW);
  Serial.print("Fault con: ");
  Serial.print(RSSI);
  Serial.println(" dbm");
  Serial.println(name);
  Serial.println(address);
 }
    else if (RSSI<FAULT_ZONE && RSSI>WARNING_ZONE){
    digitalWrite(YELLOW, RSSI<FAULT_ZONE ? HIGH:LOW);
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,LOW);
    Serial.print("Warning con: ");
    Serial.print(RSSI);
    Serial.println(" dbm");
    Serial.println(name);
    Serial.println(address);
    }
  else {
  digitalWrite(GREEN,HIGH);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,LOW);
  Serial.print("Free zone con: ");
  Serial.print(RSSI);
  Serial.println(" dbm");
  Serial.println(name);
  Serial.println(address);
  }
 
}