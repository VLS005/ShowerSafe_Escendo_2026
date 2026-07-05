# Title: ShowerSafe - Smart Fall-Prevention Shower Chair
## Problem Statement: 
Addressing bathroom fall risks for elderly users.

## Solution: 
ShowerSafe is a multi-sensor shower chair for elderly with high fall-risk to minimise chances of a fatal slip/fall in the bathroom.

## How it Works: 
1. **Detection Phase:** An ultrasonic sensor monitors the gap between the user’s back and the chair; a distance beyond the safety threshold signals a forward-leaning posture. Simultaneously, pressure sensors on the base detect uneven weight distribution (e.g., front-heavy loading or side-shifting).
   
2. **Logic Processing:** The Arduino backend performs a "Sensor Fusion" check; if both the ultrasonic and pressure sensors return a "high risk" signal (1), the system confirms a fall is in progress.

3. **Mechanical & Emergency Response:**
   * Secure: Motors at the back of the chair immediately deploy safety handles to lock the user in place.
   * Inform: An I2C display starts a digital timer to track the precise duration of unconsciousness (vital for paramedic assessment).
   * Alert: A loud alarm and emergency strobe light are triggered to summon immediate help from neighbors or caregivers.
   * Impact: Minimized false alarms via multi-sensor cross-verification, providing a robust "fail-safe" for both the elderly and their families.


## Components: 
Sensors: pressure sensor, ultrasonic sensor 

Displays: I2C, LED light 

Microprocessor: ESP-32 

Others: motors 
