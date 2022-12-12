// main
# include <reg51.h>
# include <servo.h>
# include <NIR.h>

// void delay(int t);

typedef unsigned char uchar;
typedef unsigned int uint;

#define out P0
sbit E=P1^2;
sbit RW=P1^1;
sbit RS=P1^0;

//12Mhz，83us
void delay(uint j); //延时
void delay_ms(uchar t); //ms级延时
void check_busy(); //查忙
void write_command(uchar com); //写命令
void write_data(uchar wdata); //写数据
void lcd_initial(); //LCD初始化
void string(uchar address,uchar *s); //将字符串显示在LCD的指定位置



// 车传感器的状态

void main(void)
{
	// Init
//	IE = 0x81;	// 启用INT 0中断，捕获stop
//	TCON = 0x01;	// 下降沿触发
	ENA = 1;
	ENB = 1;

	if(isLeft()){
		right();
		string(0x80,"turn right"); //从第一行第一处开始显示（80H + 00H）
		delay(1);
	}
	else if(isRight()){
		left();
		string(0x80,"turn left"); //从第一行第一处开始显示（80H + 00H）
		delay(1);
	}
	else if(isArrive()){
		stop();
		string(0x80,"stop"); //从第一行第一处开始显示（80H + 00H）
		forward();
		string(0x80,"forward"); //从第一行第一处开始显示（80H + 00H）
		delay(500);	 // 直线0.3s，驶离停车区
	}
	else{
		forward();
		string(0x80,"forward"); //从第一行第一处开始显示（80H + 00H）
	}
}

void delay(uint t)
{
	int i,j;
	for(i=0;i<t;i++){
		for(j=0;j<120;j++);	// 1ms
	}
}








// void main(){
	// lcd_initial();
	// while(1){
		// string(0x80,"Hello world!"); //从第一行第一处开始显示（80H + 00H）
		// string(0xc0,"Welcome ZZULI!"); //从第二行第一处开始显示（80H + 40H）
		// delay(100);
	// }
// }



void delay_ms(uchar t){
	uchar j;
	for(;t!=0; t--){
	  for (j=0;j<225;j++);
  }
}

void check_busy(){
	uchar flag=0xff;
	do{
		E=0;
		RS=0;
		RW=1;
		E=1; //E从0到1，上升沿读取，读LCD状态
		flag=out;//从lcd的输出读取状态字
	}while(flag&0x80); //检查BF，直到flag中D7=0，可以进行读写
	E=0;
}

void write_command(uchar com){
	check_busy();
	E=0;
	RS=0;
	RW=0;
	out=com;
	delay_ms(5);
	E=1; //当上升沿到来时，写入状态字
	delay_ms(5);
	E=0;
	delay(1);
}

void write_data(uchar wdata){
	check_busy();
	E=0;
	RS=1;
	RW=0;
	out=wdata;
	delay_ms(5);
	E=1; //当上升沿到来时，写入数据
	delay_ms(5);
	E=0;
	delay(1);
}

void lcd_initial(){
	write_command(0x38);//8位总线,双行显示，5X7的点阵字符
	write_command(0x0C);//开整体显示,光标关，无闪烁  0000_1100
	write_command(0x06);//光标右移  0000_0110
	write_command(0x01);//清屏
	delay(1);
}

// void string(uchar address,uchar *s){
	// write_command(address); //找显示数据RAM地址
	// while(*s>0) write_data(*s++); //循环写入数据
// }

void string(uchar address,uchar *s){
	uchar i=0;
	while(*s!='\0') 
	{
		write_command(address+i); //找显示数据RAM地址
		write_data(*s++); //循环写入数据
		i++;
	}
	i=0;
}