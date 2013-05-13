#pragma once
#include "RandomUser.h"
class Signal
{
public:
	Signal(void);
	~Signal(void);
	RandomUser rnd;
	int x0;
	int y0;
	int x1;
	int y1;
	int weighting;
	int SignalGen(double*);
	void SetStart(int x, int y);
	void SetEnd(int x, int y);
	double LenthCompute(int x_s, int x_e);
	int SetCharge(int charge);
	int AddNoise(double* signal);
};
