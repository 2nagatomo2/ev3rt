#include "linemon.h"

const int linemon_sensor = EV3_PORT_3;
#define LINEMON_THRESHOLD 20
int lm_threshold = LINEMON_THRESHOLD;

void linemon_config(void) {
  ev3_sensor_config(linemon_sensor, COLOR_SENSOR);
}

bool linemon_is_online(void) {
  return ev3_color_sensor_get_reflect(linemon_sensor) < lm_threshold;
}
