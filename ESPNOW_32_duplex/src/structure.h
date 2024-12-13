typedef struct comand 
{
    char msg[2];
    bool response;
} comand;

comand myComand;

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&myComand, incomingData, sizeof(myData));
  comandEval(myComand);

}

void comandEval(comand a){
 if 
}