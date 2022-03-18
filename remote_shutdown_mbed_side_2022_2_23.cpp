/**
nucleo-f303k8用の遠隔停止プログラム
**/
/**********************************************************************
Include Libraries
**********************************************************************/
#include "mbed.h"
#include <ros.h>
#include <std_msgs/Bool.h>
/**********************************************************************
Declare MACRO
**********************************************************************/
#define CTRL_PERIOD 0.02f
#define Disconnect_Time 0.1f
/**********************************************************************
Proto_type_Declare functions
**********************************************************************/
inline void SetOrder();
inline void emergency_cb(const std_msgs::Bool &msg);
/**********************************************************************
Declare variables
**********************************************************************/
Timer ControlTicker;
Timer LastConnection;
bool order_emergency = 0;
/**********************************************************************
Declare Instances
**********************************************************************/
Serial PC(USBTX, USBRX, 115200);

DigitalOut emergency_switch(PF_1);
AnalogIn current_mater(PB_0);


ros::Subscriber<std_msgs::Bool> sub_emergency("remote_shutdown", &emergency_cb);

int main(int argc, char **argv)
{
  ControlTicker.start();
  LastConnection.start();
  ros::NodeHandle n;
  n.getHardware()->setBaud(460800);
  n.initNode();
  n.subscribe(sub_emergency);

  for (;;)
  {
    if (ControlTicker.read() >= CTRL_PERIOD)
    {
      ControlTicker.reset();
      SetOrder();
      n.spinOnce();
    }
  }
}

inline void SetOrder()
{
  if (LastConnection.read() > Disconnect_Time) emergency_switch = 0;
  else emergency_switch = order_emergency;
}

inline void emergency_cb(const std_msgs::Bool &msg)
{
    order_emergency = msg.data;
    LastConnection.reset();
}
