#include <Joystick.h>
#include "FlySkyIBus.h"

// Joystick setup object
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 32, 0, true, true, false, false, false, false, true, true, false, false, false);
//                ( HID report ID             Joystick Type,           btn hat  X     Y     Z      Rx     Ry     Rz   Rudd   Thro  Acc   Break  Steer)

void setup()
{
  Joystick.begin(true);
  Serial1.begin(115200);
  IBus.begin(Serial1);
  
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setThrottleRange(0, 1023);
  Joystick.setRudderRange(0, 1023);
}

void loop()
{
  IBus.loop();
  
  // Get iBus values and map to supported ranges
  int roll = map(IBus.readChannel(0), 1000, 2000, 0, 1023);
  int pitch = map(IBus.readChannel(1), 1000, 2000, 0, 1023);
  int throttle = map(IBus.readChannel(2), 1000, 2000, 0, 1023);
  int yaw = map(IBus.readChannel(3), 1000, 2000, 0, 1023);
  int arm = map(IBus.readChannel(4), 1000, 2000, 0, 1023);
  int mode = map(IBus.readChannel(5), 1000, 2000, 0, 1023);



  // Map values to the Joystick object
  Joystick.setXAxis(roll);
  Joystick.setYAxis(pitch);
  Joystick.setThrottle(throttle);
  Joystick.setRudder(yaw);
  if(arm < 512)
  {
    Joystick.setButton(0, 1);
    Joystick.setButton(1, 0);
  }
  else
  {
    Joystick.setButton(0, 0);
    Joystick.setButton(1, 1);
  }

  if(mode < 340)
  {
    Joystick.setButton(2, 1);
    Joystick.setButton(3, 0);
    Joystick.setButton(4, 0);
  }
  else if(mode < 680)
  {
    Joystick.setButton(2, 0);
    Joystick.setButton(3, 1);
    Joystick.setButton(4, 0);
  }
  else
  {
    Joystick.setButton(2, 0);
    Joystick.setButton(3, 0);
    Joystick.setButton(4, 1);
  }
  
}