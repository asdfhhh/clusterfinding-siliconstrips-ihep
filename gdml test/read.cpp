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
	TGeoManager::Import("DAMPE.gdml");
	gGeoManager->GetVolume("PSDDetector")->SetLineColor(3);
	gGeoManager->GetVolume("ActiveTileY")->SetLineColor(7);
	gGeoManager->GetVolume("ActiveTileX")->SetLineColor(7);
	gGeoManager->GetVolume("STKDetectorX")->SetLineColor(4);
	gGeoManager->GetVolume("STKDetectorY")->SetLineColor(4);
	gGeoManager->GetVolume("ThickConverter")->SetLineColor(5);
	gGeoManager->GetVolume("Converter")->SetLineColor(5);
	gGeoManager->GetVolume("BGODetectorY")->SetLineColor(6);
	gGeoManager->GetVolume("BGODetectorX")->SetLineColor(6);

	gGeoManager->GetVolume("Plane")->SetVisibility(false);
	gGeoManager->GetVolume("PlaneThickW")->SetVisibility(false);
	gGeoManager->GetVolume("PlaneThinW")->SetVisibility(false);
	gGeoManager->GetVolume("PSD")->SetVisibility(false);
	gGeoManager->GetVolume("STK")->SetVisibility(false);
	gGeoManager->GetVolume("BGOLayerX")->SetVisibility(false);
	gGeoManager->GetVolume("BGOLayerY")->SetVisibility(false);
	gGeoManager->GetVolume("BGO")->SetVisibility(false);
	gGeoManager->GetVolume("Payload")->SetVisibility(false);

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
	//gGeoManager->GetVolume("World")->Draw("ogl");
}