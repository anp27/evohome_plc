#include "boilercontrol.h"

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
  /*
   * Check for timer roll over and update timestamp if required. Strictly speaking
   * this will extend the open / close time in the unlikely event a valve event happens 
   * on roll over, but this is the safest and easiest way of dealing with the problem.
   */
  if (millis() < ActionTime)
    ActionTime = millis();
    
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
      if ((millis() - ActionTime) > BOILER_START_TIME)
        State = ON;
      break;
      
    case SHUTTING_DOWN :
      if ((millis() - ActionTime) > BOILER_STOP_TIME)
        State = OFF;

      if (Requests > 0)
      {
        FireUp();
        State = FIRING_UP; 
      }
      break;

    default :
      break;
  }
}
