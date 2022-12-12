#ifndef _MODULE_H_
#define _MODULE_H_
#include "nv.h"
//
// General MERGLCB stuff
//
#define NUM_SERVICES 4   
// The data version stored at NV#0
#define APP_NVM_VERSION 1


//
// NV service
//
#define NV_NUM  10
#define NV_ADDRESS  0x200
#define NV_NVM_TYPE EEPROM_NVM_TYPE
#define NV_CACHE
extern uint8_t APP_nvDefault(uint8_t index);
extern NvValidation APP_nvValidate(uint8_t index, uint8_t value);
extern void APP_nvValueChanged(uint8_t index, uint8_t newValue, uint8_t oldValue);

//
// CAN service
//
#define CANID_ADDRESS  0x3FE    // 1 byte
#define CANID_NVM_TYPE EEPROM_NVM_TYPE
#define CAN_INTERRUPT_PRIORITY 0    // all low priority
#define CAN_CLOCK_MHz   64
// Number of buffers
#define CAN_NUM_RXBUFFERS   32  
#define CAN_NUM_TXBUFFERS   8

//
// BOOT service
//
#define BOOT_FLAG_ADDRESS   0x3FF
#define BOOT_FLAG_NVM_TYPE EEPROM_NVM_TYPE
#define BOOTLOADER_PRESENT

//
// MNS service
//
// Processor clock speed
#define clkMHz      64
// 2 bytes for the module's node number
#define NN_ADDRESS  0x3FC 
#define NN_NVM_TYPE EEPROM_NVM_TYPE
// 1 byte for the mode
#define MODE_ADDRESS    0x3FB
#define MODE_NVM_TYPE   EEPROM_NVM_TYPE
// Parameters
#define PARAM_MANU              0xA5
#define PARAM_MODULE_ID         0xAD
#define PARAM_MAJOR_VERSION     1
#define PARAM_MINOR_VERSION     'a'
#define PARAM_BUILD_VERSION     1
#define PARAM_NUM_NV            NV_NUM
#define PARAM_NUM_EVENTS        0
#define PARAM_NUM_EV_EVENT      0
// Module name - must be 7 characters
#define NAME    "TEST   "
// LEDs and PB
#define NUM_LEDS    2                                   // GREEN is 0 YELLOW is 1
#define APP_setPortDirections()(TRISBbits.TRISB6=TRISBbits.TRISB7=0,TRISAbits.TRISA2=1)
#define APP_writeLED1(state)   (LATBbits.LATB7=state)   // GREEN true is on
#define APP_writeLED2(state)   (LATBbits.LATB6=state)   // YELLOW true is on 
#define APP_pbState()          (!(PORTAbits.RA2))            // where the push button is connected

#endif