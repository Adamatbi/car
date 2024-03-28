#include "hal/drive.h"
#include "hal/helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LEFT_WHEEL_DIRECTION_FILE_PATH "/sys/class/gpio/gpio23/direction"
#define LEFT_WHEEL_VALUE_FILE_PATH "/sys/class/gpio/gpio23/value"
#define LEFT_WHEEL_ACTIVE_LOW_FILE_PATH "/sys/class/gpio/gpio23/active_low"

#define RIGHT_WHEEL_DIRECTION_FILE_PATH "/sys/class/gpio/gpio15/direction"
#define RIGHT_WHEEL_VALUE_FILE_PATH "/sys/class/gpio/gpio15/value"
#define RIGHT_WHEEL_ACTIVE_LOW_FILE_PATH "/sys/class/gpio/gpio15/active_low"


// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;

void drive_init(void) 
{
    assert(!is_initialized);
    is_initialized = true;
    run_command("config-pin p9.15 gpio");
    run_command("config-pin p9.23 gpio");
    set_int_value_in_file(RIGHT_WHEEL_ACTIVE_LOW_FILE_PATH, 1);
    set_int_value_in_file(LEFT_WHEEL_ACTIVE_LOW_FILE_PATH, 1);
    set_char_value_in_file(LEFT_WHEEL_DIRECTION_FILE_PATH, "out");
    set_char_value_in_file(RIGHT_WHEEL_DIRECTION_FILE_PATH, "out");
    
    srand(time(0));
}

void drive_set_left_wheel(bool forward)
{
    assert(is_initialized);
    set_int_value_in_file(LEFT_WHEEL_VALUE_FILE_PATH, forward ? 1 : 0);
}

void drive_set_right_wheel(bool forward)
{
    assert(is_initialized);
    set_int_value_in_file(RIGHT_WHEEL_VALUE_FILE_PATH, forward ? 1 : 0);
}

void drive_cleanup(void)
{
    // Free any memory, close files, ...
    assert(is_initialized);
    is_initialized = false;
}