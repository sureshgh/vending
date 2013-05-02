

#define ENABLE_TEXT_MODE "AT+CMGF=1"
#define ECHO_OFF		 "ATE0"
#define ENTER 0x0D

uint8_t initGSM();
void sendCommand(char* command);
uint8_t waitResponse(uint16_t timeout);
uint8_t readMsg(uint8_t i, char *msg);
void extractPinCode(char* msg,char *pin);
void extractMachineCode(char *msg,char *machine);
void extractItemCode(char *msg,char *item);
uint8_t isMessageNotification();
void sendMsg(char *msg);
void deleteMsg();
