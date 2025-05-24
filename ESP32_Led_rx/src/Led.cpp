#include <Led.h>


// costruttore oggetto Led
Led::Led(int PIN) {
    _pin = PIN;
    _timeSetup = 10000;
}

void Led::begin(){
  _state = LedState::UNKNOWN;
  pinMode(_pin,OUTPUT);
} 

void Led::run() {
  if (_state != _lastState) {
    if ((_lastState == LedState::ON) || (_lastState == LedState::OFF) || (_lastState == LedState::UNKNOWN)) {
      _lastRun = millis(); 
    }
    _lastState = _state;
  }
  switch (_state) {
    case LedState::UNKNOWN:
      break;
    case LedState::ON:
      accendi();
      break;
    case LedState::OFF:
      spegni();
      break;
    case LedState::BLINK:
      blink();
      break;
 /**  case LedState::STOPPED:
      stop();
      break;  */


    default:
      return;
  }
}

void Led::accendi(){
    if ((_state != LedState::ON)) {
    unsigned long t = millis();
    long tDiff = static_cast<long>(t - _lastRun);
    long tsum = tsum + tDiff;
    
    if ( tsum > _timeSetup) {
      _state = LedState::ON;
      notifyStateChanged();
      digitalWrite(_pin, HIGH);
    } else {
      digitalWrite(_pin, HIGH);
      delay(200);
      digitalWrite(_pin, LOW);
      delay(200);

    }
    _lastRun = t;

  }
}
void Led::blink(){
    if ((_state != LedState::BLINK)) {
    unsigned long t = millis();
    long tDiff = static_cast<long>(t - _lastRun);
    long tsum = tsum + tDiff;
    
    if ( tsum > _timeSetup) {
      _state = LedState::BLINK;
      notifyStateChanged();
      digitalWrite(_pin, HIGH);
      delay(1000);
      digitalWrite(_pin, LOW);
      delay(1000);
    } else {
      digitalWrite(_pin, HIGH);
      delay(200);
      digitalWrite(_pin, LOW);
      delay(200);
    }
    _lastRun = t;
  }
}


void Led::spegni(){
       _state = LedState::OFF;
      notifyStateChanged();
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
  //    _state=LedState::ON;
      }
    case 'S':{
      spegni();
  //    _state=LedState::OFF;
      }
    case 'B':{
      blink();      
   //   _state=LedState::BLINK;
    }
    case 'E':{
      Serial.println("send done and succes");
    }

    }
  }
 }
}

void Led::setOnStateCallback(StateCallback callback) {
  _cb = callback;
}

void Led::notifyStateChanged() {
  if (_cb) {
    _cb(_state);  // Call the callback function
  }
}