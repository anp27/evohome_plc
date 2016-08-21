/*
* receiver.h
*.

#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
  
class Receiver
{
    unsigned short InputBinding;
    unsigned short OutputBinding;
    tReceiverState State;
    unsigned long TriggerTime;

    public:
    Receiver(unsigned short InputBinding, unsigned short OutputBinding);
    bool iscallingforheat();
    };

#endif
