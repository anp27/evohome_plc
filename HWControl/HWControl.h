
/*
 * Heating System IO Configuration
 */

#ifndef HWCONTROL_H
#define HWCONTROL_H

#include <Arduino.h>
#include <Controllino.h>
 
// Inputs
#define DOWNSTAIRS_DEMAND       CONTROLLINO_A0
#define UPSTAIRS_DEMAND         CONTROLLINO_A1
#define HW_DEMAND               CONTROLLINO_A2
#define BATHROOM_UF_DEMAND      CONTROLLINO_A3

//Outputs
#define BOILER_CFH              CONTROLLINO_R0
#define UNDERFLOOR_VALVE        CONTROLLINO_R2
#define DOWNSTAIRS_VALVE        CONTROLLINO_R3
#define UPSTAIRS_VALVE          CONTROLLINO_R1
#define DHW_VALVE               CONTROLLINO_R4
#define BATHROOM_UF_PUMP        CONTROLLINO_R7

#define DOWNSTAIRS_RCVR_PWR     CONTROLLINO_R6
#define UPSTAIRS_RCVR_PWR       CONTROLLINO_R6
#define HW_DEMAND_RCVR_PWR      CONTROLLINO_R6
#define BATHROOM_UF_PWR         CONTROLLINO_R6


#endif

