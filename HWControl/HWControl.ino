#include <SPI.h>
#include <Controllino.h>
#include "HWControl.h"
#include "valvecontrol.h"
#include "boilercontrol.h"
#include "receiver.h"

//#define HW_PRIORITY
#undef HW_PRIORITY

//Set receiver auto reset
#define RECEIVER_AUTO_RESET 1

/*
* Boiler Control
*/
Boiler BoilerControl(BOILER_CFH);
/*
 * Valve Outputs
 */
Valve UpstairsValve(UPSTAIRS_VALVE, &BoilerControl);
Valve DownstairsValve(DOWNSTAIRS_VALVE, &BoilerControl);
Valve DHWValve(DHW_VALVE, &BoilerControl);

/*
* Receiver Control
*/
Receiver UpstairsRcvr(UPSTAIRS_DEMAND, UPSTAIRS_RCVR_PWR, RECEIVER_AUTO_RESET);
Receiver DownstairsRcvr(DOWNSTAIRS_DEMAND, DOWNSTAIRS_RCVR_PWR, RECEIVER_AUTO_RESET);
Receiver DHWRcvr(HW_DEMAND, HW_DEMAND_RCVR_PWR, RECEIVER_AUTO_RESET);

void setup() {
    return;
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
 
 if (DHWRcvr.iscallingforheat())            //DHW Priority
 {
    UpstairsValve.CloseValve();
    DownstairsValve.CloseValve();
    DHWValve.OpenValve();
 }
 else
 {
  DHWValve.CloseValve();
  
  if (if UpstairsRcvr.iscallingforheat())     //Upstairs Zone    
    UpstairsValve.OpenValve();
  else
    UpstairsValve.CloseValve();

  if (DownstairsRcvr.iscallingforheat())   //Downstairs Zone
    DownstairsValve.OpenValve();
  else
    DownstairsValve.CloseValve();
 }

 #else

 if (DHWRcvr.iscallingforheat())     //  Hot Water
    DHWValve.OpenValve();
  else
    DHWValve.CloseValve();

 if (UpstairsRcvr.iscallingforheat())     //Upstairs Zone
    UpstairsValve.OpenValve();
  else
    UpstairsValve.CloseValve();

  if (DownstairsRcvr.iscallingforheat())   //Downstairs Zone
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
