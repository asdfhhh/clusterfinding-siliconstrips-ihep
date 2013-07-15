{
#include "define.h"
	double data_buf[DATA_NUM];
	int ch;
	char filename[50];
	double data_post[DATA_NUM];

	ifstream fin("trueth.txt");
	while(!fin.eof())
	{
	}
	//write the results
	TFile*out=new TFile("results.root","RECREATE");
	out->cd();
	for(int i=0;i<nentries;i++)
	{
		h[i]->Write();
	}
}
