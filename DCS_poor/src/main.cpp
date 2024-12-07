
#include <main.h>

void setup(){
 Serial.begin(baud_rate);

 pinMode(GREEN,OUTPUT);

 bool init=sBarometer.begin(0X76);
  if (!init){
    Serial.println("sensore BME280 non inizializzato");
  }

}
float i=0; // per asse X del teleplot
void loop() {
 i +=0.1;

  // Plot a Temp
            double Temp = sBarometer.readTemperature();
            Serial.print(">temp:"); //  >var:123 cosi lo plotta
            Serial.println(Temp); 

  if (Serial.available()){
    char comand_1= Serial.read();
    delay(serial_delay);
    if (comand_1 == '>'){
    char comand_2 = Serial.read();
    //delay(100);
    switch(comand_2){
      case 'T':{
          Serial.print("Temperatura: ");
          double Temp = sBarometer.readTemperature();
          Serial.print(Temp);
          Serial.println(" *C");
        if (Temp>temp_limit){
          digitalWrite(GREEN,HIGH);
        }
        else {
          digitalWrite(GREEN,LOW);
        }
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
  }
  /*else{
    Serial.println("serial port wait comand >X");
    delay(5000);
  } */
}
