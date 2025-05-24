#ifndef Led_h
#define Led_h

#include <Arduino.h>
#include <stdbool.h>

enum class LedState : char{
  ON = 'O',
  ON_ed = 'o',
  OFF = 'F',
  OFF_ed = 'f',
  UNKNOWN = 'U',
  BLINK = 'B',
  BLINK_ed = 'b'
};

typedef void (*StateCallback)(LedState state);

class  Led{
public:
  Led(int PIN);
  
  void begin();
  void run();
  void accendi();
  void spegni();
  void blink();
  void msgEval();
  LedState getState();
  bool CheckState(LedState state);

  void setOnStateCallback(StateCallback callback);

private:
  int _pin;
  int _timeSetup;
  unsigned long _lastRun;
  LedState _state;
  LedState _lastState;

    StateCallback _cb; 
    void notifyStateChanged();
};

#endif