/*
* receiver.h
*/

#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>

typedef enum {  BOOTING = 0,
                BOOTED,
                RESETTING} tReceiverState;
  
class Receiver
{
    unsigned short InputBinding;
    unsigned short OutputBinding;
    tReceiverState State;
    unsigned long EventTime;
    bool ResetReceiver;
    bool LastRequestState = false;

    public:
    Receiver(unsigned short input, unsigned short output, bool reset);
    bool iscallingforheat();
    };
    
#define RESET_PIN_STATE                 0
#define DEFAULT_RESET_TIME              1000
#define DEFAULT_BOOT_TIME_MS            3000
#define DEFAULT_RESET_TIMEOUT_HRS       3
#define DEFAULT_RESET_TIMEOUT           DEFAULT_RESET_TIMEOUT_HRS * 60 * 60 * 1000

#endif