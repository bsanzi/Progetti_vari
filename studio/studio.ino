
  int GREEN = A0;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
}

void loop(){
  // int dimensione =2;
  char comand = Serial.read();

  if (comand =='G'){
    digitalWrite(GREEN, HIGH);
    Serial.println("Led green ON");
  }
  else if (comand =='g'){
    digitalWrite(GREEN,LOW);
    Serial.println("Led green OFF");
  }
}