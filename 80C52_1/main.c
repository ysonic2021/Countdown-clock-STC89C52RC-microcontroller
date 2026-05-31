#include<reg52.h>
#include "TM1637.h"
#include "intrins.h"
#include <stdio.h>

sfr AUXR = 0X8E;
sfr ISP_CONTR = 0xe7;

sbit KA=P3^2;                //旋转编码器A
sbit KB=P3^3;                //旋转编码器B
sbit KC=P3^6;                //旋转编码器中
bit relay=0;        //时间到标志
sbit com=P0^7;        //蜂鸣器
sbit con=P2^1;  //七彩LED
unsigned char KO=0;  //旋转编码器
char Num=0,Nu=0;                //计时变量
unsigned char hour=0,minute=0,second=0,time_count=0;   //时，分，秒，10ms计数器
unsigned char show[6]={0,0,0,0,0,0}; //TM1637四位数码管显示数组：小时的十位和个位，分钟的十位和个位，最后两个为小时和分钟。
unsigned int Se=0;   //秒计数
unsigned int Kcase=0;//旋转编码器中键按键次数
bit flag_1s=0;                //秒任务标志位
bit flag_500ms=0;        //半秒标志位
bit stat_100ms=0;        //快闪标志位
bit stat_500ms=0;        //半秒状态位，控制闪烁

bit flag=0;                //调整标志位

/******************************
函数说明：延时函数，STC_ISP软件给出 @6MHz 1T单片机
入口参数：us=延时微秒数
出口参数：无
******************************/
void Delay_US(unsigned int us)
{
   while(us--)
   {
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                _nop_();
        }
}//us延时函数结束

void djs(void)   ///////////////////////////////倒计时
{                                
                                if(flag_1s==1)
                                {flag_1s=0;
                                         if(second>0)
                                                {second--;
                                                Se++;
                                                }
                                        else if(minute>0)
                                                {minute--;
                                                second=59;}
                                        else if(hour>0)
                                                {hour--;
                                                minute=59;
                                                second=59;}
                                        else{relay=1;flag=1;}
                                }
                                show[4]=hour;        
                                show[5]=minute;
                            show[0]=show[4]/10%10; //显示的小时十位数
                                show[1]=show[4]%10;           //显示的小时个位数
                                show[2]=show[5]/10%10; //显示的分钟十位数
                                show[3]=show[5]%10;           //显示的分钟个位数
                                                //以下时间到，闪烁显示00
                                 if(relay==1)
                                {               
                                                        con=1;
                                                        if(stat_500ms==0)
                                                        {
                                                         TM1637_display(21,21,21,21,0); //半秒熄灭
                                                                        if(Se==0)
                                                                        {com=1;}
                                                                        else{com=0;}
                                                        }
                                                        else
                                                        {
                                                         TM1637_display(0,0,0,0,1); //半秒显示00:00
                                                        com=1;
                                                        }
                                }        
                                                        
                                else {        com=1;
                                                        con=0;
                                                        if(stat_500ms==0)
                                                        {
                                                         TM1637_display(show[0],show[1],show[2],show[3],stat_500ms); //半秒秒点
                                                        }
                                                        else
                                                        {
                                                         TM1637_display(show[0],show[1],show[2],show[3],stat_500ms); //半秒秒点
                                                        }

                                           }
                        
}

/******************************
函数说明：定时器0初始化，12T自动重装模式，定时10毫秒
******************************/
void Timer0Init(void)        //10毫秒@6.000MHz
{
        AUXR &= 0x7F;                //定时器时钟12T模式
        TMOD &= 0xF0;                //设置定时器模式
        TL0 = 0x78;                        //设置定时初值
        TH0 = 0xEC;                        //设置定时初值
        TF0 = 0;                        //清除TF0标志
        TR0 = 1;                        //定时器0开始计时
        ET0=1;                                //允许T0中断
        EA=1;                                //开全局中断
}//定时器初始化结束

void Zuan()   //旋转处理
{                                            
      switch(Kcase)
                {case 1:
                                                  if((KO==KA)||(KA==1))  //不理会A引脚上升沿，低电平每个脉冲只做一次处理
                                         {
                                 KO=KA;
                                                _nop_();        
                                                _nop_();
                                return;
                                         }                                                         
                                      (KB == 0)?Num-- : Num++;   //根据引脚B的值,判断正反转
                                       KO=KA;    //存储引脚A状态
                                                _nop_();
                                                _nop_();
        
                                                if(Num<0){Num=59;}
                                                 if(Num==60){Num=0;}
                                show[5]=Num;
                            show[0]=show[4]/10%10; //显示的小时十位数
                                show[1]=show[4]%10;           //显示的小时个位数
                                show[2]=show[5]/10%10; //显示的分钟十位数
                                show[3]=show[5]%10;           //显示的分钟个位数
                                minute=Num;
                                break;
                case 2:
                                                  if((KO==KA)||(KA ==1))  //不理会A引脚上升沿，低电平每个脉冲只做一次处理
                                         {
                                 KO=KA;
                                                _nop_();
                                                _nop_();
                                                _nop_();
                                          return;
                                         }                                                         
                                       (KB == 0)?Nu-- : Nu++;   //根据引脚B的值,判断正反转
                                        KO=KA;
                                                 _nop_();
                                                _nop_();
                                                _nop_();//存储引脚A状态
                                                 if(Nu<0){Nu=23;}
                                                 if(Nu==24){Nu=0;}
                                        show[4]=Nu;
                              show[0]=show[4]/10%10; //显示的小时十位数
                                        show[1]=show[4]%10;           //显示的小时个位数
                                        show[2]=show[5]/10%10; //显示的分钟十位数
                                        show[3]=show[5]%10;           //显示的分钟个位数
                                        hour=Nu;
                                        break;
               
                case 3:
                                break;
                }
}




void main(void)
{
        Se=0;
        relay=0;
        flag=0;
        com=1;
        con=1;
          TM1637_display(0,0,0,0,stat_500ms); //上电后默认显示00:00
         Timer0Init();           //定时器T0初始化并启动
        while(1)
        {
        
           
                if(KC==0)/////////////中键检测
                {
                  Delay_US(7000);///////////按键消抖
                if(KC==0)////再次确认中键
                {
                Kcase++;
                if(Kcase==5)
                        {Kcase=1;
                        com=1;
                        con=1;
                        relay=0;
                        flag=0;
                        Num=0;
                        }
        
                }
                }
                switch(Kcase)///////////////////状态选择
                {  case 1:
                                        if(stat_500ms==1)         //半秒闪烁分钟
                                        {
                                        TM1637_display(show[0],show[1],21,21,1); //半秒闪烁分钟
                                        }
                                        else
                                        {
                                         TM1637_display(show[0],show[1],show[2],show[3],1); //半秒闪烁分钟
                                        }
                                       
                          Zuan();                        
                                        break;
                        case 2:
                                        if(stat_500ms==1)         //半秒闪烁小时
                                        {
                                        TM1637_display(show[0],show[1],show[2],show[3],1); //半秒闪烁小时
                                        }
                                        else
                                        {
                                         TM1637_display(21,21,show[2],show[3],1); //半秒闪烁小时
                                        }
                                        Zuan();        
                                        break;
                   case 3:
                                        djs();
                                        break;
                        case 4:
                                        ISP_CONTR=0x20;        //第4按软件复位
                                        break;
                  }        ////////switch状态选择结束
        }//while(1)结束
}//main函数结束



void time0(void) interrupt 1   //T0中断服务，每10ms响应一次
{
                time_count++;                 //计数加1
                if(time_count==55)
                {stat_500ms=~stat_500ms;
                }
                if(time_count==113)
                {time_count=0;
                stat_500ms=~stat_500ms;
                flag_1s=1;
                }
}////////////////////////////////T0中断结束

