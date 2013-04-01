{
#include "define.h"
	double L=121;
	double D=320;
	int incident=1;
	double ladder_width=STRIP_NUM*L;
	double x0=0;
	double x1=0;
	double start=0;
	double end=0;
	double theta=0;
	double tmp_p=0;
	double tmp_e=0;
	char Hname[50];
	char Tname[50];
	double p[11]={0.035,0.045,0.095,0.115,0.38,1,0.38,0.115,0.095,0.045,0.035};
	double signal[STRIP_NUM];
	int ch;
	int nloop=1000000;
	TRandom2 *rnd=new TRandom2();
	TFile * rootf= new TFile("data.root","RECREATE" );
	TH1I*hitp=new TH1I("hitn","the hit num",20,0,20);
	ofstream fout("trueth.txt");
	TTree*t= new TTree("event" ,"data of event");
	for (int i= 0; i<STRIP_NUM ; i+=2)
	{
		sprintf(Hname, "t_Ch%d",i/2);
		sprintf(Tname, "signal%d/D",i/2);
		t->Branch(Hname,&signal[i],Tname);
		signal[i]=0;
	}

	for(int i=0;i<nloop;i++)
	{
		incident=rnd->Poisson(1);
		hitp->Fill(incident);
		fout<<incident<<"\t";
		for(int jj=0;jj<incident;jj++)
		{
			x0=(rnd->Rndm())*ladder_width;
			fout<<x0<<"\t";
			theta=(rnd->Rndm()-0.5)*2*PI/3;
			x1=tan(theta)*D+x0;
			fout<<x1<<"\t";
			start=(x1>x0 ? x0 : x1);
			start=(start<0? 0:start);
			end=(x1<x0 ? x0 : x1);
			end=(end>ladder_width?ladder_width:end);
			//fill every channel with oringinal ionization
			while(start<end)
			{
				ch=int(start/L);
				tmp_p=((int(start/L)+1)*L<end?(int(start/L)+1)*L:end);
				tmp_e=dEdx*(tmp_p-start)/cos(theta);
				//charge sharing
				for(int ii=-5;ii<6;ii++)
				{
					if(((ch+ii)>-1)&&((ch+ii)<STRIP_NUM))signal[ch+ii]+=p[5+ii]*tmp_e;
				}
				start=tmp_p;
			}
		}
		/*for (int j= 0; j<STRIP_NUM ;j++)
		{
			signal[j]+=rnd->Gaus(0,NOISE);
		}*/
		t->Fill();
		for (int j= 0; j<STRIP_NUM ;j++)
		{
			signal[j]=0;
		}
		fout<<endl;
	}
	fout.close();
	hitp->Write();
	t->Write();
	rootf->Close();
}
