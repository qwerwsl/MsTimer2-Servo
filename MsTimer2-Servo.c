/**需要使用MsTimer2库，实现定时器中断
1. 外接按键，有消除抖动功能，按键可计数
2. 每按一次按键，舵机转动10度，完成摆动功能。0-10-20-30---90---170-180-170-160---90---0
3. 随着舵机转动角度的变化，板载LED灯以不同的频率闪烁.
**/
#include<Servo.h>
#include<MsTimer2.h>
Servo myservo;        // 创建一个舵机对象
int pos = 0;        // 舵机转动的角度
int a=0;            //按键的次数
int pushButton= 2; //按键的引脚
int in=1000;
int oos = 0;
//板载LED闪烁
void ggyy()
{
  static int y=0;
  y=1-y;
  digitalWrite(13,y);
}
int tick=0;
//中断服务程序
void onTimer()
{
  Serial.print("timer：");
  Serial.println(tick++);
}
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200); //打开串口
    pinMode( pushButton, INPUT);//设置按钮为输入
    myservo.attach(9);//数字9引脚接舵机
}
void loop() {
  // put your main code here, to run repeatedly:
  int x =digitalRead(pushButton);//读取按钮的状态
  if(x){   //如果按钮状态发生变化
       ++a; 
      if(oos<170){ 
       Serial.println(a);
       pos += 10;
       Serial.println(pos);
       myservo.write(pos);           // 给舵机写入角度   
       delay(500);// 延时500ms让舵机转到指定位置
       MsTimer2::set(in, onTimer); //设置中断，每in(ms)进入一次中断服务程序 onTimer()
       MsTimer2::start(); //开始计时
       in=in-50;
       oos=pos;
        }
      if(oos>=170){
		Serial.println(a);
		pos=pos-10;
		myservo.write(pos);
		delay(500);
		MsTimer2::set(in, ggyy);
		MsTimer2::start();
		in=in+50;
		if(pos==0){
			oos=pos;
				}
			}
		}
	}
