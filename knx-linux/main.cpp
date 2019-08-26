#include "../examples/knx-logik/Logikmodul.h"
#include "knx/bau57B0.h"
#include "knx_facade.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

KnxFacade *KNX = 0;
Platform *platform = 0;

uint32_t milliSec() {
    return platform->millis();
}
    
int main(int argc, char **argv) {

    platform = new LinuxPlatform(argc, argv);
    Bau57B0 bau(*platform);
    KNX = new KnxFacade(bau);


    appSetup();

    while (1) {
        KNX->loop();
        if (KNX->configured())
            appLoop();
        platform->mdelay(10);
    }
}