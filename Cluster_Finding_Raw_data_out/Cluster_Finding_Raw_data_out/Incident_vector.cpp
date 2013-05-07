#include "StdAfx.h"
#include "Incident_vector.h"

Incident_vector::Incident_vector(void)
{
	srand (time(NULL));
}

Incident_vector::~Incident_vector(void)
{
}
void Incident_vector::GetPosition(int* x, int* y)
{
	//考虑到模拟限制在一个TRB内，所以整个探测器的面积限制在40×40cm2内
	//初始位置步长以微米作为单位，整个探测器位于（0，0）（400 000，400 000）区间内
	*x=rand()%400000;
	*y=rand()%400000;

}
void Incident_vector::GetDirection(double* vx, double* vy, double* vz)
{
	//初始入射角度可以在z<0范围内随机
	//精度取决于precision，最大精度为RAND_MAX 0x7fff 32767
	int precision=RAND_MAX;
	*vx=(rand()%precision-precision/2)/double(precision/2);
	*vy=(rand()%precision-precision/2)/double(precision/2);
	*vz=(rand()%(precision/2))/double(precision/2);
}
