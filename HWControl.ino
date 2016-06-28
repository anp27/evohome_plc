#include <SPI.h>
#include <Controllino.h>
#include "HWControl.h"
#include "valvecontrol.h"
#include "boilercontrol.h"

//#define HW_PRIORITY
#undef HW_PRIORITY
/*
 * Valve Outputs
 */
Boiler BoilerControl(BOILER_CFH);
Valve UpstairsValve(UPSTAIRS_VALVE, &BoilerControl);
Valve DownstairsValve(DOWNSTAIRS_VALVE, &BoilerControl);
Valve DHWValve(DHW_VALVE, &BoilerControl);

void setup() {

/*
 * Configure Controllino IO
 */
//Configuration Digital IN (24Vdc)
pinMode(CONTROLLINO_A0, INPUT);  
pinMode(CONTROLLINO_A1, INPUT);  
pinMode(CONTROLLINO_A2, INPUT);

// Configuration Relay OUT
pinMode(CONTROLLINO_R0, OUTPUT);  
pinMode(CONTROLLINO_R1, OUTPUT); 
pinMode(CONTROLLINO_R2, OUTPUT);  
pinMode(CONTROLLINO_R3, OUTPUT); 
pinMode(CONTROLLINO_R4, OUTPUT);

}

/*
 * Processes valve requests on all valves
 */
void ProcessValves() {
  UpstairsValve.ProcessValve();
  DownstairsValve.ProcessValve();
  DHWValve.ProcessValve();
}

void loop() {
/*
 * Main Control Loop
 */

 #ifdef HW_PRIORITY
 
 if (digitalRead(HW_DEMAND) == HIGH)            //DHW Priority
 {
    UpstairsValve.CloseValve();
    DownstairsValve.CloseValve();
    DHWValve.OpenValve();
 }
 else
 {
  DHWValve.CloseValve();
  
  if (digitalRead(UPSTAIRS_DEMAND) == HIGH)     //Upstairs Zone    
    UpstairsValve.OpenValve();
  else
    UpstairsValve.CloseValve();

  if (digitalRead(DOWNSTAIRS_DEMAND) == HIGH)   //Downstairs Zone
    DownstairsValve.OpenValve();
  else
    DownstairsValve.CloseValve();
 }

 #else

 if (digitalRead(HW_DEMAND) == HIGH)     //  Hot Water
    DHWValve.OpenValve();
  else
    DHWValve.CloseValve();

 if (digitalRead(UPSTAIRS_DEMAND) == HIGH)     //Upstairs Zone
    UpstairsValve.OpenValve();
  else
    UpstairsValve.CloseValve();

  if (digitalRead(DOWNSTAIRS_DEMAND) == HIGH)   //Downstairs Zone
    DownstairsValve.OpenValve();
  else
    DownstairsValve.CloseValve();
    
 #endif

  /*
   * Process valve requests
   */
  ProcessValves();

  /*
   * Process Boiler State
   */
  BoilerControl.ProcessState();  
}
