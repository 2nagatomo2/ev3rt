#include "wall_detector.h"

const int wall_detector_sensor = EV3_PORT_4;
#define WALL_DETECTOR_THRESHOLD 8
int wd_threshold = WALL_DETECTOR_THRESHOLD;

void wall_detector_config(void) {
  ev3_sensor_config(wall_detector_sensor, ULTRASONIC_SENSOR);
}

bool wall_detector_is_detected(void) {
  return ev3_ultrasonic_sensor_get_distance(wall_detector_sensor) < WALL_DETECTOR_THRESHOLD;
}
