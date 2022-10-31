#include<reg51.h>
sbit  l0=P1^3;
sbit  l50=P1^2;
sbit  l75=P1^1;
sbit  l100=P1^0;

sbit  led0=P2^4;
sbit  led50=P2^3;
sbit  led75=P2^2;
sbit  led100=P2^1;

sbit  buzzer=P2^0;
void delay(int time){
  unsigned int i,j;
  for(i=0;i<time;i++)
    for(j=0;j<1275;j++);
}
void main(){
  while(1){
    P1=0x00;
    P2=0x00;
    buzzer=0;
  if(l0==1 && l50==1 && l75==1 && l100==1){
    led0=1;
    led50=1;
    led75=1;
    led100=1;
    buzzer=1;
    delay(50);
  }
  if(l0==1 && l50==1 && l75==1 && l100==0){
    led0=1;
    led50=1;
    led75=1;
    led100=0;
    buzzer=0;
    delay(50);
  }
  if(l0==1 && l50==1 && l75==0 && l100==0){
    led0=1;
    led50=1;
    led75=0;
    led100=0;
    buzzer=0;
    delay(50);
  }
  if(l0==1 && l50==0 && l75==0 && l100==0){
    led0=1;
    led50=0;
    led75=0;
    led100=0;
    buzzer=0;
    delay(50);
  }
  if(l0==0 && l50==0 && l75==0 && l100==0){
    led0=0;
    led50=0;
    led75=0;
    led100=0;
    buzzer=1;
    delay(50);
  }
  }
}
