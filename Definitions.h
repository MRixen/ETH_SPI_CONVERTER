// USER DEFINED
const int SLOW_DOWN_CODE = 2;
const int CS_PIN_ENC28J60 = 7;
const int SPI_CS_PIN = 7;


const byte MESSAGE_SIZE_TCP = 5 * 6;
const byte MESSAGE_SIZE_SPI = 4;


MCP_CAN CAN(SPI_CS_PIN);                                  
byte len = 0;
byte buf[MESSAGE_SIZE_SPI];
byte bufferInTcp[MESSAGE_SIZE_TCP];
byte bufferOutSpi[MESSAGE_SIZE_SPI];



// GLOBAL DATA
const long MAX_WAIT_TIME = 5000;
const int MAX_ERROR_COUNTER_MODESWITCH = 3;
bool stopAllOperations = false;
bool debugMode;
const int ADXL = 1;
const int MCP2515 = 2;
const int NO_DEVICE = 3;
long errorTimerValue;
const int MAX_MOTOR_AMOUNT = 6;


EthernetClient client;
byte incoming_data[8];
