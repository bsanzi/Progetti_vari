
#include <main.h>

void setup(){
 Serial.begin(baud_rate);
 pinMode(GREEN,OUTPUT);
  boolean init=sBarometer.begin(0X76);
  if (!init){
    Serial.println("sensore BME280 non inizializzato");
  }

}

void loop() {
  if (Serial.available()){
    char comand_1= Serial.read();
    delay(100);
    if (comand_1 == '>'){
    char comand_2 = Serial.read();
    delay(100);
    switch(comand_2){
      case 'T':{
          Serial.print("Temperatura: ");
          Serial.print(sBarometer.readTemperature());
          Serial.println(" *C");
          break;
      }
      case 'U': {
          Serial.print("Umidità: ");
          Serial.print(sBarometer.readHumidity());
          Serial.println(" %");
          break;
      }
      case 'P':{
          Serial.print("Pressione: ");
          Serial.print(sBarometer.readPressure() / 100.0F);
          Serial.println(" hPa");
          break;
      }
      case 'L':{
          int analogLux=analogRead(sLux);
          int Lux = map(analogLux, 0, 1023, 0, 100);
          if (MODE == wifi){
          Serial.println("MODE_wifi");
          Serial.print("Lux: ");
          Serial.println(Lux);
          Serial.print("Lux analogico: ");
          Serial.println(analogLux);
          }
          else {
             Serial.println("definire MODE");
          }
          break;
      }
     }
  }
  delay(2000);
}
}
