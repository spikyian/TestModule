#include <xc.h>
#include "merglcb.h"
// the services
#include "mns.h"
#include "nv.h"
#include "can.h"
#include "boot.h"
// continue
#include "module.h"

void init(void) {
    uint8_t i;
    i=0;
    // add the services we need
    //services[i++] = &consumerService;  // event consumption done early for better response times
    services[i++] = &canService;
    services[i++] = &mnsService;
    services[i++] = &nvService;
    services[i++] = &bootService;  

}

void loop(void) {
    
}

// Application functions required by MERGLCB library
uint8_t APP_nvDefault(uint8_t index) {
    return 0;
} 
void APP_GSTOP(void) {
    
} 
void APP_nvValueChanged(uint8_t index, uint8_t value, uint8_t oldValue) {
    
}
uint8_t APP_nvValidate(uint8_t index, uint8_t value)  {
    return 0;
}
uint8_t APP_isSuitableTimeToWriteFlash(void){
    return 1;
} 