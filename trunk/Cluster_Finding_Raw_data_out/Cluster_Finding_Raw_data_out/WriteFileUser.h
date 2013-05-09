#pragma once
#include "afx.h"
#include <fstream>
using namespace std;
class WriteFileUser
{
public:
	WriteFileUser(void);
	~WriteFileUser(void);
	int OpenDataFile(CString name);
	int OpenTruthFile(CString name);
	int AddData(double* data);
	int AddTruth(int charge,unsigned int x,unsigned int y,double vx, double vy,double vz);
	int CloseDataFile(void);
	int CloseTruth(void);
	ofstream data_out;
	ofstream truth_out;
};
