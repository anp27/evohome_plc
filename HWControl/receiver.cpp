#include "receiver.h"
#include <limits.h>

/* Receiver constructor
*/
Receiver::Receiver(unsigned short input, unsigned short output, bool reset)
{
    //Initialise setup
    InputBinding = input;
    OutputBinding = output;
    ResetReceiver = reset;
    
    //Initialise state
    State = RESETTING;
    
    //Setup Arduino IO
    pinmode(InputBinding, INPUT);
    pinmode(OutputBinding, OUTPUT);
    
    //Put the receiver in reset state
    digitalwrite(OutputBinding, RESET_PIN_STATE);
    
    //Timestamp init event:
    EventTime = millis();
}


bool Receiver::iscallingforheat()
{
    unsigned long TimeTaken;
    
    //Disable call for heat, unless we are in a valid state
    bool heat = false;
    
    //Calculate time taken since last event
    if (millis() >= EventTime)
        TimeTaken = (millis() - EventTime);
    else
        TimeTaken = (millis() + (ULONG_MAX - EventTime));
    
    
    switch(State)
    {   case PENDING_RESET:
            digitalwrite(OutputBinding, RESET_PIN_STATE);
            State = RESETTING;
            break;
            
        case BOOTING:
            if (TimeTaken >= DEFAULT_BOOT_TIME_MS)
                State = BOOTED;
            break;
            
        case BOOTED:
            heat = digitalread(InputBinding);
            
            //Detect a request change
            if (heat != LastRequestState)
            {
                //Record the switch time
                EventTime = millis();
                //Update the request state
                LastRequestState = heat;
            }
            
            if (heat && ResetReceiver)
                if (TimeTaken > DEFAULT_RESET_TIMEOUT)
                    //Reset the receiver as we have been heating for a while
                    State = PENDING_RESET;
            break;
            
        case RESETTING:
            //Wait for device reset time
            if (TimeTaken >= DEFAULT_RESET_TIME){
                digitalwrite(OutputBinding, !RESET_PIN_STATE);
                State = BOOTING;
            }
            break;
        
        default:
            State = PENDING_RESET;
            break;
    }
    
    return heat;
}
