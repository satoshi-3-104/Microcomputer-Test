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
//dc_motor_1 Motor_1(PB_0, PF_1, 1);     //右前　MD_0
//dc_motor_1 Motor_2(PA_7, PB_5, 1 );    //右前　MD_1
//dc_motor_1 Motor_3(PA_3, PA_1, 1 );    //右前　MD_2

/**********************************エンコーダの設定**********************************/
//rotary_encoder ENC_1(PB_7, PB_6, NC, 512, rotary_encoder::X4_ENCODING);     //ENC_0
//rotary_encoder ENC_2(PB_1, PF_0, NC, 512, rotary_encoder::X4_ENCODING);     //ENC_1
//rotary_encoder ENC_3(PA_9, PA_8, NC, 512, rotary_encoder::X4_ENCODING);     //ENC_2

/*********************************servo_motorの設定**********************************/
//ServoMotor servo(A6, 180.0); //SRV0
//ServoMotor servo(A2, 180.0); //SRV1

/***********************************cylinderの設定***********************************/
//DigitalOut cylinder0(A3); //SOLE0
//DigitalOut cylinder1(A0); //SOLE1

Timer control_ticker;
float motor_cycleout = 0.0f;
int SW_prev;
float servo_degree = 100.0f;
float enco_now[8];

Serial PC(USBTX, USBRX, 115200);

int main()
{
  control_ticker.start();
  for (int i = 0; i < 8; i++)
  {
    enco_now[i] = 0.0f;
  }
  for (;;)
  {
    //    hoge_monitor.printf("motor_output %f\r\n", motor_cycleout);
    if (control_ticker.read() >= CONTROL_CYCLE)
    {
      control_ticker.reset();
      if (SW.read() == 0)
      {
          //motor_cycleout = 10.0f;
          //servo.rot(servo_degree);
          //cylinder0 = 1;
          //cylinder1 = 1;
        
      } //スイッチを押すとき
      else
      {
          //motor_cycleout = 10.0f;
          //servo.rot(servo_degree);
          //cylinder0 = 0;
          //cylinder1 = 0;
      } //スイッチを押さないとき
        /***********************446*********************/
      // enco_now[0] = gear_ration * ENC_Ma.getRad(); //ENC_0
      // enco_now[1] = gear_ration * ENC_Mb.getRad(); //ENC_1
      // enco_now[2] = gear_ration * ENC_Mc.getRad(); //ENC_2
      // enco_now[3] = gear_ration * ENC_Md.getRad(); //ENC_3
      //    enco_now[4] = gear_ration * ENC_Me.getRad(); //ENC_4
      //    enco_now[5] = gear_ration * ENC_Mf.getRad(); //ENC_5
      //    enco_now[6] = gear_ration * ENC_Mg.getRad(); //ENC_6
      //    enco_now[7] = gear_ration * ENC_Mh.getRad(); //ENC_7
      /***********************303*********************/
      //enco_now[8] = ENC_Mi.getRad() * gear_ration; //ENC_0
      //enco_now[9] = gear_ration * ENC_Mj.getRad(); //ENC_1
      //enco_now[10]= gear_ration * ENC_Mk.getRad(); //ENC_2

      /**********モータ446**********/
       //Motor_a.drive(motor_cycleout); //MD_0
      // Motor_b.drive(motor_cycleout); //MD_1
      // Motor_c.drive(motor_cycleout); //MD_2
      // Motor_d.drive(motor_cycleout); //MD_3
      // Motor_e.drive(motor_cycleout);   //MD_4
      // Motor_f.drive(motor_cycleout);   //MD_5
      // Motor_g.drive(motor_cycleout);   //MD_6
      // Motor_h.drive(motor_cycleout);   //MD_7

      /**********モータ303**********/
       Motor_i.drive(motor_cycleout); //MD_0
      // Motor_j.drive(motor_cycleout); //MD_1
      // Motor_k.drive(motor_cycleout); //MD_2

       //PC.printf("E0==> %f\r\n", ENC_Ma.getRad());
      // PC.printf("E1==> %f\r\n", ENC_Mb.getRad());
       //PC.printf("E2==> %f\r\n", ENC_Mc.getRad());
      // PC.printf("E3==> %f\r\n", ENC_Md.getRad());
      // PC.printf("E4==> %f\r\n", ENC_Me.getRad());
      // PC.printf("E5==> %f\r\n", ENC_Mf.getRad());
      // PC.printf("E6==> %f\r\n", ENC_Mg.getRad());
      //PC.printf("E7==> %f\r\n", ENC_Mh.getRad());
       PC.printf("E7==> %f\r\n", ENC_Mi.getRad());
      // PC.printf("E7==> %f\r\n", ENC_Mj.getRad());
      // PC.printf("E7==> %f\r\n", ENC_Mk.getRad());

    } //制御周期
  }   //while文
} //main文
