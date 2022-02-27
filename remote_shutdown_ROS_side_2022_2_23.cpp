/**********************************************************************
遠隔停止プログラム　ROS側
L&Rスティック同時押し込みで通電<->遮断を繰り返す
**********************************************************************/
/**********************************************************************
   Include Libraries
**********************************************************************/
#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <vector>
#include "std_msgs/Bool.h"
#include <sys/stat.h>


/**********************************************************************
   Declare variables(変数宣言)
**********************************************************************/
#define CYCLE_PERIOD 0.02f
#define Disconnect_Time 1.0f
/**ロボ研のコントローラー用
enum MacroesJoyButtons
{ //デジタル値
    BUTTONS_SELECT = 0,
    BUTTONS_STICK_LEFT = 1,
    BUTTONS_STICK_RIGHT = 2,
    BUTTONS_START = 3,
    BUTTONS_CROSS_UP = 4,
    BUTTONS_CROSS_RIGHT = 5,
    BUTTONS_CROSS_DOWN = 6,
    BUTTONS_CROSS_LEFT = 7,
    BUTTONS_L2 = 8,
    BUTTONS_R2 = 9,
    BUTTONS_L1 = 10,
    BUTTONS_R1 = 11,
    BUTTONS_TRIANGLE = 12,
    BUTTONS_CIRCLE = 13,
    BUTTONS_CROSS = 14,
    BUTTONS_SQUARE = 15,
    BUTTONS_PAIRING = 16
};
enum MacroesJoyAxes
{ // アナログ値
    AXES_STICK_LEFT_X = 0,
    AXES_STICK_LEFT_Y = 1,
    AXES_STICK_RIGHT_X = 3,
    AXES_STICK_RIGHT_Y = 4,
    AXES_BUTTON_CROSS_UP = 8,
    AXES_BUTTON_CROSS_RIGHT = 9,
    AXES_BUTTON_CROSS_DOWN = 10,
    AXES_BUTTON_CROSS_LEFT = 11,
    AXES_BUTTON_L2 = 12,
    AXES_BUTTON_R2 = 13,
    AXES_BUTTON_L1 = 14,
    AXES_BUTTON_R1 = 15,
    AXES_BUTTON_TRIANGLE = 16,
    AXES_BUTTON_CIRCLE = 17,
    AXES_BUTTON_CROSS = 18,
    AXES_BUTTON_SQUARE = 19
};

std::vector<int> JoyButtonsArray(17, 0);
std::vector<float> JoyAxesArray(20, 0.0);

**/

//ps4コントローラーの番号を追記
enum MacroesJoyButtons
{ //デジタル値(int)
    BUTTONS_CROSS = 0,
    BUTTONS_CIRCLE = 1,
    BUTTONS_TRIANGLE = 2,
    BUTTONS_SQUARE = 3,
    BUTTONS_L1 = 4,
    BUTTONS_R1 = 5,
    BUTTONS_L2 = 6,
    BUTTONS_R2 = 7,
    BUTTONS_SHARE = 8,
    BUTTONS_OPTIONS = 9,
    BUTTONS_PAIRING = 10,
    BUTTONS_STICK_LEFT = 11,
    BUTTONS_STICK_RIGHT = 12
};
enum MacroesJoyAxes
{ // アナログ値(float)
    AXES_STICK_LEFT_X = 0,
    AXES_STICK_LEFT_Y = 1,
    AXES_BUTTON_L2 = 2,
    AXES_STICK_RIGHT_X = 3,
    AXES_STICK_RIGHT_Y = 4,
    AXES_BUTTON_R2 = 5,
    AXES_BUTTON_CROSS_X = 6,
    AXES_BUTTON_CROSS_Y = 7
};

std::vector<int> JoyButtonsArray(13, 0);
std::vector<float> JoyAxesArray(8, 0.0);


std_msgs::Bool remote_shutdown; /*マイコンに送るremote_shutdownの信号*/
std_msgs::Bool ex_data; /*前回のループでのjoyボタンの状態*/

// float t_start;

/**********************************************************************
  Proto_type_Declare functions
**********************************************************************/
void joy_ps3_Callback(const sensor_msgs::Joy::ConstPtr &joy_msg);

/**********************************************************************
   Main
**********************************************************************/

int main(int argc, char **argv)
{
    ros::init(argc, argv, "remote_shutdown_ROS_side");
    ros::NodeHandle nh;
    ros::Subscriber sub_first = nh.subscribe("joy", 1, joy_ps3_Callback);                       //joyコンの値を受け取る

    ros::Publisher pub_remote_shutdown = nh.advertise<std_msgs::Bool>("remote_shutdown", 10);//
    ros::Rate loop_rate(1.0f / CYCLE_PERIOD);
    
    
    remote_shutdown.data = 0;
    ex_data.data = 1;

    struct stat st;
    const char* file = "/dev/input/js2";
    int ret = stat(file, &st);


    while (ros::ok())
    {
        ros::spinOnce(); //callback関数を読み込む

        /*遠隔停止用*/
        if ((JoyButtonsArray[BUTTONS_STICK_LEFT] && JoyButtonsArray[BUTTONS_STICK_RIGHT]) && ex_data.data == 0){
            remote_shutdown.data =! remote_shutdown.data;
        }
        ROS_INFO("%d", remote_shutdown.data);
        ex_data.data = (JoyButtonsArray[BUTTONS_STICK_LEFT] && JoyButtonsArray[BUTTONS_STICK_RIGHT]);


        ret = stat(file, &st);
        if (0 != ret) {
            remote_shutdown.data = 0;
            ROS_INFO("lost.reset");
            std::cout << "Not Exist!" << std::endl;
        }
        else std::cout << "Exist!" << std::endl;

        pub_remote_shutdown.publish(remote_shutdown);

        loop_rate.sleep();
    }
    return 0;
}

/**********************************************************************
   Functions <Call Back>
**********************************************************************/

void joy_ps3_Callback(const sensor_msgs::Joy::ConstPtr &joy_msg)
{
    JoyButtonsArray = joy_msg->buttons;
    JoyAxesArray = joy_msg->axes;
}
