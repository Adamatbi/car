#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "hal/drive.h"

static long long getTimeInMs(void);

int main()
{
    drive_init();
    
    sleep(1);
    drive_set_left_wheel(true);
    sleep(1);
    drive_set_left_wheel(false);
    sleep(1);
    drive_set_right_wheel(true);
    sleep(1);
    drive_set_right_wheel(false);
    sleep(1);
    
    drive_cleanup();
}



static long long getTimeInMs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nano_seconds = spec.tv_nsec;
    long long milliseconds = seconds * 1000 + nano_seconds / 1000000;  
    return milliseconds;
}