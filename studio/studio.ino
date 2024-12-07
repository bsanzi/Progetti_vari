#include <CapacitiveSensor.h>

CapacitiveSensor touch = CapacitiveSensor(10,11);

// AnalogOUTPUT
#define GREEN A0 
unsigned long push_buttom;
unsigned long prev_push;

void setup(){
  Serial.begin(9600);
  pinMode(GREEN,OUTPUT);

}
void loop(){
  long value=touch.capacitiveSensor(100);
  Serial.println(value);
    if (value>150){
     prev_push = push_buttom;
     digitalWrite(GREEN, HIGH);
     push_buttom = millis();
    }
      else{
      digitalWrite(GREEN, LOW);
      }
unsigned long interv = push_buttom-prev_push;
Serial.println(interv);
  delay(100);
}
