#include <std.h>
#include <stdio.h>
#include <stdlib.h>
#include <tistdtypes.h>
#include <sio.h>
#include <tsk.h>

#include "common.h"

int licznik = 0;
int dioda = 0;

void led_blink()
{
while(1) {
licznik ++;
if (licznik >5000) {
licznik = 0;
if (dioda == 1) {
//	RED_OFF 
dioda =0; 
}
else { 
//	RED_ON
dioda = 1;
}
}
TSK_yield();
}
}
