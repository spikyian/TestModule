#define NUMSERVICES 2   // don't count MNS as a service

//
// NV service
//
#define NV_NUM  10
#define NV_ADDRESS  0x200
#define NV_NVM_TYPE EEPROM
#define NV_CACHE
extern void APP_factoryResetNv(void);
extern unsigned char APP_nvValidate(unsigned char index, unsigned char value);
extern void APP_nvValueChanged(unsigned char index, unsigned char newValue, unsigned char oldValue);

//
// CAN service
//
#define CANID_ADDRESS  0x3FE    // 1 byte
#define CANID_NVM_TYPE EEPROM


//
// MNS service
//
#define NUM_RXBUFFERS   32
#define NUM_TXBUFFERS   8
#define NN_ADDRESS  0x3FC   // 2 bytes
#define NN_NVM_TYPE EEPROM
#define MODE_ADDRESS    0x3FB   // 1 byte
#define MODE_NVM_TYPE   EEPROM
extern void APP_GSTOP(void);