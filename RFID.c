#include<reg51.h> 
sbit rs=P1^0; 
sbit rw=P1^1; 
sbit en=P1^2;
void lcddat(unsigned char); 
void lcdcmd(unsigned char);
void lcddis(unsigned char *); 
void lcd_init();
void serial_init();
void ser_dis(unsigned char *);
void check();
void delay();
unsigned char rfid[13],i;
// Main Function 
void main(){ 
 serial_init();
 lcd_init();
 lcddis(" RFID BASED ");
 lcdcmd(0xc0); 
 lcddis("ATTENDANCE SYSTEM");
 ser_dis("3245FR6786B12 - Ali Sir");
 ser_dis("2018-3-60-050 - Sifat");
 ser_dis("2019-3-60-030 - Noortaz");
 ser_dis("2019-3-60-100 - Samiha");
 while(1){ 
 lcdcmd(0x01);
 lcddis("SWIPE YOUR CARD");
 ser_dis("SWIPE YOUR CARD");
 for(i=0;i<13;i++){
 while(RI==0); 
 rfid[i]=SBUF;
 RI=0;
 SBUF=rfid[i];
 while(TI==0);
 TI=0;
 } 
 check();
 SBUF=0X0D;
 while(TI==0);
 TI=0;
 } 
} 
// Checker Function 
void check(){ 
 if(rfid[0]=='2'&&rfid[1]=='0'&&rfid[2]=='1'&&rfid[3]=='9'&&rfid[4]=='-'&&rfid[5]=='3'&&rfid[6]=='-'&&rfid[7]=='6'&&rfid[8]=='0'&&rfid[9]=='-'&&rfid[10]=='0'&&rfid[11]=='5'&&rfid[12]=='0'){ 
 lcdcmd(0x01);
 lcddis("STUDENT");
 lcdcmd(0xc0);
 lcddis("Sifat - PRESENT");
 ser_dis(" - Sifat PRESENT");
 } 
 else 
if(rfid[0]=='3'&&rfid[1]=='2'&&rfid[2]=='4'&&rfid[3]=='5'&&rfid[4]=='F'&&rfid[5]=='R'&&rfid[6]=='6'&&rfid[7]=='7'&&rfid[8]=='8'&&rfid[9]=='6'&&rfid[10]=='B'&&rfid[11]=='1'&&rfid[12]=='2'){ 
 lcdcmd(0x01);
 lcddis("Sir");
 lcdcmd(0xc0);
 lcddis("Ali Sir - PRESENT");
 ser_dis(" - Ali Sir PRESENT"); 
 } 
 else if(rfid[0]=='2'&&rfid[1]=='0'&&rfid[2]=='1'&&rfid[3]=='9'&&rfid[4]=='-'&&rfid[5]=='3'&&rfid[6]=='-'&&rfid[7]=='6'&&rfid[8]=='0'&&rfid[9]=='-'&&rfid[10]=='0'&&rfid[11]=='3'&&rfid[12]=='0'){ 
 lcdcmd(0x01);
 lcddis("STUDENT");
 lcdcmd(0xc0);
 lcddis("Noortaz - PRESENT");
 ser_dis(" - Noortaz PRESENT");
 } 
 else if(rfid[0]=='2'&&rfid[1]=='0'&&rfid[2]=='1'&&rfid[3]=='9'&&rfid[4]=='-'&&rfid[5]=='3'&&rfid[6]=='-'&&rfid[7]=='6'&&rfid[8]=='0'&&rfid[9]=='-'&&rfid[10]=='1'&&rfid[11]=='0'&&rfid[12]=='0'){ 
 lcdcmd(0x01);
 lcddis("STUDENT");
 lcdcmd(0xc0);
 lcddis("Mithun - PRESENT");
 ser_dis(" - Mithun PRESENT");
 } 
 else{ 
 lcdcmd(0x01);
 lcddis("Not valid");
 lcdcmd(0xc0);
 lcddis("NOT REGISTERED"); 
 ser_dis(" - NOT REGISTERED");
 } 
} 
// LCD initialization function 
void lcd_init(){ 
 lcdcmd(0x38); 
 lcdcmd(0x01);
 lcdcmd(0x10); 
 lcdcmd(0x0c);
 lcdcmd(0x80); 
} 
// LCD common function 
void lcdcmd(unsigned char val){ 
 P2=val;
 rs=0;
 rw=0;
 en=1; 
 delay();
 en=0;
 } 
// LCD data function 
 void lcddat(unsigned char val){ 
 P2=val;
 rs=1;
 rw=0;
 en=1;
 delay();
 en=0;
 } 
// delay or wait function 
void delay(){ 
 unsigned int j;
 for(j=0;j<16000;j++);
} 
// LCD display show function 
void lcddis(unsigned char *s){ 
 unsigned char m;
 for(m=0;s[m]!='\0';m++){
 lcddat(s[m]); } 
} 
// serial initialization function 
void serial_init(){ 
 SCON=0X50; 
 TMOD=0X20; 
 TH1=-3; 
 TR1=1; 
} 
// serial display show function 
void ser_dis(unsigned char *s){ 
 unsigned char v;
 for(v=0;s[v]!='\0';v++){
 SBUF=s[v];
 while(TI==0);
 TI=0;
 } 
 SBUF=0x0d;
 while(TI==0);
 TI=0;
} 
