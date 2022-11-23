//
// General MERGLCB stuff
//
#define NUM_SERVICES 8   
// Number of buffers
#define NUM_RXBUFFERS   32  
#define NUM_TXBUFFERS   8
// The data version stored at NV#0
#define APP_NVM_VERSION 1
extern void APP_GSTOP(void);


//
// NV service
//
#define NV_NUM  10
#define NV_ADDRESS  0x200
#define NV_NVM_TYPE EEPROM_NVM_TYPE
#define NV_CACHE
extern void APP_factoryResetNv(void);
extern unsigned char APP_nvValidate(unsigned char index, unsigned char value);
extern void APP_nvValueChanged(unsigned char index, unsigned char newValue, unsigned char oldValue);

//
// CAN service
//
#define CANID_ADDRESS  0x3FE    // 1 byte
#define CANID_NVM_TYPE EEPROM_NVM_TYPE
#define CANID_DEFAULT   1

//
// BOOT service
//
#define BOOT_FLAG_ADDRESS   0x3FF
#define BOOTLOADER_PRESENT

//
// MNS service
//
// 2 bytes for the module's node number
#define NN_ADDRESS  0x3FC 
#define NN_NVM_TYPE EEPROM_NVM_TYPE
#define NN_HI_DEFAULT  0
#define NN_LO_DEFAULT  0
// 1 byte for the mode
#define MODE_ADDRESS    0x3FB
#define MODE_NVM_TYPE   EEPROM_NVM_TYPE
#define MODE_DEFAULT    MODE_SETUP
// Parameters
#define PARAM_MANU              MANU_MERG
#define PARAM_MAJOR_VERSION     1
#define PARAM_MINOR_VERSION     'a'
#define PARAM_BUILD_VERSION     1
#define PARAM_MODULE_ID         MTYP_MERGLCB
#define PARAM_NUM_NV            NV_NUM
#define PARAM_NUM_EVENTS        0
#define PARAM_NUM_EV_EVENT      0
// Module name - must be 7 characters
#define NAME    "TEST   "

