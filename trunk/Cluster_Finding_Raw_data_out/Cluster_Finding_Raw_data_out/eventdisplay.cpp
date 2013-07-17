{
#include "Constant.h"
	int m_x=MAX_X/1000;
	int m_y=MAX_Y/1000;
	int m_z=-((DET_THICKNESS+DET_DIS)*6/1000)-10;
	string title;
	int charge;
	int x,y,z;
	int count=-1;
	int trigger=0;
	double v_x,v_y,v_z;
	double box_p[3];
	double x0,y0,z0,x1,y1,z1;

	new TGeoManager("world", "detector");

	TGeoMaterial *mat = new TGeoMaterial("Vacuum",0,0,0);
	TGeoMedium   *med = new TGeoMedium("Vacuum",1,mat);
	TGeoVolume *top=gGeoManager->MakeBox("top",med,(m_x)/2+10,(m_y)/2+10,-m_z/2);
	gGeoManager->SetTopVolume(top);

	TGeoTranslation *tr1 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10);
	TGeoVolume *d1  = gGeoManager->MakeBox("d1",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d1->SetLineColor(7);
	top->AddNode(d1,1,tr1);

	TGeoTranslation *tr2 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d2  = gGeoManager->MakeBox("d2",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d2->SetLineColor(7);
	top->AddNode(d2,1,tr2);

	TGeoTranslation *tr3 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-2*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d3  = gGeoManager->MakeBox("d3",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d3->SetLineColor(7);
	top->AddNode(d3,1,tr3);

	TGeoTranslation *tr4 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-3*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d4  = gGeoManager->MakeBox("d4",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d4->SetLineColor(7);
	top->AddNode(d4,1,tr4);

	TGeoTranslation *tr5 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-4*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d5  = gGeoManager->MakeBox("d5",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d5->SetLineColor(7);
	top->AddNode(d5,1,tr5);

	TGeoTranslation *tr6 = new TGeoTranslation((m_x)/2+10,(m_y)/2+10,-m_z/2-10-5*(DET_THICKNESS+DET_DIS)/2000);
	TGeoVolume *d6  = gGeoManager->MakeBox("d6",med,m_x/2,m_y/2,DET_THICKNESS/2000);
	d6->SetLineColor(7);
	top->AddNode(d6,1,tr6);

	TEveManager::Create();
	TGeoNode* node = gGeoManager->GetTopNode();
	TEveGeoTopNode* en = new TEveGeoTopNode(gGeoManager, node);
	en->SetVisLevel(4);
	en->GetNode()->GetVolume()->SetVisibility(kFALSE);
	gEve->AddGlobalElement(en);

	gEve->Redraw3D(kTRUE);
	TEveTrackList *list = new TEveTrackList();
	TEveTrackPropagator* prop = g_prop = list->GetPropagator();
	prop->SetFitDaughters(kFALSE);
	prop->SetMaxZ(1000);
	ifstream fin("truth_data.txt");
	getline(fin,title);


	TEveTrackList *list=0;
	TEveRecTrackD *rc = new TEveRecTrackD();
	TEveTrack* track=0;
	while(fin.good())
	{
		fin>>trigger>>charge>>x>>y>>z>>v_x>>v_y>>v_z;
		x0=x/1000;
		y0=y/1000;
		z0=z/1000;
		rc->fP.Set(v_x, v_y,v_z);
		rc->fV.Set(x0,y0,z0);
		rc->fSign = charge;
		if(trigger!=count)
		{
			if(list)
			{
				list->SetLineColor(kRed);  
				list->MakeTracks();
			}
			count=trigger;
			list= new TEveTrackList();
			TEveTrackPropagator* prop = g_prop = list->GetPropagator();
			prop->SetMagField(0.);
			list->SetName(Form("trigger %d", trigger));
			track= new TEveTrack(rc,prop);
			track->SetName(Form("charge %d", charge));
			list->AddElement(track);
			gEve->AddElement(list);
		}
		else 
		{
			track= new TEveTrack(rc,prop);
			track->SetName(Form("charge %d", charge));
			list->AddElement(track);
			continue;
		}
	} 
	list->SetLineColor(kRed);  
	list->MakeTracks();

	TEveViewer *ev = gEve->GetDefaultViewer();
	TGLViewer  *gv = ev->GetGLViewer();
	gv->SetGuideState(TGLUtil::kAxesOrigin, kTRUE, kFALSE, 0);
	gEve->Redraw3D(kTRUE);
}
