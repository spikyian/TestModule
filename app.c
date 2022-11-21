#include <xc.h>
#include "service.h"
#include "nv.h"
#include "can.h"

void init(void) {
    unsigned char i;
    
    i=0;
    // add the services we need
 //   services[i++] = ConsumerService;  // event consumption done early for better response times
    services[i++] = &canService;
    // services[i++] = &MnsService;
    services[i++] = &nvService;
}