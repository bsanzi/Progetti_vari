#include <Arduino.h>
#include <stdbool.h>

enum class LedState : char{
  ON = 'O',
  OFF = 'o',
  BLINK = 'B'
};

typedef void (*StateCallback)(LedState state);

class  Led{
public:
  Led(int PIN);
  
  void begin();
  void accendi();
  void spegni();
  void msgEval();
  LedState getState();
  bool CheckState(LedState state);

private:
  int _pin;
  LedState _state;
};
