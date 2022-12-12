// main
# include <reg51.h>
# include <servo.h>
# include <NIR.h>

void delay(int t);

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
		delay(1);
	}
	else if(isRight()){
		left();
		delay(1);
	}
	else if(isArrive()){
		stop();
		forward();
		delay(500);	 // 直线0.3s，驶离停车区
	}
	else{
		forward();
	}
}

void delay(int t)
{
	int i,j;
	for(i=0;i<t;i++){
		for(j=0;j<120;j++);	// 1ms
	}
}