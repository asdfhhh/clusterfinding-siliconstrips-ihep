{
	gROOT->ProcessLine(".L MultiView.C");
	class MultiView;
	MultiView* gMultiView = 0;

	string title;
	double charge;
	int x,y,z;
	int count=-1;
	UInt_t trigger=0;
	double v_x,v_y,v_z;
	double box_p[3];
	double x0,y0,z0,x1,y1,z1;
	double energy;
	int pdg;
	TBranch        *v_event;
	TBranch        *v_tt_pv_x;
	TBranch        *v_tt_pv_y;
	TBranch        *v_tt_pv_z;
	TBranch        *v_tt_pvpart_px;
	TBranch        *v_tt_pvpart_py;
	TBranch        *v_tt_pvpart_pz;
	TBranch        *v_tt_pvpart_ekin;
	TBranch        *v_tt_pvpart_q;
	TBranch        *v_tt_pvpart_pdg;

	/*TCanvas *c1= new TCanvas("c1","Online monitor",1600,1000);
    gStyle->SetCanvasPreferGL(kTRUE);
	c1->cd();
	c1->SetGrid();*/
	//Draw DAMPE
	TGeoManager::Import("DAMPE.gdml");
	gGeoManager->GetVolume("PSDDetector")->SetLineColor(3);
	gGeoManager->GetVolume("ActiveTileY")->SetLineColor(7);
	gGeoManager->GetVolume("ActiveTileX")->SetLineColor(7);
	gGeoManager->GetVolume("STKDetectorX")->SetLineColor(4);
	gGeoManager->GetVolume("STKDetectorY")->SetLineColor(4);
	gGeoManager->GetVolume("ThickConverter")->SetLineColor(5);
	gGeoManager->GetVolume("Converter")->SetLineColor(5);
	gGeoManager->GetVolume("BGODetectorY")->SetLineColor(9);
	gGeoManager->GetVolume("BGODetectorX")->SetLineColor(9);

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

	gMultiView = new MultiView;

	gMultiView->ImportGeomRPhi(en);
	gMultiView->ImportGeomRhoZ(en);


	//gEve->Redraw3D(kTRUE);
	TEveTrackList *list = new TEveTrackList();
	TEveTrackPropagator* prop = g_prop = list->GetPropagator();
	prop->SetFitDaughters(kFALSE);
	prop->SetMaxZ(1000);
	TEveTrackList *list=0;
	TEveRecTrackD *rc = new TEveRecTrackD();
	TEveTrack* track=0;

	TFile*f=new TFile("DmpSimu.root");
	TTree* t=(TTree*)f->Get("dampe");
	t->SetBranchAddress("tt_event", &trigger, &v_event);

	t->SetBranchAddress("tt_pv_x", &x0, &v_tt_pv_x);
	t->SetBranchAddress("tt_pv_y", &y0, &v_tt_pv_y);
	t->SetBranchAddress("tt_pv_z", &z0, &v_tt_pv_z);

	t->SetBranchAddress("tt_pvpart_px", &v_x, &v_tt_pvpart_px);
	t->SetBranchAddress("tt_pvpart_py", &v_y, &v_tt_pvpart_py);
	t->SetBranchAddress("tt_pvpart_pz", &v_z, &v_tt_pvpart_pz);

	t->SetBranchAddress("tt_pvpart_ekin", &energy, &v_tt_pvpart_ekin);
	t->SetBranchAddress("tt_pvpart_q", &charge, &v_tt_pvpart_q);
	t->SetBranchAddress("tt_pvpart_pdg", &pdg, &v_tt_pvpart_pdg);


	Int_t nentries = (Int_t)t->GetEntries();
   for (Int_t i=0; i<nentries; i++) 
   {
	    t->GetEntry(i);
		rc->fP.Set(v_x, v_y,v_z);
		rc->fV.Set(x0/10,y0/10,z0/10);
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
/*	gGeoManager->GetVolume("World")->Draw();
	c1->Modified();
	c1->Update();
	c1->GetView()->ShowAxis();

	TPolyLine3D *poly=new TPolyLine3D();
	poly->SetPoint(0, x0,y0, z0);
	poly->SetPoint(1, x1,y1, z1);
	poly->SetLineColor(2);
	poly->Draw();
*/
}