{
#include "Constant.h"
	int m_x=MAX_X/1000;
	int m_y=MAX_Y/1000;
	int m_z=-((DET_THICKNESS+DET_DIS)*6/1000)-10;
	string title;
	int charge;
	int x,y,z;
	int trigger=0;
	int count=0;
	double v_x,v_y,v_z;
	double box_p[3];
	double x0,y0,z0,x1,y1,z1;
	int tmp_data;
	/*TParticle*cosmic=new TParticle(22, 1, 0,0,0,0,0,0,0,1,0,0,0,0);*/
	TCanvas *c1= new TCanvas("c1","Online monitor",1600,1000);
	TPad*pad1 = new TPad("pad1","X-Y",0.02,0.51,0.48,0.98,33);
	TPad*pad2 = new TPad("pad2","Y-Z",0.52,0.51,0.98,0.98,33);
	TPad*pad3 = new TPad("pad3","X-Z",0.02,0.02,0.48,0.49,33);
	TPad*pad4 = new TPad("pad4","3D",0.52,0.02,0.98,0.49,33);
	pad1->Range(-10,-10,m_x+10,m_y+10);
	pad2->Range(-10,m_z,m_y+10,20);
	pad3->Range(-10,m_z,m_x+10,20);

	c1->cd();
	c1->SetGrid();
	pad1->Draw();
	pad2->Draw();
	pad3->Draw();
	pad4->Draw();
	//Draw TH2F plot
	pad1->cd();
	TH2F*monitor=new TH2F("monitor","online monitor",3072,0,3072,6,0,6);
	pad1->Modified();
	pad1->Update();

	//Draw Y-Z plot
	TBox*d12= new TBox(0,0,m_y,-DET_THICKNESS/1000);
	d12->SetFillColor(9);
	TBox*d22= new TBox(0,-((DET_THICKNESS+DET_DIS)/1000),m_y,-((DET_THICKNESS+DET_DIS)/1000)-DET_THICKNESS/1000);
	d22->SetFillColor(9);
	TBox*d32= new TBox(0,-((DET_THICKNESS+DET_DIS)*2/1000),m_y,-((DET_THICKNESS+DET_DIS)*2/1000)-DET_THICKNESS/1000);
	d32->SetFillColor(9);
	TBox*d42= new TBox(0,-((DET_THICKNESS+DET_DIS)*3/1000),m_y,-((DET_THICKNESS+DET_DIS)*3/1000)-DET_THICKNESS/1000);
	d42->SetFillColor(9);
	TBox*d52= new TBox(0,-((DET_THICKNESS+DET_DIS)*4/1000),m_y,-((DET_THICKNESS+DET_DIS)*4/1000)-DET_THICKNESS/1000);
	d52->SetFillColor(9);
	TBox*d62= new TBox(0,-((DET_THICKNESS+DET_DIS)*5/1000),m_y,-((DET_THICKNESS+DET_DIS)*5/1000)-DET_THICKNESS/1000);
	d62->SetFillColor(9);
	TText*t3= new TText(0,0,"Y-Z" );
	t3->SetTextColor(12);

	pad2->cd();
	d12->Draw();
	d22->Draw();
	d32->Draw();
	d42->Draw();
	d52->Draw();
	d62->Draw();
	t3->Draw();
	pad2->Modified();
	pad2->Update();

	//Draw X-Z plot
	TBox*d11= new TBox(0,0,m_x,-DET_THICKNESS/1000);
	d11->SetFillColor(9);
	TBox*d21= new TBox(0,-((DET_THICKNESS+DET_DIS)/1000),m_x,-((DET_THICKNESS+DET_DIS)/1000)-DET_THICKNESS/1000);
	d21->SetFillColor(9);
	TBox*d31= new TBox(0,-((DET_THICKNESS+DET_DIS)*2/1000),m_x,-((DET_THICKNESS+DET_DIS)*2/1000)-DET_THICKNESS/1000);
	d31->SetFillColor(9);
	TBox*d41= new TBox(0,-((DET_THICKNESS+DET_DIS)*3/1000),m_x,-((DET_THICKNESS+DET_DIS)*3/1000)-DET_THICKNESS/1000);
	d41->SetFillColor(9);
	TBox*d51= new TBox(0,-((DET_THICKNESS+DET_DIS)*4/1000),m_x,-((DET_THICKNESS+DET_DIS)*4/1000)-DET_THICKNESS/1000);
	d51->SetFillColor(9);
	TBox*d61= new TBox(0,-((DET_THICKNESS+DET_DIS)*5/1000),m_x,-((DET_THICKNESS+DET_DIS)*5/1000)-DET_THICKNESS/1000);
	d61->SetFillColor(9);
	TText*t2= new TText(0,0,"X-Z" );
	t2->SetTextColor(12);

	pad3->cd();
	d11->Draw();
	d21->Draw();
	d31->Draw();
	d41->Draw();
	d51->Draw();
	d61->Draw();
	t2->Draw();
	pad3->Modified();
	pad3->Update();

	//Draw 3D
	pad4->cd();

	new TGeoManager("world", "detector");

	TGeoMaterial *mat = new TGeoMaterial("Vacuum",0,0,0);
	TGeoMedium   *med = new TGeoMedium("Vacuum",1,mat);
	TGeoVolume *top=gGeoManager->MakeBox("top",med,(m_x)/2+10,(m_y)/2+10,-m_z/2);
	gGeoManager->SetTopVolume(top);

	TGeoTranslation *tr1 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10);
	TGeoVolume *d1  = gGeoManager->MakeBox("d1",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d1->SetLineColor(9);
	top->AddNode(d1,1,tr1);

	TGeoTranslation *tr2 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d2  = gGeoManager->MakeBox("d2",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d2->SetLineColor(9);
	top->AddNode(d2,1,tr2);

	TGeoTranslation *tr3 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-2*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d3  = gGeoManager->MakeBox("d3",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d3->SetLineColor(9);
	top->AddNode(d3,1,tr3);

	TGeoTranslation *tr4 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-3*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d4  = gGeoManager->MakeBox("d4",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d4->SetLineColor(9);
	top->AddNode(d4,1,tr4);

	TGeoTranslation *tr5 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-4*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d5  = gGeoManager->MakeBox("d5",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d5->SetLineColor(9);
	top->AddNode(d5,1,tr5);

	TGeoTranslation *tr6 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-5*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d6  = gGeoManager->MakeBox("d6",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d6->SetLineColor(9);
	top->AddNode(d6,1,tr6);

	gGeoManager->SetVisLevel(4);
	top->Draw("ogle");

	ifstream din("data.txt");
	for(int i=0;i<6;i++)
	{
		for(int ii=0;ii<STRIP_NUM;ii++)
		{
			din>>tmp_data;
			monitor->Fill(ii,i,tmp_data);
		}
	}
	pad1->cd();
	monitor->Draw("LEGO2");

	ifstream fin("truth_data.txt");
	getline(fin,title);

	while(fin.good())
	{
		TLine *plotlineY= new TLine(0,0,1,1);
		plotlineY->SetLineColor(46);
		plotlineY->SetLineStyle(4);

		TLine *plotlineX= new TLine(0,0,1,1);
		plotlineX->SetLineColor(46);
		plotlineX->SetLineStyle(4);

		fin>>trigger>>charge>>x>>y>>z>>v_x>>v_y>>v_z;
		x0=x/1000;
		y0=y/1000;
		z0=z/1000;
		x1=-v_x*m_z/v_z+x0;
		y1=-v_y*m_z/v_z+y0;
		z1=m_z;
		plotlineY->SetLineWidth(charge);
		plotlineX->SetLineWidth(charge);

		//Draw Y-Z line
		pad2->cd();
		plotlineY->SetX1(y0);
		plotlineY->SetY1(z0);
		plotlineY->SetX2(y1);
		plotlineY->SetY2(z1);
		plotlineY->Draw();
		pad2->Modified();
		pad2->Update();
		//Draw X-Z line
		pad3->cd();
		plotlineX->SetX1(x0);
		plotlineX->SetY1(z0);
		plotlineX->SetX2(x1);
		plotlineX->SetY2(z1);
		plotlineX->Draw();
		pad3->Modified();
		pad3->Update();
		//Draw 3D
		pad4->cd();
		/*cosmic->SetMomentum(v_x,v_y,v_z,1);
		cosmic->SetProductionVertex(x0-m_x/2,y0-m_y/2,-m_z/2,0);
		gGeoManager->AddTrack(count,22,cosmic);*/
		TPolyLine3D *cosmic = new TPolyLine3D();
		cosmic->SetPoint(0, x0-m_x/2, y0-m_y/2, -m_z/2);
		cosmic->SetPoint(1, x1-m_x/2, y1-m_y/2, z1-m_z/2);
		cosmic->SetLineColor(46);
		cosmic->Draw();

		pad4->Modified();
		pad4->Update();

		cout<<count++<<endl;
		//getchar();
	}
	gGeoManager->CloseGeometry();

}