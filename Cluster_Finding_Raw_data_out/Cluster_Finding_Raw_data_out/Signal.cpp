#include "StdAfx.h"
#include "Signal.h"
#include <math.h>
#include "Constant.h"
Signal::Signal(void)
{
}

Signal::~Signal(void)
{
}

int Signal::SignalGen(double* signal)
{	//initial the data
	int ladder_width=MAX_X;
	int start=0;
	int end=0;
	int tmp_p=0;
	double tmp_e=0;
	double p[11]={0.035,0.045,0.095,0.115,0.38,1,0.38,0.115,0.095,0.045,0.035};
	int ch;
	start=(x1>x0 ? x0 : x1);//make sure the start point minimum
	start=(start<0? 0:start);//make sure the start point bigger than 0
	end=(x1<x0 ? x0 : x1);//make sure the end point maximum
	end=(end>ladder_width?ladder_width:end);//make sure the end point smaller than width
	//fill every channel with oringinal ionization
	while(start<end)
	{
		ch=int(start/DET_WIDTH);//find the incident channel
		tmp_p=((int(start/DET_WIDTH)+1)*DET_WIDTH<end?(int(start/DET_WIDTH)+1)*DET_WIDTH:end);//distinguish the end point
		tmp_e=dEdx*LenthCompute(tmp_p,start)*weighting*weighting;//given the delta E
		//charge sharing
		for(int ii=-5;ii<6;ii++)
		{
			if(((ch+ii)>-1)&&((ch+ii)<STRIP_NUM))signal[ch+ii]+=p[5+ii]*tmp_e;
		}
		start=tmp_p;//renew the point
	}
	return 0;
}

void Signal::SetStart(int x, int y)
{
	x0=x;
	y0=y;
}

void Signal::SetEnd(int x, int y)
{
	x1=x;
	y1=y;
}

double Signal::LenthCompute(int x_s, int x_e)
{
	return abs(double((x_e-x_s))*sqrt(double((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1)))/double(x1-x0));
}

int Signal::SetCharge(int charge)
{
	weighting=charge;
	return 0;
}

int Signal::AddNoise(double* signal)
{
	//add noise
	for (int j= 0; j<STRIP_NUM ;j++)
	{
		signal[j]=rnd.Normal(0,NOISE);
	}	
	return 0;
}
