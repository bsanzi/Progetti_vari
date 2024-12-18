#include <Led.h>

Led::Led(int PIN) {
    _pin = PIN;
}


void Led::begin(){
  _state = LedState::OFF;
} 
void Led::accendi(){
  digitalWrite(_pin,HIGH);
}
void Led::spegni(){
   digitalWrite(_pin,LOW);
}
LedState Led::getState(){
  return _state;
}
bool Led::CheckState(LedState state){
  _state = getState();
  if (_state == state){
    return true;
  }
  else {
    return false;
  }
}
void Led::msgEval(){
 if (Serial.available()){
  if (Serial.read()!='>') {}
  else{
  delay(10);
  char comand = Serial.read();
    switch (comand){
     case 'A':{
       accendi();
      _state=LedState::ON;
      }
    case 'S':{
      spegni();
      _state=LedState::OFF;
      }
    case 'B':{
      accendi();
      delay(500);
      spegni();
      delay(500);      
      _state=LedState::BLINK;
    }

    }
  }
 }


}