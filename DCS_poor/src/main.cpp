#include <config.h>
Adafruit_BME280 sBarometer;

void setup(){
 Serial.begin(baud_rate);
 boolean init=sBarometer.begin(0X76);

 if (!init){
  Serial.println("sensore non inizializzato");
 }

}

void loop() {
  Serial.print("Temperatura: ");
  Serial.print(sBarometer.readTemperature());
  Serial.println(" *C");

  Serial.print("Umidità: ");
  Serial.print(sBarometer.readHumidity());
  Serial.println(" %");

  Serial.print("Pressione: ");
  Serial.print(sBarometer.readPressure() / 100.0F);
  Serial.println(" hPa");

  int analogLux=analogRead(sLux);
  int Lux = map(analogLux, 0, 1023, 0, 100);
  Serial.print("Lux analogico: ");
  Serial.println(Lux);

  delay(2000);
}
