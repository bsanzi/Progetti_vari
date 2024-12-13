#define baud_rate 115200
#define serial_delay 10

enum class ShutterState : char {
  CLOSED = 'C',
  CLOSING= 'c',
  OPENED = 'O',
  OPENING = 'o',
  STOPPED = 'S',
  UNKNOWN = 'U'
};



// funzione di stampa comando
void printcomand(ShutterState a) {
  Serial.print(">");
  char carattere = static_cast<char>(a);
  Serial.println((char)carattere);
}