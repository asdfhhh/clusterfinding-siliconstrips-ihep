#include "StdAfx.h"
#include "RandomUser.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

RandomUser::RandomUser(void)
{
	seed = time(NULL);
	srand(seed);
}

RandomUser::~RandomUser(void)
{
}

double RandomUser::Constant(double mean)
{
	return mean;
}

double RandomUser::Uniform(double mean)
{
	//Generate a random number between 0 and 1.
	//REMEMBER: Always cast the oparands of a division to double, or truncation will be performed.
	double R;
	R = ( double)rand()/(double )(RAND_MAX+1);

	return  2*mean*R;
}

double RandomUser::Exponential(double mean)
{
	//Generate a random number between 0 and 1.
	//REMEMBER: Always cast the oparands of a division to double, or truncation will be performed.
	double R;
	R = ( double)rand()/(double )(RAND_MAX+1);

	//Put it as a parameter to the inverse distribution function.
	return  -mean*log(R);
}

int RandomUser::Poisson(int mean)//Special technique required: Box-Muller method...
{
	double R;
	double sum = 0;
	int i;
	i=-1;
	double z;

	while(sum <=mean)
	{

		R = ( double)rand()/(double )(RAND_MAX+1);
		z = -log(R);
		sum+= z;
		i++;
	}
	return i;
}

double RandomUser::Pareto(double alpha)
{
	double R;
	R = ( double)rand()/(double )(RAND_MAX+1);
	return (double )1/(double)(pow(R,( double)1/alpha));
}

double RandomUser::Normal(double mean, double stdev)
{
	double R1;
	R1 = ( double)rand()/(double )(RAND_MAX+1);
	double R2;
	R2 = ( double)rand()/(double )(RAND_MAX+1);
	return mean + stdev*cos(2*3.14*R1)*sqrt(-log(R2));
}

int RandomUser::Geometric(double p)
{
	double R;
	R= ( double)rand()/(double )(RAND_MAX+1);
	return (int )(log(R)/log(1-p) - 1);
}

double RandomUser::Weibull(double scale, double shape)
{
	double R;
	R= ( double)rand()/(double )(RAND_MAX+1);
	return scale*pow(-log(R),(double )1/shape);
}

double RandomUser::Erlang(int scale, double shape) //Special technique required...
{
	double R=1;
	int i;
	for (i=1;i<=scale;i++)
		R = R*(( double)rand()/(double )(RAND_MAX+1));
	return -shape*log(R);
}



int RandomUser::CosmicRandom()
{	
	double cosmic[28]={540,26,0.4,0.4,0.4,2.2,2.2,2.2,0.3,0.3,0.22,0.22,0.19,0.19,0.03,0.03,0.01,0.01,0.02,0.02,0.05,0.05,0.05,0.05,0.05,0.12,0.12,0.12};
	double uni=57595;
	int num=rand()%57595;
	for(int i=0;i<28;i++)
	{
		if(num<(cosmic[i]*100))return i+1;
	}
}
