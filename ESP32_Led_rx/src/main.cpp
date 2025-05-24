#include <WiFi.h>
#include <esp_now.h>

#include <Led.h>
#include <config.h>

int PIN_1 = GREEN;
Led Led(PIN_1);


// macAddress tx {0xCC,0x7B,0x5C,0xFB,0xC9,0x88}
uint8_t RxAddress[] = {0xCC,0x7B,0x5C,0xF1,0xA7,0xEC};


char msg_in[8];
char state[4];

esp_now_peer_info_t peerInfo;


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (len >= sizeof(msg_in)) {
    memcpy(&msg_in, incomingData, sizeof(msg_in));
    Serial.print("Data received: ");
    Serial.println(msg_in);
    Led.msgEval();
  }
}


void setup() {

  Serial.begin(baud_rate);

  WiFi.mode(WIFI_STA);


  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register peer
  memcpy(peerInfo.peer_addr, RxAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  // Callback Functions
  esp_now_register_recv_cb(OnDataRecv);

  Led.begin();

}
 
void loop() {
  Led.run();
}