#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "hal/drive.h"


int main()
{
    drive_init();    
    
    sleep(1);
    turn_left(10);

    //cleanup
    drive_cleanup();
}