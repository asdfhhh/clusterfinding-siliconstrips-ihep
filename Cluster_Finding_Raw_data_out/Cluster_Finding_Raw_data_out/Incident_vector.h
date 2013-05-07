#pragma once

class Incident_vector
{
public:
	Incident_vector(void);
	~Incident_vector(void);
	void GetPosition(int* x, int* y);
	void GetDirection(double* vx, double* vy, double* vz);
};
