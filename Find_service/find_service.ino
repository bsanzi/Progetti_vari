#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>

int baud_rate = 115200;

BLEAdvertisedDevice* device;
BLEScan* scan;
BLEScanResults* results;
BLEClient* pClient;
BLERemoteService* pService;
<<<<<<< HEAD
BLERemoteCharacteristic* pCharacteristic;

String address_beacon = "e5:31:d2:ed:02:8b";
String UUID_SERVIZIO_1 =   "00001800-0000-1000-8000-00805f9b34fb"; //Generic Access Service
String Characteristic_name_11 ="00002a00-0000-1000-8000-00805f9b34fb"; //name
String UUID_SERVIZIO_2 ="00001801-0000-1000-8000-00805f9b34fb";  // Special Interest Group
String UUID_SERVIZIO_3 ="6e400001-b5a3-f393-e0a9-e50e24dcca9e"; // Customer service
String Characteristic_31 ="6e400002-b5a3-f393-e0a9-e50e24dcca9e";
String Characteristic_32 ="6e400003-b5a3-f393-e0a9-e50e24dcca9e";
=======
String address_beacon = "e5:31:d2:ed:02:8b";
>>>>>>> ee3a83d13b6e4b7e58b0fdae6a0d2eb08d1ff88f

void setup() {
    Serial.begin(baud_rate);

    // Inizializza il BLE
    BLEDevice::init("");

    // Scansiona i dispositivi per trovare il beacon
<<<<<<< HEAD
    scan = BLEDevice::getScan();
    scan->setActiveScan(true);
    results = scan->start(1); // Scansiona per 5 secondi

    // Cerca il dispositivo desiderato
    device = nullptr;
    for (int i = 0; i < results->getCount(); i++) {
        BLEAdvertisedDevice newdevice = results->getDevice(i);
        String name = newdevice.toString();
        Serial.print("Dispositivo trovato: ");
        Serial.println(name);

        // Confronta con l'indirizzo MAC o un identificatore specifico
        if (newdevice.getAddress().toString() == address_beacon) {
            device = new BLEAdvertisedDevice(newdevice);
            //String battery_level = device->getServiceData();
            //Serial.println(battery_level);
=======
    BLEScan* scan = BLEDevice::getScan();
    scan->setActiveScan(true);
    BLEScanResults *results = scan->start(1); // Scansiona per 5 secondi

    // Cerca il dispositivo desiderato
    BLEAdvertisedDevice* targetDevice = nullptr;
    for (int i = 0; i < results->getCount(); i++) {
        BLEAdvertisedDevice device = results->getDevice(i);
        Serial.printf("Dispositivo trovato: %s\n", device.toString().c_str());

        // Confronta con l'indirizzo MAC o un identificatore specifico
        if (device.getAddress().toString() == address_beacon) {
            targetDevice = new BLEAdvertisedDevice(device);
>>>>>>> ee3a83d13b6e4b7e58b0fdae6a0d2eb08d1ff88f
            break;
        }
    }

    if (!device) {
        Serial.println("Beacon non trovato.");
        return;
    }

    // Connetti al dispositivo
    pClient = BLEDevice::createClient();
    if (pClient->connect(device)) {
        Serial.println("Connesso al beacon!");

        // Scopri i servizi
        std::map<std::string, BLERemoteService*>* services = pClient->getServices();
        for (auto const& entry : *services) {
            Serial.printf("Servizio trovato: %s\n", entry.first.c_str());
        }

        // Accedi a un servizio specifico (sostituisci con il UUID corretto)
        pService = pClient->getService("00002a04-0000-1000-8000-00805f9b34fb");
        if (pService) {
            Serial.println("Servizio UUID_SERVIZIO_1 trovato!");

            // Scopri le caratteristiche del servizio
            std::map<std::string, BLERemoteCharacteristic*>* characteristics = pService->getCharacteristics();
            //BLERemoteCharacteristic* characteristics = pService->getCharacteristics();
            for (auto const& entry : *characteristics) {
                Serial.printf("Caratteristica trovata: %s\n", entry.first.c_str());

                // Puoi leggere o scrivere sulla caratteristica
                pCharacteristic = pService->getCharacteristic("00002a00-0000-1000-8000-00805f9b34fb");
                //if (pCharacteristic->canRead()) {
                String valueStr = pCharacteristic->readValue();
                std::string value = valueStr.c_str(); // Conversione a std::string
                Serial.println("Characteristic_11 è: ");
                Serial.println(value.c_str());       // Stampa il valore
                //}
            }
        } else {
            Serial.println("Servizio non trovato.");
        }
    } else {
        Serial.println("Impossibile connettersi al beacon.");
    }
}

void loop() {
    // Nulla qui
}
