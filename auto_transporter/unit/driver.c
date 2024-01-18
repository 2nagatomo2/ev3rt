#include "driver.h"

const int left_wheel = EV3_PORT_A;
const int right_wheel = EV3_PORT_C;

#define DR_POWER 40
int dr_power = DR_POWER;

void driver_config(void) {
  ev3_motor_config(left_wheel, LARGE_MOTOR);
  ev3_motor_config(right_wheel, LARGE_MOTOR);
}

void driver_turn_left(void) {
  ev3_motor_set_power(left_wheel, 0);
  ev3_motor_set_power(right_wheel, dr_power);
}

void driver_turn_right(void) {
  ev3_motor_set_power(left_wheel, dr_power);
  ev3_motor_set_power(right_wheel, 0);
}

void driver_stop(void) {
  ev3_motor_stop(left_wheel, true);
  ev3_motor_stop(right_wheel, true);
}

void driver_back(void) {
  ev3_motor_set_power(left_wheel, -dr_power);
  ev3_motor_set_power(right_wheel, -dr_power);
}

void driver_spin(void) {
  driver_turn_left();
}