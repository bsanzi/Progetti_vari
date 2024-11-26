#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>

BLEClient* pClient;
BLERemoteService* pService;

void setup() {
    Serial.begin(115200);

    // Inizializza il BLE
    BLEDevice::init("");

    // Scansiona i dispositivi per trovare il beacon
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true);
    BLEScanResults *scanResults = pBLEScan->start(5); // Scansiona per 5 secondi

    // Cerca il dispositivo desiderato
    BLEAdvertisedDevice* targetDevice = nullptr;
    for (int i = 0; i < scanResults->getCount(); i++) {
        BLEAdvertisedDevice device = scanResults->getDevice(i);
        Serial.printf("Dispositivo trovato: %s\n", device.toString().c_str());

        // Confronta con l'indirizzo MAC o un identificatore specifico
        if (device.getAddress().toString() == "e5:31:d2:ed:02:8b") {
            targetDevice = new BLEAdvertisedDevice(device);
            break;
        }
    }

    if (!targetDevice) {
        Serial.println("Beacon non trovato.");
        return;
    }

    // Connetti al dispositivo
    pClient = BLEDevice::createClient();
    if (pClient->connect(targetDevice)) {
        Serial.println("Connesso al beacon!");

        // Scopri i servizi
        std::map<std::string, BLERemoteService*>* services = pClient->getServices();
        for (auto const& entry : *services) {
            Serial.printf("Servizio trovato: %s\n", entry.first.c_str());
        }

        // Accedi a un servizio specifico (sostituisci con il UUID corretto)
        pService = pClient->getService("UUID_SERVIZIO");
        if (pService) {
            Serial.println("Servizio trovato!");

            // Scopri le caratteristiche del servizio
            std::map<std::string, BLERemoteCharacteristic*>* characteristics = pService->getCharacteristics();
            for (auto const& entry : *characteristics) {
                Serial.printf("Caratteristica trovata: %s\n", entry.first.c_str());

                // Puoi leggere o scrivere sulla caratteristica
                BLERemoteCharacteristic* pCharacteristic = entry.second;
                if (pCharacteristic->canRead()) {
                String valueStr = pCharacteristic->readValue();
                std::string value = valueStr.c_str(); // Conversione a std::string
                Serial.println(value.c_str());       // Stampa il valore
                }
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
