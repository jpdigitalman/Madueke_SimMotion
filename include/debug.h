#define DEBUG_ON 1
#define DEBUG_OFF 0
byte serialPrintMode = DEBUG_ON;

#define PRINTLINE(...) serialPrintMode == DEBUG_ON ? Serial.println(__VA_ARGS__) : 0

#define PRINT(...) serialPrintMode == DEBUG_ON ? Serial.print(__VA_ARGS__) : 0

#define PRINTF(...) serialPrintMode == DEBUG_ON ? Serial.printf(__VA_ARGS__) : 0