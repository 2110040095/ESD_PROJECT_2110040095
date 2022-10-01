// P3_5 as trigger
// p0.7 as buzzer
// P3_2 as echo


/* P0 */
sbit  P0_0=0x80  ;
sbit  P0_1=0x81  ;
sbit  P0_2=0x82  ;
sbit  P0_3=0x83  ;
sbit  P0_4=0x84  ;
sbit  P0_5=0x85  ;
sbit  P0_6=0x86  ;
sbit  P0_7=0x87  ;

/* P1 */
sbit  P1_0=0x90  ;
sbit  P1_1=0x91  ;
sbit  P1_2=0x92  ;
sbit  P1_3=0x93  ;
sbit  P1_4=0x94  ;
sbit  P1_5=0x95  ;
sbit  P1_6=0x96  ;
sbit  P1_7=0x97  ;

/* P2 */
sbit  P2_0=0xA0  ;
sbit  P2_1=0xA1  ;
sbit  P2_2=0xA2  ;
sbit  P2_3=0xA3  ;
sbit  P2_4=0xA4  ;
sbit  P2_5=0xA5  ;
sbit  P2_6=0xA6  ;
sbit  P2_7=0xA7  ;

/*  P3  */
sbit  P3_0=0xB0  ;
sbit  P3_1=0xB1  ;
sbit  P3_2=0xB2  ;
sbit  P3_3=0xB3  ;
sbit  P3_4=0xB4  ;
sbit  P3_5=0xB5  ;
sbit  P3_6=0xB6  ;
sbit  P3_7=0xB7  ;


#include<reg51.h>
#define rs P2_0
#define rw P2_1
#define en P2_2
#define data1 P1
int flag=0;
unsigned char templ,temph,templ1,temph1,num[3];
unsigned int time=0;
unsigned int range=0;
unsigned char t=0,z=0,b=0,m=0;
int i;
void busy()
{
for(t=0;t<40;t++);
return;
}
void lcdsetcommand(unsigned char a)
{
busy();
rs=0;
rw=0;
data1=a;
en=1;
en=0;
return;
}
void lcddisplay(unsigned char x[])
{
rs=1;
rw=0;
for(m=0;x[m]!='\0';m++)
{
busy();
data1=x[m];
en=1;
en=0;
}
return;
}
void lcddisplaychar(unsigned char y)
{
rs=1;
rw=0;
busy();
data1=y;
en=1;
en=0;
}

void delay()
{
	TH1=0x00;
	TL1=0x00;
	TR1=1;
	while(TF1==0);
	TR1=0;
	TF1=0;

}
void delay10us()
{
	TH1=0xFF;
	TL1=0xF6;
	TR1=1;
	while(TF1==0);
	TR1=0;
	TF1=0;
}
void delay1()
{
	for(i=0;i<10;i++)
	{
		delay();
	}
}
void main()
{
	P0_7=0;
	TMOD=0x11;
	P3_5=0;//make trigger 0
	P3_2=1;	 // echo port as input

while(1)
	{
		lcdsetcommand(0x38);
lcdsetcommand(0x0e);
lcdsetcommand(0x06);
lcdsetcommand(0x80);
lcdsetcommand(0x01);
lcddisplay(" DISTANCE: ");
	P2_3=0;	
	P0_7=1;
	TH0=0;
	TL0=0;
	P3_5=1;//give trigger
	delay10us();
	P3_5=0;//make trigger 0 again
  while(P3_2==0);
	TR0=1;
	while(P3_2==1);
	TR0=0;
	P2_3=1;
	TF0=0;
	time=(TH0 << 8) | TL0;
	if(time<35000)
	{
		range=time/59;
	}
	else
	{
		flag=1;
		range=0;
	}
	num[2]=range%10;
	num[1]=(range/10)%10;
	num[0]=(range/10)/10;
	for(z=0;z<3;z++) 
	{
		num[z]=num[z]+0x30;
		lcddisplaychar(num[z]);
	}
	if(range<20&&flag==0)
	{
		P0_7=0;
	}
	delay1();
}
}