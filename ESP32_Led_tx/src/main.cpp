#include <WiFi.h>
#include <esp_now.h>

#include <Led.h>
#include <config.h>


int PIN_2 = RED;
Led Led(PIN_2);


// macAddress tx {0xCC,0x7B,0x5C,0xFB,0xC9,0x88}
uint8_t RxAddress[] = {0xCC,0x7B,0x5C,0xF1,0xA7,0xEC};

char msg_out[8];
char state[4];

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t sendStatus) {
  if (sendStatus != ESP_NOW_SEND_SUCCESS) {
    Serial.println(">E\n");
  }
}


void handleLedStateChange(LedState state) {

  char pos[10];
    switch (state) {
      case LedState::ON:
        snprintf(pos, sizeof(pos), ">O\n");
        break;
      case LedState::OFF:
        snprintf(pos, sizeof(pos), ">F\n");
        break;
      case LedState::BLINK:
        snprintf(pos, sizeof(pos), ">B\n");
        break;
      default:
        return;
  }
  esp_err_t result = esp_now_send(RxAddress, (uint8_t *)pos, strlen(pos));
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
  esp_now_register_send_cb(OnDataSent);

  Led.begin();

}
 
void loop() {
  Led.run();
  Led.setOnStateCallback(handleLedStateChange);
}