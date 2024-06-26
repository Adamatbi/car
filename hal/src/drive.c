#include "hal/drive.h"
#include "hal/helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LEFT_WHEEL_DIRECTION_FILE_PATH "/sys/class/gpio/gpio48/direction"
#define LEFT_WHEEL_VALUE_FILE_PATH "/sys/class/gpio/gpio48/value"

#define RIGHT_WHEEL_DIRECTION_FILE_PATH "/sys/class/gpio/gpio49/direction"
#define RIGHT_WHEEL_VALUE_FILE_PATH "/sys/class/gpio/gpio49/value"


// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;
double rampUpTime = 0.04;
double secondPerRotation = 1.1;
double secondPerDegree;


void drive_init(void) 
{
    assert(!is_initialized);
    is_initialized = true;
    run_command("config-pin p9.15 gpio");
    run_command("config-pin p9.23 gpio");
    set_char_value_in_file(LEFT_WHEEL_DIRECTION_FILE_PATH, "out");
    set_char_value_in_file(RIGHT_WHEEL_DIRECTION_FILE_PATH, "out");
    drive_set_left_wheel(false);
    drive_set_right_wheel(false);
    secondPerDegree = secondPerRotation/360.0;
}

void turn_left(int degree)
{
    drive_set_left_wheel(false);
    drive_set_right_wheel(true);
    usleep((degree * secondPerDegree * 1000000)-rampUpTime*1000000);
    drive_set_left_wheel(false);
    drive_set_right_wheel(false);
}

void turn_right(int degree)
{
    drive_set_left_wheel(true);
    drive_set_right_wheel(false);
    usleep(degree * secondPerDegree * 1000000);
    drive_set_left_wheel(false);
    drive_set_right_wheel(false);
}

void drive_set_left_wheel(bool forward)
{
    assert(is_initialized);
    set_int_value_in_file(LEFT_WHEEL_VALUE_FILE_PATH, !forward ? 1 : 0);
}

void drive_set_right_wheel(bool forward)
{
    assert(is_initialized);
    set_int_value_in_file(RIGHT_WHEEL_VALUE_FILE_PATH, !forward ? 1 : 0);
}

void drive_set_both_wheels(bool forward)
{
    assert(is_initialized);
    drive_set_left_wheel(forward);
    drive_set_right_wheel(forward);
}

void drive_cleanup(void)
{
    // Free any memory, close files, ...
    assert(is_initialized);
    is_initialized = false;
}