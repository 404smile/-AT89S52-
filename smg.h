#include <REGX51.H>
sbit w = P1^3;
sbit p = P1^2;
unsigned char number[11] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf};
int data_n[4][2];


/////////////////////
//注；程序中ns ====== 南北
//			we =======东西
//          p ======= 代表人行道
//          后面的参数代表性质；例子： p_ns =====南北方向的人行道
//
//
 ///////////////////////////////////////////////////////////////////////////////////////////

void sdelay()		//@12.000MHz
{
	unsigned char i;
	i = 22;
	while (--i);
}
																  //////延时
void delay(unsigned int t)
{
	unsigned char k,i;
	for (;t>0;t--)
	{
		for (i = 2 ;i>0;i--)
		{
			for (k = 250;k>0;k--)
			{;}
		}
	} 

}

////////////////////////////////////////////////////////////////////////////////////////


char decode(int n)
{
	char k2;
	 switch(n)
	 {
	 	case 0: k2 = number[0];return k2;break;
		case 1: k2 = number[1];return k2;break;
		case 2: k2 = number[2];return k2;break;
		case 3: k2 = number[3];return k2;break;							  ////解码模块
		case 4: k2 = number[4];return k2;break;
		case 5: k2 = number[5];return k2;break;
		case 6: k2 = number[6];return k2;break;
		case 7: k2 = number[7];return k2;break;
		case 8: k2 = number[8];return k2;break;
		case 9: k2 = number[9];return k2;break;
		case -1: k2 = number[10];return k2;break;		
	 }
}




///////////////////////////////////////////////////////////////////////////////


void write(int k3,int k4)  /////k3是位置；k4 是值
{
		int i5;
		int i3;
		for (i5 = 1;i5>=0;i5--)
		{	
			{																	////写入模块
			i3 = k4%10;
			k4 = (k4-i3)/10;
			data_n[k3][i5] = i3;
			}	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
int read(int i2,int weix )
{		
		int i4;
		for (i4 = 0;i4<=1;i4++)
		{
			w = 1;P0 = weix;w = 0;sdelay();//delay(400);
			P0 = 0xff;
			p = 1;P0 = decode(data_n[i2][i4]);p = 0;sdelay();//delay(400);						   /////读取模块
			P0 = 0xff;
			weix = weix<<1;
			delay(2);sdelay();	
		}
		return weix;
}
		
/////////////////////////////////////////////////////////////////////////////////////////////////



void smgp(int ns,int p_ns,int we,int p_we,unsigned long int t2)
{
	int wei;
	write(0,ns);
	write(1,p_ns);
	write(2,we);
	write(3,p_we);
	
	for (;t2>0;t2--)
	{
		wei = 0x01;
		wei = read(0,wei);
		wei = read(1,wei);
		wei = read(2,wei);
		wei = read(3,wei);	
	}
}


////24工互1 欧旭军