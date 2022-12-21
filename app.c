#include <xc.h>
#include "module.h"
#include "merglcb.h"
// the services
#include "mns.h"
#include "nv.h"
#include "can.h"
#include "boot.h"
#include "event_teach.h"
#include "event_consumer.h"
#include "event_producer.h"
#include "event_acknowledge.h"
// continue
#include "arduino.h"


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
    &bootService,
    &eventTeachService,
    &eventConsumerService,
    &eventProducerService,
    &eventAckService
};
#define NUM_IO  16
uint8_t lastState[NUM_IO];

void setup(void) {
    uint8_t io;
    
    // use CAN as the module's transport
    transport = &canTransport;
    
    for (io=0; io<NUM_IO; io++) {
        pinMode(io, INPUT);
        lastState[io] = digitalRead(io);
    }
}

void loop(void) {
    uint8_t io;
    uint8_t state;
    
    for (io=0; io<NUM_IO; io++) {
        state = digitalRead(io);
        if (state != lastState[io]) {
            lastState[io] = state;
            sendProducedEvent(io+1, state?EVENT_ON:EVENT_OFF);
        }
    }
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
uint8_t APP_addEvent(uint16_t nodeNumber, uint16_t eventNumber, uint8_t evNum, uint8_t evVal) {
    return addEvent(nodeNumber, eventNumber, evNum, evVal, 0);
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