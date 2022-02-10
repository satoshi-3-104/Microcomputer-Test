/***************************memo***************************
- モータ，エンコーダの確認用プログラム．
**********************************************************/
#include "mbed.h"
#include "dc_motor_1.h"
#include "rotary_encoder.h"

#define CONTROL_CYCLE 0.02f

DigitalIn SW(PC_0); //446スイッチ

/******************************モータの設定446*************************************/
//dc_motor_1 Motor_a(PA_1, PC_6, 1);     //MD_0
//dc_motor_1 Motor_b(PA_0, PB_1, 1);     //MD_1
//dc_motor_1 Motor_c(PA_10, PC_7, 1);    //MD_2
//dc_motor_1 Motor_d(PA_11, PC_5, 1);    //MD_3
//dc_motor_1 Motor_e( PB_4, PA_6, 1 );   //MD_4
//dc_motor_1 Motor_f( PB_10, PC_8, 0 );  //MD_5
//dc_motor_1 Motor_g( PA_8, PC_4, 0 );   //MD_6
//dc_motor_1 Motor_h( PB_2, PC_9, 1 );   //MD_7
/*********************************************************************************/

/************************************エンコーダの設定*********************************/
//rotary_encoder ENC_Ma(PA_4,  PC_11, NC, 512, rotary_encoder::X4_ENCODING);    //ENC_0
//rotary_encoder ENC_Mb(PC_1,  PB_0,  NC, 512, rotary_encoder::X4_ENCODING);    //ENC_1
//rotary_encoder ENC_Mc(PC_3,  PC_2,  NC, 512, rotary_encoder::X4_ENCODING);    //ENC_2
//rotary_encoder ENC_Md(PC_10, PC_12, NC, 512, rotary_encoder::X4_ENCODING);    //ENC_3
//rotary_encoder ENC_Me(PB_14, PB_15, NC, 512, rotary_encoder::X4_ENCODING);    //ENC_4
//rotary_encoder ENC_Mf(PB_6,  PA_7,  NC, 512, rotary_encoder::X4_ENCODING);    //ENC_5
//rotary_encoder ENC_Mg(PB_13, PB_5,  NC, 512, rotary_encoder::X4_ENCODING);    //ENC_6
//rotary_encoder ENC_Mh(PB_8,  PB_9,  NC, 512, rotary_encoder::X4_ENCODING);    //ENC_7

Timer control_ticker;
int SW_prev;

Serial PC(USBTX, USBRX, 115200);

int main()
{
  control_ticker.start();
  float motor_cycleout;
  for (;;)
  {
    if (control_ticker.read() >= CONTROL_CYCLE)
    {
      control_ticker.reset();
      if (SW.read() == 0)
      {
         motor_cycleout = 10.0f;
      } //スイッチを押すとき
      else
      {
        motor_cycleout = 0.0f;
      } //スイッチを押さないとき
      /*******************モータ*******************/
      //Motor_a.drive(motor_cycleout); //MD_0
      //Motor_b.drive(motor_cycleout); //MD_1
      //Motor_c.drive(motor_cycleout); //MD_2
      //Motor_d.drive(motor_cycleout); //MD_3
      //Motor_e.drive(motor_cycleout); //MD_4
      //Motor_f.drive(motor_cycleout); //MD_5
      //Motor_g.drive(motor_cycleout); //MD_6
      //Motor_h.drive(motor_cycleout); //MD_7

      /**************エンコーダの値表示**************/
      //PC.printf("E0==> %f\r\n", ENC_Ma.getRad());
      //PC.printf("E1==> %f\r\n", ENC_Mb.getRad());
      //PC.printf("E2==> %f\r\n", ENC_Mc.getRad());
      //PC.printf("E3==> %f\r\n", ENC_Md.getRad());
      //PC.printf("E4==> %f\r\n", ENC_Me.getRad());
      //PC.printf("E5==> %f\r\n", ENC_Mf.getRad());
      //PC.printf("E6==> %f\r\n", ENC_Mg.getRad());
      //PC.printf("E7==> %f\r\n", ENC_Mh.getRad());
    } //制御周期
  }   //while文
} //main文
