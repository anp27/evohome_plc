#include "boilercontrol.h"
#include <limits.h>

Boiler::Boiler(unsigned short binding)
{
    Binding = binding;
    Requests = 0;
    State = OFF;
    ActionTime = millis();
    pinMode(Binding, OUTPUT);
    digitalWrite(Binding,BOILER_OFF);
}

void Boiler::FireUp()
{
    ActionTime = millis();
    digitalWrite(Binding, BOILER_ON);  
}

void Boiler::ShutDown()
{
    ActionTime = millis();
    digitalWrite(Binding, BOILER_OFF);
}

bool Boiler::RequestHeat()
{
  //Increment request count:
  Requests+= 1;
  return true;
}

bool Boiler::RevokeRequest()
{
  //Decrement request count and return request status
  if (Requests > 0)
    Requests-= 1;

  return (Requests > 0);
}

bool Boiler::AllowClose()
{
  //Allow a valve to close if another opens, or the boiler has shutdown fully.s
  return ((Requests > 0) || (State == OFF));
}


void Boiler::ProcessState()
{
  unsigned long TimeTaken;

 //Calculate time taken since last event
  if (millis() >= ActionTime)
    TimeTaken = (millis() - ActionTime);
  else
    TimeTaken = (millis() + (ULONG_MAX - ActionTime));
    
  switch (State) {
    case DISCONNECTED : break;
    
    case OFF :
      if (Requests > 0)
      {
        FireUp();
        State = FIRING_UP; 
      }
    break;
    
    case ON : 
      if (Requests == 0)
      {
        ShutDown();
        State = SHUTTING_DOWN;
      }
      break;
      
    case FIRING_UP :
      if (TimeTaken > BOILER_START_TIME)
        State = ON;
      break;
      
    case SHUTTING_DOWN :
      if (TimeTaken > BOILER_STOP_TIME)
        State = OFF;
      else
      {
        if (Requests > 0)
        {
          FireUp();
          State = FIRING_UP;
        }
      }
      break;

    default :
      break;
  }
}
