
int GREEN = A0;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
}

void loop(){

  if (Serial.available()){
    //delay (1000);
    char comand_1 = Serial.read();
    delay(100);

    if (comand_1!='>'){
      Serial.println("il comando ha format >X ");
    }
    else {
        char comand_2 = Serial.read();
        switch (comand_2) {
          case 'G':{
          digitalWrite(GREEN, HIGH);
          Serial.println ("Led green acceso");
          break;
           }
          case 'g': {
          digitalWrite(GREEN, LOW);
          Serial.println ("Led green spento");
          break;
          }
        }
    }
  }

}
