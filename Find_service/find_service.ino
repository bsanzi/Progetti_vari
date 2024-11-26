// per conoscere tutti i servizi e caratteristiche di un beacon

#include <BLEDevice.h>            // sets up BLE device constructs<font></font>
#include <BLEUtils.h>             // various BLE utilities for processing BLE data<font></font>
#include <BLEScan.h>              // contains BLE scanning functions<font></font>
#include <BLEAdvertisedDevice.h>  // contains BLE device characteristic data<font></font>
//#include <config.h> // setup del sistema

const int REDD = 4; //PIN DGIO4
const int YELLOWW = 16; //PIN DGIO16
const int GREENN = 17;  //PIN DGIO17

const int FAULT_ZONEE = -65; //dbm
const int WARNING_ZONEE = -72;
const int DEFAULT_ZONEE = -150;

String my_beacon_address = "e5:31:d2:ed:02:8b";

BLEScan* pBLEScan;
BLEScanResults* pBLEresults;
BLEDevice* pDevice;
BLEAdvertisedDevice device;
BLEService* pService;
BLECharacteristic* pCharacteristic;

void setup() {
  // ... inizializzazione ...
 BLEDevice :: init();
 Serial.begin(115200);

}

void loop() {
  // Inizia la scansione
  pBLEScan = BLEDevice::getScan();
  pBLEscan-> setActiveScan(true);
  pBLEresults = pBLEScan->start(1); // Avvia la scansione per 0 secondi (continua finché non viene fermata)

  // ... codice per trovare e connettersi al dispositivo desiderato ...
 for (i=0; i<pBLEresults->getCount();i++){
  BLEAdvertisedDevice device=results->getDevice(i);
  address= device.getAddress().toString();
  if (address == my_beacon_address ) {
      // Ottieni il primo servizio del dispositivo
  pService = pDevice->services()[0];
  std::string value = pservice->value();
  Serial.print("Service: ");
  Serial.println(value);

    // Ottieni la prima caratteristica del servizio
  pCharacteristic = pService->characteristics()[0];
  std::string value = pCharacteristic->value();
  Serial.print("Characteristic: ");
  Serial.println(value);
 }
 else{
  Serial.println("beacon non trovato");
 }
}