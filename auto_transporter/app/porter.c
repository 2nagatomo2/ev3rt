#include "porter.h"

typedef enum { P_INIT,
  P_WAIT_FOR_LOADING, P_WAIT_FOR_START1, P_TRANSPORTING,
  P_WAIT_FOR_UNLOADING, P_WAIT_START2, P_MOVING1, P_TERMINATED
} porter_state;
porter_state p_state = P_INIT;

void porter_config(void) {
  init_f("transporter");
  line_tracer_config();
  carrier_config();
  bumper_config();
}

bool p_is_entry = true;

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
      p_state = P_WAIT_FOR_LOADING;
      p_is_entry = true;
    }
    break;
  case P_WAIT_FOR_LOADING:
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
    if (bamper_is_pushed()) {
      p_state = P_TRANSPORTING;
      p_is_entry = true;
    }
    if( p_is_entry ) {
    }
    break;
  case P_MOVING1:
    if( p_is_entry ) {
      p_is_entry = false;
      p_is_do = true;
    }
  case P_TRANSPORTING:
    if( p_is_entry ) {
      p_is_entry = false;
    }
    line_tracer_run();
    if (wall_detector_is_detected()) {
      p_state = P_WAIT_FOR_UNLOADING;
      p_is_entry = true;
    }
    if( p_is_entry ) {
    }
    break;
  /*
  case P_WAIT_FOR_UNLOADING:
    if( p_is_entry ) {
      p_is_entry = false;
    }
    line_tracer_run();
    if (timer_is_timedout()) {
      p_state = STOPPED;
      p_is_entry = true;
    }
    if( p_is_entry ) {
      line_tracer_stop();
      timer_stop();
    }
    break;
  case STOPPED:
    break;
    */
  }
}
