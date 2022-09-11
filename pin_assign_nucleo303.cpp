//Nucleo303用メインボード Ver1.1.0 pinアサイン

//DCモーター  宣言時はPWM→DIRの順で書く
#define MD0_PWM D3
#define MD0_DIR D8

#define MD1_PWM A6 //SRV0との同時使用不可
#define MD1_DIR D11

#define MD2_PWM A2 //SRV1との同時使用不可
#define MD2_DIR A1 //SW_PUSH(基板上タクトスイッチ)との同時使用不可

//エンコーダ
#define ENC0_A D4
#define ENC0_B D5

#define ENC1_A D6
#define ENC1_B D7

#define ENC2_A D1 //SW_LIMIT0との同時使用不可
#define ENC2_B D9 //SW_LIMIT1との同時使用不可

//サーボモーター
#define SRV0 A6 //MD1_PWMとの同時使用不可
#define SRV1 A2 //MD2_PWMとの同時使用不可

//ソレノイド (シリンダー)
#define SOLE0 A3
#define SOLE1 A0


//基板上タクトスイッチ
#define SW_PUSH A1 //MD2_DIRとの同時使用不可

//外付けスイッチ  
//!!!! ENC2との同時使用不可 !!!!
#define SW_LIMIT0 D1 //ENC2_Aとの同時使用不可
#define SW_LIMIT1 D9 //ENC2_Bとの同時使用不可
