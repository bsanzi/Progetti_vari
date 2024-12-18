#include <Led.h>
#include <config.h>


// Led(GREEN)= Led ledg;

int PIN_1 = GREEN;
int PIN_2 = RED;
Led Led1(PIN_1);
Led Led2(PIN_2);


void setup() {
  pinMode(GREEN,OUTPUT);
  pinMode(RED,OUTPUT);
  Serial.begin(baud_rate);
  Led1.begin();
  Led2.begin();


}
 
void loop() {
  LedState a=Led1.getState();
  LedState b=Led2.getState();
  delay(1000);
  if(a == b){
    Serial.println("same state");
    delay(1000);
  }
  Led1.msgEval();
}
