/*
 * This is an example module using the MERGLCBlib. 
 * THIS IS NOT READY FOR PRODUCTION but may prove useful for testing and as a 
 * guide of how to use MERGLCBlib.
 * 
 * This simply sends an event message whenever the digital inputs change.
 * It does not provide:
 * * Pulse outputs
 * * Flashing outputs
 * * Ability to change the polarity of outputs generated
 * * Restore previous state on power on
 * * Any default events
 * 
 * This module could have been implemented in two ways:
 * 1. To add code to the APP_preProcessMessage() function and process the 
 *    ACON/ACOF/ASON/ASOF directly.
 * 2. Add code to the APP_processConsumedEvent(tableIndex, m) function without
 *    any interpretation of how the EVs are used.
 * 3. To allow the event_consumer service add the event's Actions to an action 
 *    queue and then process the Actions from the queue in the application's
 *    main loop.
 * 
 * This example implements method 3.
 */

/**
 * @copyright Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
 */
/*
  This work is licensed under the:
      Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
   To view a copy of this license, visit:
      http://creativecommons.org/licenses/by-nc-sa/4.0/
   or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

   License summary:
    You are free to:
      Share, copy and redistribute the material in any medium or format
      Adapt, remix, transform, and build upon the material

    The licensor cannot revoke these freedoms as long as you follow the license terms.

    Attribution : You must give appropriate credit, provide a link to the license,
                   and indicate if changes were made. You may do so in any reasonable manner,
                   but not in any way that suggests the licensor endorses you or your use.

    NonCommercial : You may not use the material for commercial purposes. **(see note below)

    ShareAlike : If you remix, transform, or build upon the material, you must distribute
                  your contributions under the same license as the original.

    No additional restrictions : You may not apply legal terms or technological measures that
                                  legally restrict others from doing anything the license permits.

   ** For commercial use, please contact the original copyright holder(s) to agree licensing terms

    This software is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE
 */
/**
 * @author Ian Hogg 
 * @date Mar 2023
 * 
 */ 

#include <xc.h>
#include "module.h"
#include "vlcb.h"
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
    &eventProducerService,  // needed for the Heartbeat event
    &eventAckService
};
#define NUM_IO  16

void setup(void) {
    uint8_t io;
    
    // use CAN as the module's transport
    transport = &canTransport;
    
    for (io=0; io<NUM_IO; io++) {
        pinMode(io, OUTPUT);
        digitalWrite(io, 0);
    }
}

void loop(void) {
    uint8_t io;
    uint8_t state;
    Action * a;
    
    a = popAction();
    if (a != NULL) {
        //convert the action into a channel and state
        io = a->a.value;
        if ((io >0) && (io <= NUM_IO)) {
            state = a->state;
            digitalWrite(io, state);
        }
    }
}

// Application functions required by MERGLCB library
/**really used by this example code. They are simply initialised
 * here in a reconisable way.
 */
uint8_t APP_nvDefault(uint8_t index) {
    return index*3;
} 

/**
 * We don't need to do anything when NVs change.
 */
void APP_nvValueChanged(uint8_t index, uint8_t value, uint8_t oldValue) {
    
}

/**
 * We don't need to validate NV values.
 */
NvValidation APP_nvValidate(uint8_t index, uint8_t value)  {
    return VALID;
}

/**
 * When adding an event we just simply need to call the library.
 */
uint8_t APP_addEvent(uint16_t nodeNumber, uint16_t eventNumber, uint8_t evNum, uint8_t evVal) {
    return addEvent(nodeNumber, eventNumber, evNum, evVal, 0);
}

/**
 * There are no special timing constraints so anytime is a good time.
 */
ValidTime APP_isSuitableTimeToWriteFlash(void){
    return GOOD_TIME;
}

/**
 * This application doesn't need to process any messages in a special way.
 */
Processed APP_preProcessMessage(Message * m) {
    return NOT_PROCESSED;
}

/**
 * This application doesn't need to process any messages in a special way.
 */
Processed APP_postProcessMessage(Message * m) {
    if (m->opc == OPC_TOF) {
        updateModuleErrorStatus();
    }
    return NOT_PROCESSED;
}

/**
 * This is needed by the library to get the current event state. However it isn't used
 */
EventState APP_GetEventState(Happening h) {
    return EVENT_OFF;
}