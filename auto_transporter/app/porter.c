#include "porter.h"

typedef enum { P_INIT,
  P_WAIT_FOR_LOADING1, P_WAIT_FOR_START1, P_TRANSPORTING1, P_WAIT_FOR_UNLOADING1, P_WAIT_FOR_START2,
  P_MOVING1, P_WAIT_FOR_LOADING2, P_WAIT_FOR_START3,
  P_MOVING2, P_MOVING3,
  P_TRANSPORTING2, P_TRANSPORTING3, P_WAIT_FOR_UNLOADING2, P_SPINNING, P_MOVING4,
  P_STOPPED
} porter_state;
porter_state p_state = P_INIT;

void porter_config(void) {
  init_f("transporter");
  line_tracer_config();
  carrier_config();
  bumper_config();
  wall_detector_config();
  linemon_config();
  driver_config();
}

bool p_is_entry = true;
bool p_is_do = false;
bool p_is_exit = false;

void porter_transport(void) {
  if( p_is_entry ) {
    fmt_f("state:%d", p_state, 2);
  }
  switch(p_state) {
  case P_INIT:
    if( p_is_entry ) {
      porter_config();
      p_is_entry = false;
    }
    if( true ) { // イベントを待たずに必ず遷移する
      p_state = P_WAIT_FOR_LOADING1;
      p_is_entry = true;
    }
    break;
  case P_WAIT_FOR_LOADING1:
    if( p_is_entry ) {
      p_is_entry = false;
    }
    if (carrier_cargo_is_loaded()) {
      p_state = P_WAIT_FOR_START1;
      p_is_entry = true;
    }
    if (bumper_is_pushed()) {
      p_state = P_MOVING1;
      p_is_entry = true;
    }
    if( p_is_entry ) {
    }
    break;
  case P_WAIT_FOR_START1:
    if( p_is_entry ) {
      p_is_entry = false;
    }
    if (bumper_is_pushed()) {
      p_state = P_TRANSPORTING1;
      p_is_entry = true;
    }
    if( p_is_entry ) {
    }
    break;
  case P_TRANSPORTING1:
    if( p_is_entry ) {
      p_is_entry = false;
      p_is_do = true;
    }
    if( p_is_do ) {
      while(!wall_detector_is_detected()) {
        line_tracer_run();
      }
      p_is_do = false;
      p_is_exit = true;
    }
    if( p_is_exit ) {
      line_tracer_stop();
      p_state = P_WAIT_FOR_UNLOADING1;
      p_is_exit = false;
      p_is_entry = true;
    }
    if( p_is_entry ) {
    }
    break;
  case P_WAIT_FOR_UNLOADING1:
    if( p_is_entry ) {
      p_is_entry = false;
    }
    if (!carrier_cargo_is_loaded()) {
      p_state = P_WAIT_FOR_START2;
      p_is_entry = true;
    }
    if( p_is_entry ) {
    }
    break;
  case P_WAIT_FOR_START2:
    if ( p_is_entry ) {
      p_is_entry = false;
    }
    if (bumper_is_pushed()) {
      p_state = P_MOVING2;
      p_is_entry = true;
    }
    break;
  // 確認済み
  case P_MOVING1:
    if( p_is_entry ) {
      p_is_entry = false;
      p_is_do = true;
    }
    if( p_is_do ) {
      while(!wall_detector_is_detected()){
        line_tracer_run();
      }
      if(wall_detector_is_detected()) {
        p_is_do = false;
        p_is_exit = true;
      }
    }
    if( p_is_exit ) {
      line_tracer_stop();
      p_state = P_WAIT_FOR_LOADING2;
      p_is_exit = false;
      p_is_entry = true;
    }
    break;
  case P_MOVING2:
    if ( p_is_entry ) {
      p_is_entry = false;
      p_is_do = true;
    }
    if ( p_is_do ) {
      while(!wall_detector_is_detected()) {
        line_tracer_run();
      }
      p_state = P_MOVING3;
      p_is_do = false;
    }
    break;
  case P_MOVING3:
    if( p_is_entry ) {
      p_is_entry = false;
      p_is_do = true;
    }
    if( p_is_do ) {
      while(!wall_detector_is_detected()) {
        line_tracer_run();
      }
      p_is_do = false;
      p_is_exit = true;
    }
    if( p_is_exit ) {
      line_tracer_stop();
      p_is_exit = false;
      p_state = P_STOPPED;
    }
    break;
  case P_WAIT_FOR_LOADING2:
    if( p_is_exit ) {
      p_is_entry = false;
    }
    if(bumper_is_pushed()) {
      p_state = P_MOVING2;
      p_is_entry = true;
    }
    if(carrier_cargo_is_loaded()) {
      p_state = P_WAIT_FOR_START3;
      p_is_entry = true;
    }
    break;
  case P_WAIT_FOR_START3:
    if( p_is_entry ) {
      p_is_entry = false;
    }
    if(bumper_is_pushed()) {
      p_state = P_TRANSPORTING2;
      p_is_entry = true;
    }
    break;
  case P_TRANSPORTING2:
    if( p_is_entry ) {
      p_is_entry = false;
      p_is_do = true;
    }
    if( p_is_do ) {
      line_tracer_run();
      if (!bumper_is_pushed()) {
        p_is_do = false;
        p_is_entry = true;
        p_state = P_TRANSPORTING3;
      }
    }
    break;
  case P_TRANSPORTING3:
    if( p_is_entry ) {
      p_is_entry = false;
      p_is_do = true;
    }
    if( p_is_do ) {
      line_tracer_run();
      if (bumper_is_pushed()) {
        p_is_do = false;
        p_is_exit = true;
      }
    }
    if( p_is_exit ) {
      line_tracer_stop();
      p_state = P_WAIT_FOR_UNLOADING2;
      p_is_exit = false;
      p_is_entry = true;
    }
    break;
  case P_WAIT_FOR_UNLOADING2:
    if( p_is_entry ) {
      p_is_entry = false;
    }
    if(!carrier_cargo_is_loaded()) {
      p_state = P_SPINNING;
      p_is_entry = true;
    }
    break;
  case P_STOPPED:
    return;
    break;
  }
}
