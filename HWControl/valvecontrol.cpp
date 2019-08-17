#include "valvecontrol.h"
#include <limits.h>

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

  unsigned long TimeTaken;

  //Calculate time taken since last event
  if (millis() >= ActionTime)
      TimeTaken = (millis() - ActionTime);
  else
      TimeTaken = (millis() + (ULONG_MAX - ActionTime));
    
  switch (State) {
    case UNBOUND : break;
    case CLOSED : break;
    case OPEN : break;
    
    case OPENING :
      if (TimeTaken > VALVE_OPEN_TIME)
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
      if (TimeTaken > VALVE_CLOSE_TIME)
        State = CLOSED;
      break;

    default :
      break;
  }
}
