/**
nucleo-f303k8用の遠隔停止プログラム
**/
/**********************************************************************
Include Libraries
**********************************************************************/
#include "mbed.h"
#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
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
std_msgs::Float32 current_now;
float power_voltage = 3.3; //電流センサの電源電圧
float sensitivity = 0.04; // 1アンペア上がると出力電圧が何ボルト上がるか

float current_ave = 0;
int i = 0;

float magnification = power_voltage/sensitivity;
/**********************************************************************
Declare Instances
**********************************************************************/
Serial PC(USBTX, USBRX, 460800);

DigitalOut emergency_switch(PF_1);
AnalogIn current_sensor(PB_0);


ros::Subscriber<std_msgs::Bool> emergency_sub("remote_shutdown", &emergency_cb);
ros::Publisher current_pub("current_now", &current_now);

int main(int argc, char **argv)
{
  ControlTicker.start();
  LastConnection.start();
  ros::NodeHandle n;
  n.getHardware()->setBaud(460800);
  n.initNode();
  n.subscribe(emergency_sub);

  n.advertise(current_pub);

  for (;;)
  {
    if (ControlTicker.read() >= CTRL_PERIOD)
    {
      ControlTicker.reset();
      SetOrder();
      n.spinOnce();
      current_now.data = (current_sensor-0.5)*magnification*1.453-0.421;
      current_pub.publish(&current_now);
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
