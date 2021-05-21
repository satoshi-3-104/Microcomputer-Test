/***************************memo***************************
- 使うときは，コメントアウトを外して使ってください．
- 確認できるのは，スイッチ，エンコーダ，モータ，シリンダ―，サーボモータ．
- サーボモータとモータを併用すると振動するので使うときはどちらかをコメントアウトして使ってください．
**********************************************************/

#include "mbed.h"
#include "servo_motor.h"
#include "dc_motor_1.h"
#include "rotary_encoder.h"

#define CONTROL_CYCLE 0.02f

DigitalIn SW(A1); //303スイッチ

/************************************モータの設定************************************/
// dc_motor_1 Motor_1(PB_0, PF_1, 1);     //右前　MD_0
// dc_motor_1 Motor_2(PA_7, PB_5, 1 );    //右前　MD_1
// dc_motor_1 Motor_3(PA_3, PA_1, 1 );    //右前　MD_2

/**********************************エンコーダの設定**********************************/
// rotary_encoder ENC_1(PB_7, PB_6, NC, 512, rotary_encoder::X4_ENCODING);     //ENC_0
// rotary_encoder ENC_2(PB_1, PF_0, NC, 512, rotary_encoder::X4_ENCODING);     //ENC_1
// rotary_encoder ENC_3(PA_9, PA_8, NC, 512, rotary_encoder::X4_ENCODING);     //ENC_2

/*********************************servo_motorの設定**********************************/
// ServoMotor servo(A6, 180.0); //SRV0
// ServoMotor servo(A2, 180.0); //SRV1

/***********************************cylinderの設定***********************************/
// DigitalOut cylinder0(A3); //SOLE0
// DigitalOut cylinder1(A0); //SOLE1

Timer control_ticker;
float motor_cycleout = 0.0f;
int SW_prev;
float servo_degree = 100.0f;
float enco_now[3];

Serial PC(USBTX, USBRX, 115200);

int main()
{
  control_ticker.start();
  for (int i = 0; i < 3; i++)
  {
    enco_now[i] = 0.0f;
  }
  for (;;)
  {
    // hoge_monitor.printf("motor_output %f\r\n", motor_cycleout);
    if (control_ticker.read() >= CONTROL_CYCLE)
    {
      control_ticker.reset();
      if (SW.read() == 0) //スイッチを押すとき
      {
          /******** モーター **********/
          // motor_cycleout = 10.0f;
          /****** servo_motor ********/
          // servo.rot(servo_degree);
          /******* cylinder **********/
          // cylinder0 = 1;
          // cylinder1 = 1; 
      }
      else //スイッチを押さないとき
      {
          /******** モーター **********/
          // motor_cycleout = 10.0f;
          /****** servo_motor ********/
          // servo.rot(servo_degree);
          /******* cylinder **********/
          // cylinder0 = 0;
          // cylinder1 = 0;
      }
      
      /********************* エンコーダー ********************/
      // enco_now[0] = ENC_Mi.getRad(); //ENC_0
      // enco_now[1] = ENC_Mj.getRad(); //ENC_1
      // enco_now[2] = ENC_Mk.getRad(); //ENC_2

      /********************* モーター ************************/
      // Motor_i.drive(motor_cycleout); //MD_0
      // Motor_j.drive(motor_cycleout); //MD_1
      // Motor_k.drive(motor_cycleout); //MD_2

      /********************* エンコーダー ********************/
      // PC.printf("E7==> %f\r\n", ENC_Mi.getRad());
      // PC.printf("E7==> %f\r\n", ENC_Mj.getRad());
      // PC.printf("E7==> %f\r\n", ENC_Mk.getRad());
    } //制御周期
  } //while文
} //main文
