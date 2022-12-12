// 马达部分
// 左边马达，当IN1=0，IN2=1时为反转。IN1=1，IN2=0时为正转。待机则全为0，刹车则全为1
// 右边马达，当IN3=1，IN4=0时为反转。IN3=0，IN4=1时为正转
# include <reg51.h>

// 左电机
sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit ENA = P2^2;

// 右电机
sbit IN3 = P2^3;
sbit IN4 = P2^4;
sbit ENB = P2^5;

// 车的运动状态
void forward(void);
void backward(void);
void right(void);
void left(void);
void stop(void);

void delay100ms(int t);

// 先不上PWM
void forward()
{// 左正右正
	IN1 = 1;
	IN2 = 0;
	IN3 = 0;
	IN4 = 1;
}

void right()
{// 左正右停
	IN1 = 1;
	IN2 = 0;
	IN3 = 0;
	IN4 = 0;
}

void left()
{// 左停右正
	IN1 = 0;
	IN2 = 0;
	IN3 = 0;
	IN4 = 1;
}

void backward()
{// 左反右反
	IN1 = 0;
	IN2 = 1;
	IN3 = 1;
	IN4 = 0;
}

void stop()
{
	// 左停右停
	IN1 = 1;
	IN2 = 1;
	IN3 = 1;	
	IN4 = 1;
	delay100ms(100);	   // 停10s
}

void delay100ms(int t)
{
	int i,j;
	for(i=0;i<t;i++){
		for(j=0;j<12000;j++);	// 0.1s
	}
}