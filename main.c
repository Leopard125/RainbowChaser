// 左边马达，当IN1=0，IN2=1时为反转。IN1=1，IN2=0时为正转。待机则全为0，刹车则全为1
// 右边马达，当IN3=1，IN4=0时为反转。IN3=0，IN4=1时为正转

// 红外传感器：有信号为1  没有信号为0	 灯亮，没有黑线，灯灭，有黑线
# include <reg51.h>

// 左电机
sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit ENA = P2^2;

// 右电机
sbit IN3 = P2^3;
sbit IN4 = P2^4;
sbit ENB = P2^5;

// 红外传感器
sbit LEFT_2 = P1^3;
sbit LEFT_1 = P1^4;
sbit CENTER = P1^5;
sbit RIGHT_1 = P1^6;
sbit RIGHT_2 = P1^7;

void delay(int t);

// 车的运动状态
void forward(void);
void backward(void);
void right(void);
void left(void);
void idle(void);

// 车传感器的状态
int isLeft(void);
int isRight(void);

void main(void)
{
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
	else if(isLeft()&&isRight()){
		idle();
	}
	else{
		forward();
	}
}

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

void idle()
{// 左停右停
	IN1 = 0;
	IN2 = 0;
	IN3 = 0;	
	IN4 = 0;
}

void delay(int t)
{
	int i,j;
	for(i=0;i<t;i++){
		for(j=0;j<120;j++);	// 1ms
	}
}

int isLeft()
{
	int chk = 0;
	if(RIGHT_1==1 && LEFT_1==0){	 // 右边踩线，左偏
		chk = 1;	
	}else chk = 0;
	return chk;
}

int isRight()
{
	int chk = 0;
	if(RIGHT_1==0 && LEFT_1==1){	 // 左边踩线，右偏
		chk = 1;	
	}else chk = 0;
	return chk;
}


//测试一下git-hwc