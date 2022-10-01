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
#define MYDATA P3
#define data1  P1
#define FL3i 35
#define FL2ii 35
#define FL2i 30
#define FL1ii 30
#define FL1i 25
#define NLii 25
#define NLi 20
#define HL1i 20
#define HL1ii 10
#define HL2i 10
#define HL2ii 00

#define rs P2_0
#define rw P2_1
#define en P2_2
//#define data1 P1
#define rd P2_5
#define wr P2_4
#define INTR P2_3
#define MTR P2_6
#define busy P2_7


//sbit rd=p2_5;
//sbit wr=p2_4;
//sbit INTR=p2_3;

//sbit MTR=p2^6;
//sbit busy=p2^7;

void msdelay(unsigned int value)
{
unsigned int x,y;
for(x=0;x<value;x++)
   for(y=0;y<1275;y++);
   }
void lcdready()
{
busy=1;
rs=0;
rw=1;
while(busy==1)
{
en=0;
en=1;
}
return;
}
void lcdcmd(unsigned char value){
lcdready();
data1=value;
rs=0;
rw=0;
en=1;
en=0;
return;
}
void lcdint(){
lcdcmd(0x38);
lcdcmd(0x0c);
lcdcmd(0x01);
lcdcmd(0x80);
return;
}
void lcddata(char value){
data1=value;
rs=1;
rw=0;
en=1;
en=0;
}
void display(char d1,char d2){
lcddata(d2);
msdelay(30);
msdelay(30);
lcddata(d1);
msdelay(30);
//msdealy();
msdelay(30);
lcddata('c');
}
void convert(char value){
char y,d1,d2,d3;
y=value/10;
d1=value%10;
d2=y%10;
d3=y/10;
d1=d1|0x30;
d2=d2|0x30;
d3=d3|0x30;
display(d1,d2);
}
void update(char value){
char y,d1,d2,d3;
y=value/10;
d1=value%10;
d2=y%10;
d3=y/10;
d1=d1|0x30;
d2=d2|0x30;
d3=d3|0x30;
lcddata(d2);
msdelay(30);
msdelay(30);
lcddata(d1);
	msdelay(30);
msdelay(30);
lcdcmd(0xc0);
}
char adcread(){
char value;
wr=0;
wr=1;
while(INTR==1)
rd=0;
value=data1;
rd=1;
return value;
}
void motorcontrol(){
unsigned char i;
unsigned char value;
unsigned char x[6]="TEMP";
unsigned char x1[6]="FAN ON";
// unsigned char y[12]="SPEED:LEVEL";
//unsigned char u1[5]="NORM";
unsigned char u1[7]="FAN OFF";
//unsigned char x[6]="TEMP";
//unsigned char x1[5]="FAN ON";
// unsigned char y[12]="SPEED:LEVEL";
//unsigned char u1[5]="NORM";
//unsigned char u1[7]="FAN OFF";
while(1){
value=adcread();
while(value>NLi&&value<NLii){
MTR=1;
//lcdcmd(0x01);
for(i=0;i<6;i++){
msdelay(50);
lcddata(x[i]);
}
convert(value);
for(i=0;i<5;i++){
msdelay(30);
lcd(u1[i]);
}
lcdcmd(0xc0);
for(i=0;i<11;i++){
msdelay([30);
lcddata(u2[i]);
}
}
bklbkl;
value=adcread();
if(value>NLi&&value<NLii){
   lcdcmd(0x86);
   update(value);
   goto bklbkl;
}
else
   break;
   }
if(value>=25)
{
    lcdcmd(0x01);
    for(i=0;i<6;i++)
    {
        msdelay(50);
        lcddata(x[i]);
    }
    convert(value);
    lcdcmd(0x8b);
    for(I=0;i<5;i++)
     {
         msdelay(30);
         lcddata(x1[i]);
     }
     while(value>=FL1i && value<FL1ii){
         lcdcmd(0xc0);
         //y[11]='1';
         for(i=0;i<12;i++){
             msdelay(30)
             //lcddata(y[1]);
         }
}
        bkl1;
        MTR=0;
        msdelay(50);
        MTR=1;
        msdelay(50);
        value=adcread;
        if(value>=FL1i && value<FL1ii){
            lcdcmd(0x86);
            update(value);
            goto bkl1;
        }
     else
     break;
    }
    while(value>=FL2i && value<FL2ii){
        //y[11]=2;
        lcdcmd(0xc0)
        for(i=0;i<12;i++){
            msdelay(30);
            lcddata(y[i]);
        }
        bkl2;
        MTR=0;
        msdelay(75);
        MTR=1;
        msdelay(25);
        value=adcread;
        if(value>=FL2i && value<FL2ii){
        lcdcmd(0x86);
        update(value);
        goto bkl2;
    }
    else
    break;
    }
    while(value>=FL3i){
        lcdcmd(0xc0);
        for(i=0;i<12;i++){
            msdelay(30);
            //lcddata(y[i]);
        }
        bkl3;
        MTR=0;
        value=adcread();
        if(value>=FL3i){
            lcdcmd(0x86);
            update(value);
            goto bkl3;
        }
        else
        break;
    }
    
}
void main()
{
 p0=0xff;
 MYDATA=0xff;
 INTR=1;
 rd=1;
 wr=1;
 MTR=1;
 msdelay(50);
 lcdint();
 motorcontrol();
}