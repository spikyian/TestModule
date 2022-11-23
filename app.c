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
    unsigned char i;
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