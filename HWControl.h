
/*
 * Heating System IO Configuration
 */

#ifndef HWCONTROL_H
#define HWCONTROL_H

#include <Arduino.h>
#include <Controllino.h>
 
// Inputs
#define DOWNSTAIRS_DEMAND CONTROLLINO_A0
#define UPSTAIRS_DEMAND CONTROLLINO_A1
#define HW_DEMAND CONTROLLINO_A2

//Outputs
#define BOILER_CFH        CONTROLLINO_R0
#define SPARE_VALVE       CONTROLLINO_R2
#define DOWNSTAIRS_VALVE  CONTROLLINO_R3
#define UPSTAIRS_VALVE    CONTROLLINO_R1
#define DHW_VALVE         CONTROLLINO_R4

#endif

