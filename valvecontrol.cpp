#include "valvecontrol.h"

Valve::Valve(unsigned short binding, Boiler* plant)
{
  Plant = plant;
  Binding = binding;
  State = CLOSED;
  ActionTime = millis();
  pinMode(Binding, OUTPUT);
  digitalWrite(Binding,VALVE_CLOSED);
}

void Valve::CloseValve()
{  
  switch (State) {
    case OPEN :
      ActionTime = millis();
      State = DEREGISTERING;
      break;
      
    default :
      break;
  }
    
}

void Valve::OpenValve()
{  
  switch (State) {
    case CLOSED :
      ActionTime = millis();
      State = OPENING;
      digitalWrite(Binding,VALVE_OPEN);
      break;
      
    case HELD_OPEN :
      ActionTime = millis();
      State = OPENING;
      digitalWrite(Binding,VALVE_OPEN);
      break;

    default :
      break;
  }  
}

void Valve::ProcessValve()
{
  /*
   * Check for timer roll over and update timestamp if required. Strictly speaking
   * this will extend the open / close time in the unlikely event a valve event happens 
   * on roll over, but this is the safest and easiest way of dealing with the problem.
   */
  if (millis() < ActionTime)
    ActionTime = millis();
    
  switch (State) {
    case UNBOUND : break;
    case CLOSED : break;
    case OPEN : break;
    
    case OPENING :
      if ((millis() - ActionTime) > VALVE_OPEN_TIME)
        State = REGISTERING;
      break;
      
    case REGISTERING :
      Plant->RequestHeat();
      State = OPEN;
      break;

    case DEREGISTERING :
      if (Plant->RevokeRequest())
      {
        State = CLOSING;
        digitalWrite(Binding,VALVE_CLOSED);
      }
      else
      {
        State = HELD_OPEN;
      }
      break;

    case HELD_OPEN :
      if (Plant->AllowClose())
      {
        State = CLOSING;
        digitalWrite(Binding, VALVE_CLOSED);
      }
      break;
      
    case CLOSING :
      if ((millis() - ActionTime) > VALVE_CLOSE_TIME)
        State = CLOSED;
      break;

    default :
      break;
  }
}
