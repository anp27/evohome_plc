/*
 * valvecontrol.h
 */

 #ifndef VALVECONTROL_H
 #define VALVECONTROL_H

#include <Arduino.h>
#include "boilercontrol.h"


/*
 * Type definitions
 */
typedef enum { UNBOUND = 0, CLOSED, OPENING, REGISTERING, OPEN, DEREGISTERING, HELD_OPEN, CLOSING } tValveState;

class Valve
{
  unsigned short Binding;
  Boiler* Plant;
  tValveState State;
  unsigned long ActionTime;
  
  public:
    Valve (unsigned short Binding, Boiler* plant);
    void ProcessValve();
    void OpenValve();
    void CloseValve();
};
 
 /*
 * System Constants
 */
#define   VALVE_OPEN_TIME   4000
#define   VALVE_CLOSE_TIME  4000
#define   VALVE_OPEN        1
#define   VALVE_CLOSED      0


#endif

