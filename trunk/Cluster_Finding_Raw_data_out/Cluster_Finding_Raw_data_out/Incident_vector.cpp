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
	//���ǵ�ģ��������һ��TRB�ڣ���������̽���������������40��40cm2��
	//��ʼλ�ò�����΢����Ϊ��λ������̽����λ�ڣ�0��0����400 000��400 000��������
	*x=rand()%400000;
	*y=rand()%400000;

}
void Incident_vector::GetDirection(double* vx, double* vy, double* vz)
{
	//��ʼ����Ƕȿ�����z<0��Χ�����
	//����ȡ����precision����󾫶�ΪRAND_MAX 0x7fff 32767
	int precision=RAND_MAX;
	*vx=(rand()%precision-precision/2)/double(precision/2);
	*vy=(rand()%precision-precision/2)/double(precision/2);
	*vz=(rand()%(precision/2))/double(precision/2);
}
