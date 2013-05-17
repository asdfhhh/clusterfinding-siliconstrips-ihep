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
	//���ǵ�ģ��������һ��TRB�ڣ���������̽���������������40��40cm2��
	//��ʼλ����ȫ����32767��֮һ��Ϊ������λ������̽����λ�ڣ�0��0����400 000��400 000��������
	double precision=double(RAND_MAX+1);
	*x=double(rand())/precision*MAX_X;
	*y=double(rand())/precision*MAX_Y;

}
void Incident_vector::GetDirection(double* vx, double* vy, double* vz)
{
	//��ʼ����Ƕȿ�����z<0��Χ�����
	//����ȡ����precision����󾫶�ΪRAND_MAX 0x7fff 32767
	double precision=double(RAND_MAX+1);
	*vx=double(rand())/(precision/2)-1;
	*vy=double(rand())/(precision/2)-1;
	*vz=double(rand())/(precision/2);
}
