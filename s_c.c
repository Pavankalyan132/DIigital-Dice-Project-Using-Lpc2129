#include<lpc21xx.h>

#define lcd_d 0xff
#define RS 1<<8
#define E 1<<9
#define sw 15
#define sw1 16

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void delay_ms(unsigned int);
void string(char*);
char arr[10]={0,0,0,0,0,0,0,0,0,0};
int count=0;
int r=0;
int x;


int main(){
	LCD_INIT();
  T0TCR=0x01;
	T0PR=5;
	LCD_CMD(0x80);
	string("* DIGITAL DICE *");

	while(1){
	if(((IOPIN0>>sw)&1)==0){
		LCD_CMD(0x01);
			LCD_CMD(0x80);
	  string("* DIGITAL DICE *");
		LCD_CMD(0xC0);
		string("ROLL-");
		x=T0PC;
		LCD_CMD(0xC5);
	  LCD_DATA(x+49);
		count++;
		LCD_CMD(0xC8);
		string("COUNT-");
		LCD_CMD(0xCE);
		LCD_DATA((count/10)+48);
		LCD_CMD(0xCF);
		LCD_DATA((count%10)+48);
		
		arr[r]=x+1;
		r++;
		if(r==10)
			r=10;
		delay_ms(200);
}

else if(((IOPIN0>>sw1)&1)==0){
	char y=0x8D;
	int i=0;
  LCD_CMD(0x01);
	LCD_CMD(0x80);
	string("HISTORY(10)-");
  while(i<10){
    LCD_CMD(y);
		LCD_DATA(arr[i]+48);
		delay_ms(100);
		i++;
		y=y+2;
		if(y==0x91)
			y=0xC0;
		
}
}
}
}

void LCD_INIT(void){

IODIR0=lcd_d|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	

}


void LCD_CMD(unsigned char cmd){

IOCLR0=lcd_d;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;

}


void LCD_DATA(unsigned char d){

IOCLR0=lcd_d;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;

}

void string(char *s){
while(*s)
	LCD_DATA(*s++);
	
}

/*void delay_ms(unsigned int n){
	int i;
    for(i=0; i < n*6000; i++);
}*/
void delay_ms(unsigned int n){
 // T0TCR=0x02;
  T1PR=15000;
	T1TCR=0x01;
	while(T1TC<n);
	T1TCR=0x03;
	T1TCR=0x00;
	
}