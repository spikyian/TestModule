#include <xc.h>
#include "merglcb.h"
// the services
#include "mns.h"
#include "nv.h"
#include "can.h"
#include "boot.h"
// continue
#include "module.h"

/**************************************************************************
 * Application code packed with the bootloader must be compiled with options:
 * XC8 linker options -> Additional options --CODEOFFSET=0x800 
 * This generates an error
 * ::: warning: (2044) unrecognized option "--CODEOFFSET=0x800"
 * but this can be ignored as the option works
 * 
 * Then the Application project must be made dependent on the Bootloader 
 * project by adding the Bootloader to project properties->Conf:->Loading
 ***************************************************************************/

const Service * const services[] = {
    &canService,
    &mnsService,
    &nvService,
    &bootService
};
void setup(void) {
    /*uint8_t i;
    i=0;
    // add the services we need
    //services[i++] = &consumerService;  // event consumption done early for better response times
    services[i++] = &canService;
    services[i++] = &mnsService;
    services[i++] = &nvService;
    services[i++] = &bootService; */
    
    
    // use CAN as the module's transport
    transport = &canTransport;
}

void loop(void) {
    
}

// Application functions required by MERGLCB library
uint8_t APP_nvDefault(uint8_t index) {
    return index*3;
} 
void APP_nvValueChanged(uint8_t index, uint8_t value, uint8_t oldValue) {
    
}
NvValidation APP_nvValidate(uint8_t index, uint8_t value)  {
    return VALID;
}
ValidTime APP_isSuitableTimeToWriteFlash(void){
    return GOOD_TIME;
} 
Processed APP_preProcessMessage(Message * m) {
    return NOT_PROCESSED;
}
Processed APP_postProcessMessage(Message * m) {
    return NOT_PROCESSED;
}