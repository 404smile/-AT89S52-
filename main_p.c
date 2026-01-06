#include <REGX51.H>
#include<smg.h>


///////////////////////////////////////////////////////////////////////////////////////////////
//注；程序中ns ====== 南北
//			we =======东西
//          p ======= 代表人行道
//          后面的参数代表性质；例子： p_ns =====南北方向的人行道
//
//
 ///////////////////////////////////////////////////////////////////////////////////////////

int mode_data = 0;
int l3 = 0;
int n[3];
sbit b32 = P3^2;	  //中断1
sbit b33 = P3^3;	  //中断2
sbit b35 = P3^5;	  //确认写入
sbit b36 = P3^6;	  //按键—
sbit b37 = P3^7;	  //按键+




sbit ns_ledr = P2^7;
sbit we_ledr = P2^6;
sbit p_ledr = P2^5;
sbit ns_ledy = P2^4;
sbit we_ledy = P2^3;
sbit ns_ledg = P2^2;
sbit we_ledg = P2^1;
sbit p_ledg = P2^0;





int r = 10;
int y = 5;
int g = 5;
int k1 = 0;
int k2 = 0;
int k3 = 0;
int k4 = 0;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void choose(int wr)
{
	int n_data = 0;
	while(1)
	{
	 	if(b37 == 0 )
		{		
			delay(5);
			if(b37 == 0)
			{
				n_data++;
				if(n_data ==100 ){n_data = 99;}
				while(b37 == 0);
			}
		}
		if(b36 == 0 )
		{
			delay(5);
			if(b36 == 0)
			{
				n_data--;
				if(n_data ==-1 ){n_data = 0;}
				while(b36 == 0);
			}
		}
		if(b35 == 0 )
		{		
			delay(5);										 ////选择红绿灯的时间；
			if(b35 == 0)
			{
				while(b35 == 0);
				break;
			}
		}
		n[wr] = n_data;
		smgp(n[0],n[1],n[2],-11,1);

	}
		
			
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void mode_1()
{		

		
		int i1 = 1;
		int i2 = -1;
		k1 = g;
		k2 = r;
		ns_ledg = 0;p_ledr = 0;
		we_ledr = 0;
		while(mode_data ==0 )
		{
				if(k1 ==0)
			 	{
					//P2 = 0xff;
			 		switch(i1)
					{
						case 1:k1 = y;i1 = 0;ns_ledy = 0;ns_ledr = 1;ns_ledg = 1;break;
						case 0:k1 = r;i1 = -1;ns_ledr = 0;p_ledg = 0;p_ledr = 1;ns_ledy = 1;ns_ledg = 1;break;
						case -1:k1 = g;i1 = 1;ns_ledg = 0;p_ledr = 0;p_ledg = 1;ns_ledy = 1;ns_ledr = 1;break;	
					}
			 	}																/////模式1：红绿灯模式
			 	if(k2 ==0)
			 	{

					//P2 = 0xff;
			 		switch(i2)
					{
						case 1:k2 = y;i2 = 0;we_ledy = 0;we_ledr = 1;we_ledg = 1;break;
						case 0:k2 = r;i2 = -1;we_ledr = 0;we_ledy = 1;we_ledg = 1;break;
						case -1:k2 = g;i2 = 1;we_ledg = 0;we_ledy = 1;we_ledr = 1;break;	
					}
			 	}
				smgp(k1,k1,k2,k2,50);                                      
				k1 --;
				k2 --;
		}
		
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mode_2()
{

	int mode_led = 1;
	while(mode_data == 1)
	{
		if(mode_led ==0)
		{
			P2 =0x1f; 
		}
		if(mode_led == 1)
		{
			P2 = 0xe7;
		}
		if(b37 == 0 )
		{		
			delay(5);
			if(b37 == 0)
			{
				mode_led++;
				if(mode_led ==2 ){mode_led = 1;}
				while(b37 == 0);											  //模式2：谨慎通行，静止通行模式
			}
		}
		if(b36 == 0 )
		{
			delay(5);
			if(b36 == 0)
			{
				mode_led--;
				if(mode_led ==-1 ){mode_led = 0;}
				while(b36 == 0);
			}
		}


	 smgp(-11,-11,-11,-11,1);
	}
	P2 = 0xff;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void mode_3()
{
	while(mode_data == 2)
	{
		choose(0);
		choose(1);
		choose(2);																 ///模式3：编写模式；
		r = n[0];
		y = n[1];
		g = n[2];
		mode_data = 0;
	}		
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void INT_0 () interrupt 0
{
	delay(5);
	if(b32 == 0)
	{	
		mode_data++;
		if( mode_data == 3)
		{
			mode_data = 0;
		}
		while(b32 == 0);
		
	}
}



void INT_1 () interrupt 2
{
	delay(5);
	if(b33 == 0)
	{	
		mode_data--;
		if( mode_data == -1)
		{
			mode_data = 0;
		}
		while(b32 == 0);
		
	}
}



/////////////////////////////////////////////////////////////////////////////////////////





void main()
{

	IT0 =1;
	IT1 = 1;
	EA = 1;
	EX0 = 1;
	EX1 = 1;
	while(1)	
	{
		mode_1(); 
		mode_2();
		mode_3();                                                                        
	 }
	 
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////24工互1  欧旭军
