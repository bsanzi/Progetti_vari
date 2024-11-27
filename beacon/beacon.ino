//ESP32 and try it out now!
 
#include <BLEDevice.h>            // sets up BLE device constructs<font></font>
#include <BLEUtils.h>             // various BLE utilities for processing BLE data<font></font>
#include <BLEScan.h>              // contains BLE scanning functions<font></font>
#include <BLEAdvertisedDevice.h>  // contains BLE device characteristic data<font></font>
#include <config.h>


int32_t buffer[4] = {0,0,0,0};

void setup(){
pinMode(RED, OUTPUT);
pinMode(YELLOW, OUTPUT);
pinMode(GREEN, OUTPUT);
BLEDevice::init("");
Serial.begin(baud_rate);
Serial.println("serial port ready");
}
 

void loop(){
static int idx;

BLEScan* scan = BLEDevice::getScan();
    scan-> setActiveScan(true);     // Modalità attiva: richiede più dati dai beacon
    scan-> setInterval(100);    // Intervallo tra scansioni (ms)
    scan-> setWindow(100);       // Finestra di scansione (ms)

BLEScanResults* results= scan->start(1,false);
delay(100);
scan->stop();

int RSSI=FREE_ZONE;
int rssi;
String name;
String address;


  for(int i=0; i <results->getCount();i++){
    BLEAdvertisedDevice device=results->getDevice(i);
    address= device.getAddress().toString();
      if (address == my_beacon_address ) {
      rssi = device.getRSSI();
      name= device.getName();
      idx++;
      }
  }

      if (idx<4){
      buffer[idx]=rssi;
      }
      else {
        idx=0;
        buffer[0]=rssi;
      }
      RSSI= ((buffer[0]+buffer[1]+buffer[2]+buffer[3])/4);
                 Serial.println(idx);

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