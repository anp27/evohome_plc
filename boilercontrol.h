/*
 * boilercontrol.h
 */

 #ifndef BOILERCONTROL_H
 #define BOILERCONTROL_H

#include <Arduino.h>

/*
 * Type definitions
 */
typedef enum { DISCONNECTED = 0, OFF, FIRING_UP, ON, SHUTTING_DOWN } tBoilerState;

class Boiler
{
  unsigned short Binding;
  tBoilerState State;
  unsigned short Requests;
  unsigned long ActionTime;
  
  public:
    Boiler (unsigned short Binding);
    void ProcessState();
    bool RequestHeat();
    bool RevokeRequest();
    bool AllowClose();

  private:
    void FireUp();
    void ShutDown();  
};
 
 /*
 * System Constants
 */
#define   BOILER_START_TIME 4000
#define   BOILER_STOP_TIME  300000
#define   BOILER_ON         1
#define   BOILER_OFF        0


#endif

