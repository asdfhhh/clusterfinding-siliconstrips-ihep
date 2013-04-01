{
#include "define.h"
	double data_buf[DATA_NUM];
	int ch;
	char filename[50];
	double data_post[DATA_NUM];
	TFile*in=new TFile("data.root");
	int nentries=event->GetEntries();
	cout<<"there are "<<nentries<<" events collected!" <<endl;
	vector<int> cluster_seed;
	TH1F*h[nentries];

	for(int i=0;i<nentries;i++)
	{
		sprintf(filename,"h_%d",i+1 );
		h[i]=new TH1F(filename,"hit",DATA_NUM,0,DATA_NUM);
	}

	for(int i=0;i<DATA_NUM;i++)
	{
		sprintf(filename,"t_Ch%d",i );
		event->SetBranchAddress(filename,&data_buf[i]);
	}

	for(int i=0;i<nentries;i++)
	{
		event->GetEntry(i);
		//zero suppress
		for(int ii=0;ii<DATA_NUM;ii++)
		{
			if(data_buf[ii]>3*NOISE)
			{
				data_post[ii]=data_buf[ii];
				if(data_buf[ii]>5*NOISE)
				{
					if(cluster_seed.empty())cluster_seed.push_back(ii);
					else if((cluster_seed.back()+1)!=ii)cluster_seed.push_back(ii);
				}
			}
			else
#ifdef ZERO_SUPPRESS
				data_post[ii]=0;
#else	
				data_post[ii]=data_buf[ii];
#endif
		}
		for(int ii=0;ii<cluster_seed.size();ii++)
		{
			cout<<"seed "<<ii<<" is "<<cluster_seed[ii]<<endl;
		}
		cluster_seed.clear();
		for(int ii=0;ii<DATA_NUM;ii++)
		{
			if(data_buf[ii]!=0)h[i]->Fill(ii,data_post[ii]);
		}
	}
	//write the results
	TFile*out=new TFile("results.root","RECREATE");
	out->cd();
	for(int i=0;i<nentries;i++)
	{
		h[i]->Write();
	}
}
