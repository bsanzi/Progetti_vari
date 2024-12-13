#include "config.h"

ShutterState stato = ShutterState::UNKNOWN;
unsigned long lastRun=0; 
uint8_t percopen=0;
uint8_t last_percopen=0;

void setup(){
  Serial.begin(baud_rate);

}

void loop (){
  while(Serial.available()){
    char comand = Serial.read();
    delay(serial_delay);
    if (comand != '>')continue; // esce dall'iterazione
    comand = Serial.read();
    delay(serial_delay);
      switch (comand) {
        // caso comando per chiusura
        case'C':{
          if (stato==ShutterState::CLOSED || stato==ShutterState::CLOSING )break;
          if (stato==ShutterState:: STOPPED){
            percopen=last_percopen;
          }
          else{
            percopen = 100;
          }
          stato = ShutterState::CLOSING;
          printcomand(stato);
          break;
        }
         // caso comando per apertura
        case 'O':{
          if (stato==ShutterState::OPENED || stato==ShutterState::OPENING)break;
          if (stato==ShutterState:: STOPPED){
            percopen=last_percopen;
          }
          else{
            percopen = 0;
          }
          stato = ShutterState::OPENING;
          printcomand(stato);
          break;
        }
        case 'S':{
          stato = ShutterState::STOPPED;
          last_percopen= percopen;
          printcomand(stato);
          Serial.println(percopen);
          break;
        }
         // caso comando per richiesta informazioni
        case 'I':{
          printcomand(stato);
          Serial.println(percopen);
          break;
        }
      }

  }

    unsigned long t = millis();
  if ((t - lastRun) >= 100UL) {
    switch (stato) {
      case (ShutterState::CLOSING): {
        percopen--;
          if (percopen == 0) {
            stato = ShutterState::CLOSED;
            printcomand(stato);
          }
        Serial.print(">F");
        Serial.println(percopen);
        break;
          }
      case (ShutterState::OPENING):{
        percopen ++;
        if (percopen==100){
          stato =ShutterState::OPENED;
          printcomand(stato);
        }
        Serial.print(">F");
        Serial.println(percopen);
        break;
      }
    }
    lastRun=t;
  }
}