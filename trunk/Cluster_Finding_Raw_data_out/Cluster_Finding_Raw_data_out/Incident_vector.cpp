#include "StdAfx.h"
#include "Incident_vector.h"
#include "Constant.h"
Incident_vector::Incident_vector(void)
{
	srand (time(NULL));
}

Incident_vector::~Incident_vector(void)
{
}
void Incident_vector::GetPosition(unsigned int* x,unsigned int* y)
{
	//考虑到模拟限制在一个TRB内，所以整个探测器的面积限制在40×40cm2内
	//初始位置以全长的32767分之一作为步长单位，整个探测器位于（0，0）（400 000，400 000）区间内
	double precision=double(RAND_MAX+1);
	*x=double(rand())/precision*MAX_X;
	*y=double(rand())/precision*MAX_Y;

}
void Incident_vector::GetDirection(double* vx, double* vy, double* vz)
{
	//初始入射角度可以在z<0范围内随机
	//精度取决于precision，最大精度为RAND_MAX 0x7fff 32767
	double precision=double(RAND_MAX+1);
	*vx=double(rand())/(precision/2)-1;
	*vy=double(rand())/(precision/2)-1;
	*vz=double(rand())/(precision/2);
}
