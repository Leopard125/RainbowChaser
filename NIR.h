// 红外传感器部分
# include<reg51.h>

// 红外传感器：有信号为1  没有信号为0	 灯亮，没有黑线，灯灭，有黑线	踩线返回0，没线返回1
sbit LEFT_2 = P1^3;
sbit LEFT_1 = P1^4;
sbit CENTER = P1^5;
sbit RIGHT_1 = P1^6;
sbit RIGHT_2 = P1^7;

int isLeft(void);
int isRight(void);
int isArrive(void);

int isLeft()
{
	int chk = 0;
	if((RIGHT_1==0 || RIGHT_2==0) && (LEFT_1==1 || LEFT_2==1)){	 // 右边踩线，左偏
		chk = 1;	
	}else chk = 0;
	return chk;
}

int isRight()
{
	int chk = 0;
	if((RIGHT_1==1 || RIGHT_2==1) && (LEFT_1==0 || LEFT_2==0)){	 // 左边踩线，右偏
		chk = 1;	
	}else chk = 0;
	return chk;
}

int isArrive()
{
	int chk = 0;
	if(RIGHT_1==0 && LEFT_1==0){
		chk = 1;
	}else chk = 0;
	return chk;
}