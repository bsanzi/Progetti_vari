
#include <Servo.h>
Servo myServo;
int posizione[4] = {30,60,90,120} ;

void setup(){
  Serial.begin(9600);
myServo.attach(8);

}

void loop(){
   myServo.write(0);
    for (int i=0; i<181; i++){
     myServo.write(i);
      Serial.println(i);
     delay(50);
    }
    for (int i=180; i>0; i--){
      myServo.write(i);
      delay(100);
    }

}

