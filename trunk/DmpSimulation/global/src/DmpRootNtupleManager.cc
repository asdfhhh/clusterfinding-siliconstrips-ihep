// Description: manager for output data to a ROOT ntuple
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpRootNtupleManager.hh"
#include "G4UnitsTable.hh"

#include "G4TrajectoryContainer.hh"
#include "G4VTrajectoryPoint.hh"
#include "G4VTrajectory.hh"
#include "G4Trajectory.hh"
#include "G4VProcess.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"

#include "DmpDetectorConstruction.hh"
#include "DmpSimuBgoHit.hh"
#include "DmpSimuStkHit.hh"
#include "DmpSimuStkDigi.hh"
#include "DmpSimuStkDigitizer.hh"

#include "G4RunManager.hh"
#include "G4DigiManager.hh"

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"

DmpRootNtupleManager::DmpRootNtupleManager()
:rootFile(0),tree(0)
{
      
  // ntuple
  tree = 0;

  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event

}

DmpRootNtupleManager::~DmpRootNtupleManager()
{
  if ( rootFile ) delete rootFile;
}

void DmpRootNtupleManager::book()
{ 
 
 // Creating a tree container to handle histograms and ntuples.
 // This tree is associated to an output file.
 //
 G4String fileName = "DmpSimu.root";
 rootFile = new TFile(fileName,"RECREATE");
 if(!rootFile) {
   G4cout << " DmpRootNtupleManager::book :" 
          << " problem creating the ROOT TFile "
          << G4endl;
   return;
 }
 G4cout << "\n----> Output ntuple file is opened in " << fileName << G4endl;

 // create 1 ntuple in subdirectory "tuples"
 tree = new TTree("dampe", "dampe tracker");

 //book ntuple branches and define ntuple data vectors here 
 tree->Branch("tt_run",       &tt_run,     "tt_run/i"  );
 tree->Branch("tt_event",     &tt_event,   "tt_event/i");
 tree->Branch("tt_npv",       &tt_npv,     "tt_npv/i"  );
 //tree->Branch("tt_npvpart",   &tt_npv,     "tt_npvpart/i");

 tree->Branch("tt_cal_totE",         &tt_cal_totE);
 tree->Branch("tt_cal_totE_1MeV",    &tt_cal_totE_1MeV);
 tree->Branch("tt_cal_totE_10MeV",   &tt_cal_totE_10MeV);

 tree->Branch("tt_pv_x",      &tt_pv_x);
 tree->Branch("tt_pv_y",      &tt_pv_y);
 tree->Branch("tt_pv_z",      &tt_pv_z);
 tree->Branch("tt_pvpart_px", &tt_pvpart_px  );
 tree->Branch("tt_pvpart_py", &tt_pvpart_py  );
 tree->Branch("tt_pvpart_pz", &tt_pvpart_pz  );
 tree->Branch("tt_pvpart_ekin",&tt_pvpart_ekin);
 tree->Branch("tt_pvpart_q",  &tt_pvpart_q   );
 tree->Branch("tt_pvpart_pdg",&tt_pvpart_pdg );

 tree->Branch("tt_pvtrj_trackID",    &tt_pvtrj_trackID);
 tree->Branch("tt_pvtrj_stop_vo",    &tt_pvtrj_stop_vo);
 tree->Branch("tt_pvtrj_stop_index", &tt_pvtrj_stop_index);
 tree->Branch("tt_pvtrj_stop_x", &tt_pvtrj_stop_x);
 tree->Branch("tt_pvtrj_stop_y", &tt_pvtrj_stop_y);
 tree->Branch("tt_pvtrj_stop_z", &tt_pvtrj_stop_z);
 /***
 tree->Branch("tt_back_pdg",  &tt_back_pdg  );
 tree->Branch("tt_back_px",  &tt_back_px  );
 tree->Branch("tt_back_py",  &tt_back_py  );
 tree->Branch("tt_back_pz",  &tt_back_pz  );
 tree->Branch("tt_back_ekin",&tt_back_ekin);
 tree->Branch("tt_back_trackID",    &tt_back_trackID);
 tree->Branch("tt_back_parentID",   &tt_back_parentID);
 tree->Branch("tt_back_stop_vo",    &tt_back_stop_vo);
 tree->Branch("tt_back_stop_index", &tt_back_stop_index);
 tree->Branch("tt_back_stop_x",  &tt_back_stop_x);
 tree->Branch("tt_back_stop_y",  &tt_back_stop_y);
 tree->Branch("tt_back_stop_z",  &tt_back_stop_z);
 ***/
 tree->Branch("tt_ele_px",  &tt_ele_px  );
 tree->Branch("tt_ele_py",  &tt_ele_py  );
 tree->Branch("tt_ele_pz",  &tt_ele_pz  );
 tree->Branch("tt_ele_ekin",&tt_ele_ekin);
 tree->Branch("tt_ele_trackID",    &tt_ele_trackID);
 tree->Branch("tt_ele_parentID",   &tt_ele_parentID);
 tree->Branch("tt_ele_stop_vo",    &tt_ele_stop_vo);
 tree->Branch("tt_ele_stop_index", &tt_ele_stop_index);
 tree->Branch("tt_ele_stop_x",  &tt_ele_stop_x);
 tree->Branch("tt_ele_stop_y",  &tt_ele_stop_y);
 tree->Branch("tt_ele_stop_z",  &tt_ele_stop_z);

 tree->Branch("tt_pos_px",  &tt_pos_px  );
 tree->Branch("tt_pos_py",  &tt_pos_py  );
 tree->Branch("tt_pos_pz",  &tt_pos_pz  );
 tree->Branch("tt_pos_ekin",&tt_pos_ekin);
 tree->Branch("tt_pos_trackID",    &tt_pos_trackID);
 tree->Branch("tt_pos_parentID",   &tt_pos_parentID);
 tree->Branch("tt_pos_stop_vo",    &tt_pos_stop_vo);
 tree->Branch("tt_pos_stop_index", &tt_pos_stop_index);
 tree->Branch("tt_pos_stop_x",  &tt_pos_stop_x);
 tree->Branch("tt_pos_stop_y",  &tt_pos_stop_y);
 tree->Branch("tt_pos_stop_z",  &tt_pos_stop_z);

 tt_stepping_ntracks = 0;
 tt_stepping_trackID        = new std::vector<int>();
 tt_stepping_trackPDG       = new std::vector<int>();
 tt_stepping_parentID       = new std::vector<int>();
 /***
 tree->Branch("tt_stepping_ntracks",  &tt_stepping_ntracks, "tt_stepping_ntracks/i");
 tree->Branch("tt_stepping_trackID",  &tt_stepping_trackID);
 tree->Branch("tt_stepping_trackPDG", &tt_stepping_trackPDG);
 tree->Branch("tt_stepping_parentID", &tt_stepping_parentID);
 ***/
 tt_pvtrack_nsteps = 0;    
 tt_step_pvtrack_px       = new std::vector<double>();
 tt_step_pvtrack_py       = new std::vector<double>();
 tt_step_pvtrack_pz       = new std::vector<double>();
 tt_step_pvtrack_ekin     = new std::vector<double>();
 tt_step_pvtrack_x        = new std::vector<double>();
 tt_step_pvtrack_y        = new std::vector<double>();
 tt_step_pvtrack_z        = new std::vector<double>();
 tt_step_pvtrack_stepLength       = new std::vector<double>();
 tt_step_pvtrack_trackLength      = new std::vector<double>();
 tt_step_pvtrack_energyDeposit    = new std::vector<double>();
 tt_step_pvtrack_stepNumber       = new std::vector<int>();
 tt_step_pvtrack_isEntering       = new std::vector<G4bool>();
 tt_step_pvtrack_thisVolume       = new std::vector<std::string>();
 tt_step_pvtrack_nextVolume       = new std::vector<std::string>();
 tt_step_pvtrack_thisIndex        = new std::vector<int>();
 tt_step_pvtrack_nextIndex        = new std::vector<int>();
 
 tree->Branch("tt_pvtrack_nsteps",         &tt_pvtrack_nsteps, "tt_pvtrack_nsteps/i"  );
 tree->Branch("tt_step_pvtrack_px",        &tt_step_pvtrack_px);
 tree->Branch("tt_step_pvtrack_py",        &tt_step_pvtrack_py);
 tree->Branch("tt_step_pvtrack_pz",        &tt_step_pvtrack_pz);
 tree->Branch("tt_step_pvtrack_ekin",      &tt_step_pvtrack_ekin);
 tree->Branch("tt_step_pvtrack_x",         &tt_step_pvtrack_x);
 tree->Branch("tt_step_pvtrack_y",         &tt_step_pvtrack_y);
 tree->Branch("tt_step_pvtrack_z",         &tt_step_pvtrack_z);
 tree->Branch("tt_step_pvtrack_stepLength",    &tt_step_pvtrack_stepLength);
 tree->Branch("tt_step_pvtrack_trackLength",   &tt_step_pvtrack_trackLength);
 tree->Branch("tt_step_pvtrack_energyDeposit", &tt_step_pvtrack_energyDeposit);
 tree->Branch("tt_step_pvtrack_stepNumber",    &tt_step_pvtrack_stepNumber);
 tree->Branch("tt_step_pvtrack_isEntering",    &tt_step_pvtrack_isEntering);
 tree->Branch("tt_step_pvtrack_thisVolume",    &tt_step_pvtrack_thisVolume);
 tree->Branch("tt_step_pvtrack_nextVolume",    &tt_step_pvtrack_nextVolume);
 tree->Branch("tt_step_pvtrack_thisIndex",     &tt_step_pvtrack_thisIndex);
 tree->Branch("tt_step_pvtrack_nextIndex",     &tt_step_pvtrack_nextIndex);

 tt_back_nsteps = 0;    
 tt_step_back_trackID  = new std::vector<int>();
 tt_step_back_pdg      = new std::vector<int>();
 tt_step_back_px       = new std::vector<double>();
 tt_step_back_py       = new std::vector<double>();
 tt_step_back_pz       = new std::vector<double>();
 tt_step_back_ekin     = new std::vector<double>();
 tt_step_back_x        = new std::vector<double>();
 tt_step_back_y        = new std::vector<double>();
 tt_step_back_z        = new std::vector<double>();
 tt_step_back_stepLength       = new std::vector<double>();
 tt_step_back_trackLength      = new std::vector<double>();
 tt_step_back_energyDeposit    = new std::vector<double>();
 tt_step_back_stepNumber       = new std::vector<int>();
 tt_step_back_isEntering       = new std::vector<G4bool>();
 tt_step_back_thisVolume       = new std::vector<std::string>();
 tt_step_back_nextVolume       = new std::vector<std::string>();
 tt_step_back_thisIndex        = new std::vector<int>();
 tt_step_back_nextIndex        = new std::vector<int>();

 tree->Branch("tt_back_nsteps",    &tt_back_nsteps,   "tt_back_nsteps/i"  );
 tree->Branch("tt_step_back_trackID",   &tt_step_back_trackID);
 tree->Branch("tt_step_back_pdg",       &tt_step_back_pdg);
 tree->Branch("tt_step_back_px",        &tt_step_back_px);
 tree->Branch("tt_step_back_py",        &tt_step_back_py);
 tree->Branch("tt_step_back_pz",        &tt_step_back_pz);
 tree->Branch("tt_step_back_ekin",      &tt_step_back_ekin);
 tree->Branch("tt_step_back_x",         &tt_step_back_x);
 tree->Branch("tt_step_back_y",         &tt_step_back_y);
 tree->Branch("tt_step_back_z",         &tt_step_back_z);
 tree->Branch("tt_step_back_stepLength",    &tt_step_back_stepLength);
 tree->Branch("tt_step_back_trackLength",   &tt_step_back_trackLength);
 tree->Branch("tt_step_back_energyDeposit", &tt_step_back_energyDeposit);
 tree->Branch("tt_step_back_stepNumber",    &tt_step_back_stepNumber);
 tree->Branch("tt_step_back_isEntering",    &tt_step_back_isEntering);
 tree->Branch("tt_step_back_thisVolume",    &tt_step_back_thisVolume);
 tree->Branch("tt_step_back_nextVolume",    &tt_step_back_nextVolume);
 tree->Branch("tt_step_back_thisIndex",     &tt_step_back_thisIndex);
 tree->Branch("tt_step_back_nextIndex",     &tt_step_back_nextIndex);

 tt_ele_nsteps = 0;    
 tt_step_ele_px       = new std::vector<double>();
 tt_step_ele_py       = new std::vector<double>();
 tt_step_ele_pz       = new std::vector<double>();
 tt_step_ele_ekin     = new std::vector<double>();
 tt_step_ele_x        = new std::vector<double>();
 tt_step_ele_y        = new std::vector<double>();
 tt_step_ele_z        = new std::vector<double>();
 tt_step_ele_stepLength       = new std::vector<double>();
 tt_step_ele_trackLength      = new std::vector<double>();
 tt_step_ele_energyDeposit    = new std::vector<double>();
 tt_step_ele_stepNumber       = new std::vector<int>();
 tt_step_ele_isEntering       = new std::vector<G4bool>();
 tt_step_ele_thisVolume       = new std::vector<std::string>();
 tt_step_ele_nextVolume       = new std::vector<std::string>();
 tt_step_ele_thisIndex        = new std::vector<int>();
 tt_step_ele_nextIndex        = new std::vector<int>();

 tree->Branch("tt_ele_nsteps",    &tt_ele_nsteps,   "tt_ele_nsteps/i"  );
 tree->Branch("tt_step_ele_px",        &tt_step_ele_px);
 tree->Branch("tt_step_ele_py",        &tt_step_ele_py);
 tree->Branch("tt_step_ele_pz",        &tt_step_ele_pz);
 tree->Branch("tt_step_ele_ekin",      &tt_step_ele_ekin);
 tree->Branch("tt_step_ele_x",         &tt_step_ele_x);
 tree->Branch("tt_step_ele_y",         &tt_step_ele_y);
 tree->Branch("tt_step_ele_z",         &tt_step_ele_z);
 //tree->Branch("tt_step_ele_stepLength",    &tt_step_ele_stepLength);
 //tree->Branch("tt_step_ele_trackLength",   &tt_step_ele_trackLength);
 tree->Branch("tt_step_ele_energyDeposit", &tt_step_ele_energyDeposit);
 tree->Branch("tt_step_ele_stepNumber",    &tt_step_ele_stepNumber);
 tree->Branch("tt_step_ele_isEntering",    &tt_step_ele_isEntering);
 tree->Branch("tt_step_ele_thisVolume",    &tt_step_ele_thisVolume);
 tree->Branch("tt_step_ele_nextVolume",    &tt_step_ele_nextVolume);
 tree->Branch("tt_step_ele_thisIndex",     &tt_step_ele_thisIndex);
 tree->Branch("tt_step_ele_nextIndex",     &tt_step_ele_nextIndex);

 tt_pos_nsteps = 0;    
 tt_step_pos_px       = new std::vector<double>();
 tt_step_pos_py       = new std::vector<double>();
 tt_step_pos_pz       = new std::vector<double>();
 tt_step_pos_ekin     = new std::vector<double>();
 tt_step_pos_x        = new std::vector<double>();
 tt_step_pos_y        = new std::vector<double>();
 tt_step_pos_z        = new std::vector<double>();
 tt_step_pos_stepLength       = new std::vector<double>();
 tt_step_pos_trackLength      = new std::vector<double>();
 tt_step_pos_energyDeposit    = new std::vector<double>();
 tt_step_pos_stepNumber       = new std::vector<int>();
 tt_step_pos_isEntering       = new std::vector<G4bool>();
 tt_step_pos_thisVolume       = new std::vector<std::string>();
 tt_step_pos_nextVolume       = new std::vector<std::string>();
 tt_step_pos_thisIndex        = new std::vector<int>();
 tt_step_pos_nextIndex        = new std::vector<int>();

 tree->Branch("tt_pos_nsteps",    &tt_pos_nsteps,   "tt_pos_nsteps/i"  );
 tree->Branch("tt_step_pos_px",        &tt_step_pos_px);
 tree->Branch("tt_step_pos_py",        &tt_step_pos_py);
 tree->Branch("tt_step_pos_pz",        &tt_step_pos_pz);
 tree->Branch("tt_step_pos_ekin",      &tt_step_pos_ekin);
 tree->Branch("tt_step_pos_x",         &tt_step_pos_x);
 tree->Branch("tt_step_pos_y",         &tt_step_pos_y);
 tree->Branch("tt_step_pos_z",         &tt_step_pos_z);
 tree->Branch("tt_step_pos_stepLength",    &tt_step_pos_stepLength);
 tree->Branch("tt_step_pos_trackLength",   &tt_step_pos_trackLength);
 tree->Branch("tt_step_pos_energyDeposit", &tt_step_pos_energyDeposit);
 tree->Branch("tt_step_pos_stepNumber",    &tt_step_pos_stepNumber);
 tree->Branch("tt_step_pos_isEntering",    &tt_step_pos_isEntering);
 tree->Branch("tt_step_pos_thisVolume",    &tt_step_pos_thisVolume);
 tree->Branch("tt_step_pos_nextVolume",    &tt_step_pos_nextVolume);
 tree->Branch("tt_step_pos_thisIndex",     &tt_step_pos_thisIndex);
 tree->Branch("tt_step_pos_nextIndex",     &tt_step_pos_nextIndex);

 tt_CalLayer_nlayer = 0;    
 tt_CalLayer_centroid   = new std::vector<double>();
 tt_CalLayer_e          = new std::vector<double>();
 tt_CalLayer_sumw2      = new std::vector<double>();
 tt_CalLayer_index      = new std::vector<int>();

 tree->Branch("tt_CalLayer_nlayer",    &tt_CalLayer_nlayer,   "tt_CalLayer_nlayer/i"  );
 tree->Branch("tt_CalLayer_centroid",  &tt_CalLayer_centroid);
 tree->Branch("tt_CalLayer_e",         &tt_CalLayer_e);
 tree->Branch("tt_CalLayer_sumw2",     &tt_CalLayer_sumw2);
 tree->Branch("tt_CalLayer_index",     &tt_CalLayer_index);

 tt_CalLayer_nlayer_1MeV = 0;    
 tt_CalLayer_centroid_1MeV   = new std::vector<double>();
 tt_CalLayer_e_1MeV          = new std::vector<double>();
 tt_CalLayer_sumw2_1MeV      = new std::vector<double>();
 tt_CalLayer_index_1MeV      = new std::vector<int>();

 tree->Branch("tt_CalLayer_nlayer_1MeV",    &tt_CalLayer_nlayer_1MeV,   "tt_CalLayer_nlayer_1MeV/i"  );
 tree->Branch("tt_CalLayer_centroid_1MeV",  &tt_CalLayer_centroid_1MeV);
 tree->Branch("tt_CalLayer_e_1MeV",         &tt_CalLayer_e_1MeV);
 tree->Branch("tt_CalLayer_sumw2_1MeV",     &tt_CalLayer_sumw2_1MeV);
 tree->Branch("tt_CalLayer_index_1MeV",     &tt_CalLayer_index_1MeV);

 tt_SiHit_n = 0;
 tt_SiHit_id = new std::vector<int>();
 tt_SiHit_strip = new std::vector<int>();
 tt_SiHit_trackID  = new std::vector<unsigned int>();
 tt_SiHit_trackID1 = new std::vector<unsigned int>();
 tt_SiHit_trackID2 = new std::vector<unsigned int>();
 tt_SiHit_ntracks     = new std::vector<int>();
 tt_SiHit_ntracksBack = new std::vector<int>();
 tt_SiHit_ntracksPrim = new std::vector<int>();
 tt_SiHit_e     = new std::vector<double>();
 tt_SiHit_e_prim= new std::vector<double>();
 tt_SiHit_x     = new std::vector<double>();
 tt_SiHit_y     = new std::vector<double>();
 tt_SiHit_z     = new std::vector<double>();

 tree->Branch("tt_SiHit_n",      &tt_SiHit_n,   "tt_SiHit_n/i"  );
 tree->Branch("tt_SiHit_strip",  &tt_SiHit_strip);
 tree->Branch("tt_SiHit_id",     &tt_SiHit_id);
 tree->Branch("tt_SiHit_trackID",&tt_SiHit_trackID);
 tree->Branch("tt_SiHit_trackID1",&tt_SiHit_trackID1);
 tree->Branch("tt_SiHit_trackID2",&tt_SiHit_trackID2);
 tree->Branch("tt_SiHit_ntracks",&tt_SiHit_ntracks);
 tree->Branch("tt_SiHit_ntracksBack",&tt_SiHit_ntracksBack);
 tree->Branch("tt_SiHit_ntracksPrim",&tt_SiHit_ntracksPrim);
 tree->Branch("tt_SiHit_e",      &tt_SiHit_e);
 tree->Branch("tt_SiHit_e_prim", &tt_SiHit_e_prim);
 tree->Branch("tt_SiHit_x",      &tt_SiHit_x);
 tree->Branch("tt_SiHit_y",      &tt_SiHit_y);
 tree->Branch("tt_SiHit_z",      &tt_SiHit_z);
 
 tt_SiDigit_n = 0;
 tt_SiDigit_strip   = new std::vector<int>();
 tt_SiDigit_trackID = new std::vector<unsigned int>();
 tt_SiDigit_e       = new std::vector<double>();
 tt_SiDigit_e_prim  = new std::vector<double>();
 tt_SiDigit_ntracks     = new std::vector<int>();
 tt_SiDigit_ntracksBack = new std::vector<int>();
 tt_SiDigit_ntracksPrim = new std::vector<int>();
 tt_SiDigit_nhits       = new std::vector<int>();
 tt_SiDigit_nhitsBack   = new std::vector<int>();
 tt_SiDigit_hitID       = new std::vector<int>();
 tt_SiDigit_hitID1      = new std::vector<int>();
 tt_SiDigit_hitID2      = new std::vector<int>();

 tree->Branch("tt_SiDigit_n",      &tt_SiDigit_n,   "tt_SiDigit_n/i"  );
 tree->Branch("tt_SiDigit_strip",  &tt_SiDigit_strip);
 tree->Branch("tt_SiDigit_trackID",&tt_SiDigit_trackID);
 tree->Branch("tt_SiDigit_e",      &tt_SiDigit_e);
 tree->Branch("tt_SiDigit_e_prim", &tt_SiDigit_e_prim);
 tree->Branch("tt_SiDigit_ntracks",    &tt_SiDigit_ntracks);
 tree->Branch("tt_SiDigit_ntracksBack",&tt_SiDigit_ntracksBack);
 tree->Branch("tt_SiDigit_ntracksPrim",&tt_SiDigit_ntracksPrim);
 tree->Branch("tt_SiDigit_nhits",      &tt_SiDigit_nhits);
 tree->Branch("tt_SiDigit_nhitsBack",  &tt_SiDigit_nhitsBack);
 tree->Branch("tt_SiDigit_hitID",      &tt_SiDigit_hitID);
 tree->Branch("tt_SiDigit_hitID1",     &tt_SiDigit_hitID1);
 tree->Branch("tt_SiDigit_hitID2",     &tt_SiDigit_hitID2);

}

void DmpRootNtupleManager::beginEvent(const G4Event* evt)
{
  //clear all ntuple data vectors here
  //set event number
  eventNumber = evt->GetEventID();

  tt_cal_totE       = 0.;
  tt_cal_totE_1MeV  = 0.;
  tt_cal_totE_10MeV = 0.;

  is_pvtrack  = false;
  is_eletrack = false;
  is_postrack = false;
  is_backtrack= false;
  pvtrackID      = -1;
  eletrackID     = -1;
  postrackID     = -1;
  currentTrackID = -100;

  eDepositAcc_pvtrack = 0.;
  eDepositAcc_ele     = 0.;
  eDepositAcc_pos     = 0.;
  eDepositAcc_back    = 0.;

  tt_stepping_ntracks = 0;
  tt_stepping_trackID  -> clear();
  tt_stepping_trackPDG -> clear();
  tt_stepping_parentID -> clear();

  tt_pvtrack_nsteps   = 0;
  tt_step_pvtrack_px            -> clear();
  tt_step_pvtrack_py            -> clear();
  tt_step_pvtrack_pz            -> clear();
  tt_step_pvtrack_ekin          -> clear();
  tt_step_pvtrack_x             -> clear();
  tt_step_pvtrack_y             -> clear();
  tt_step_pvtrack_z             -> clear();
  tt_step_pvtrack_stepNumber    -> clear();
  tt_step_pvtrack_isEntering    -> clear();
  tt_step_pvtrack_thisVolume    -> clear();
  tt_step_pvtrack_nextVolume    -> clear();
  tt_step_pvtrack_thisIndex     -> clear();
  tt_step_pvtrack_nextIndex     -> clear();
  tt_step_pvtrack_stepLength    -> clear();
  tt_step_pvtrack_trackLength   -> clear();
  tt_step_pvtrack_energyDeposit -> clear();

  tt_back_nsteps       = 0;
  tt_step_back_trackID       -> clear();
  tt_step_back_pdg           -> clear();
  tt_step_back_px            -> clear();
  tt_step_back_py            -> clear();
  tt_step_back_pz            -> clear();
  tt_step_back_ekin          -> clear();
  tt_step_back_x             -> clear();
  tt_step_back_y             -> clear();
  tt_step_back_z             -> clear();
  tt_step_back_stepNumber    -> clear();
  tt_step_back_isEntering    -> clear();
  tt_step_back_thisVolume    -> clear();
  tt_step_back_nextVolume    -> clear();
  tt_step_back_thisIndex     -> clear();
  tt_step_back_nextIndex     -> clear();
  tt_step_back_stepLength    -> clear();
  tt_step_back_trackLength   -> clear();
  tt_step_back_energyDeposit -> clear();

  tt_ele_nsteps       = 0;
  tt_step_ele_px            -> clear();
  tt_step_ele_py            -> clear();
  tt_step_ele_pz            -> clear();
  tt_step_ele_ekin          -> clear();
  tt_step_ele_x             -> clear();
  tt_step_ele_y             -> clear();
  tt_step_ele_z             -> clear();
  tt_step_ele_stepNumber    -> clear();
  tt_step_ele_isEntering    -> clear();
  tt_step_ele_thisVolume    -> clear();
  tt_step_ele_nextVolume    -> clear();
  tt_step_ele_thisIndex     -> clear();
  tt_step_ele_nextIndex     -> clear();
  tt_step_ele_stepLength    -> clear();
  tt_step_ele_trackLength   -> clear();
  tt_step_ele_energyDeposit -> clear();

  tt_pos_nsteps       = 0;
  tt_step_pos_px            -> clear();
  tt_step_pos_py            -> clear();
  tt_step_pos_pz            -> clear();
  tt_step_pos_ekin          -> clear();
  tt_step_pos_x             -> clear();
  tt_step_pos_y             -> clear();
  tt_step_pos_z             -> clear();
  tt_step_pos_stepNumber    -> clear();
  tt_step_pos_isEntering    -> clear();
  tt_step_pos_thisVolume    -> clear();
  tt_step_pos_nextVolume    -> clear();
  tt_step_pos_thisIndex     -> clear();
  tt_step_pos_nextIndex     -> clear();
  tt_step_pos_stepLength    -> clear();
  tt_step_pos_trackLength   -> clear();
  tt_step_pos_energyDeposit -> clear();

  tt_CalLayer_nlayer = 0;    
  tt_CalLayer_centroid    -> clear();
  tt_CalLayer_e           -> clear();
  tt_CalLayer_sumw2       -> clear();
  tt_CalLayer_index       -> clear();

  tt_CalLayer_nlayer_1MeV = 0;    
  tt_CalLayer_centroid_1MeV    -> clear();
  tt_CalLayer_e_1MeV           -> clear();
  tt_CalLayer_sumw2_1MeV       -> clear();
  tt_CalLayer_index_1MeV       -> clear();

  tt_SiHit_n = 0;
  tt_SiHit_e     -> clear();
  tt_SiHit_e_prim-> clear();
  tt_SiHit_x     -> clear();
  tt_SiHit_y     -> clear();
  tt_SiHit_z     -> clear();
  tt_SiHit_strip -> clear();
  tt_SiHit_id    -> clear();
  tt_SiHit_trackID  -> clear();
  tt_SiHit_trackID1 -> clear();
  tt_SiHit_trackID2 -> clear();
  tt_SiHit_ntracks     -> clear();
  tt_SiHit_ntracksBack -> clear();
  tt_SiHit_ntracksPrim -> clear();

  tt_SiDigit_n = 0;
  tt_SiDigit_e       -> clear();
  tt_SiDigit_e_prim  -> clear();
  tt_SiDigit_strip   -> clear();
  tt_SiDigit_trackID -> clear();
  tt_SiDigit_ntracks     -> clear();
  tt_SiDigit_ntracksBack -> clear();
  tt_SiDigit_ntracksPrim -> clear();
  tt_SiDigit_nhits       -> clear();
  tt_SiDigit_nhitsBack   -> clear();
  tt_SiDigit_hitID       -> clear();
  tt_SiDigit_hitID1      -> clear();
  tt_SiDigit_hitID2      -> clear();

}

void DmpRootNtupleManager::save()
{ 
  if (rootFile) {
    rootFile->Write();       // Writing the histograms to the file
    rootFile->Close();        // and closing the tree (and the file)
    G4cout << "\n----> ntuple Tree is saved \n" << G4endl;
  }
}

void DmpRootNtupleManager::FillStep(const G4Step* aStep)
{
  //fill stepping info here
  G4bool sel = false;
  //only stepping through primary charged paticles or e+/e- paire from primary photon conversion
  if (aStep->GetTrack()->GetParentID()==0) {    
    if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.) sel = true;

    G4int trackID = aStep->GetTrack()->GetTrackID();
    if(trackID != currentTrackID) {
      pvtrackID      = trackID;
      currentTrackID = trackID;
      //G4cout << "   primary track ID set to " << pvtrackID <<  G4endl;
      /***
      if(sel) {
	tt_stepping_trackID    -> push_back( trackID );
	tt_stepping_trackPDG   -> push_back( aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() );
	tt_stepping_parentID   -> push_back( aStep->GetTrack()->GetParentID() );
	++tt_stepping_ntracks;
      }
      ***/
    }
    eDepositAcc_pvtrack += aStep->GetTotalEnergyDeposit(); 
    is_pvtrack  = true;
    is_eletrack = false;
    is_postrack = false;
    is_backtrack= false;
    
  }
  else if (aStep->GetPreStepPoint()->GetMomentum().z()>0) {
    sel = true;
    is_pvtrack  = false;
    is_eletrack = false;
    is_postrack = false;
    is_backtrack= true;
    G4int trackID = aStep->GetTrack()->GetTrackID();
    if(trackID != currentTrackID) {
      currentTrackID = trackID;
      /***
      tt_stepping_trackID    -> push_back( trackID );
      tt_stepping_trackPDG   -> push_back( aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() );
      tt_stepping_parentID   -> push_back( aStep->GetTrack()->GetParentID() );
      ++tt_stepping_ntracks;
      ***/
    }
    eDepositAcc_back += aStep->GetTotalEnergyDeposit(); 

  }
  else if (aStep->GetTrack()->GetParentID()==pvtrackID && aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.) {
    sel = true;
    is_pvtrack  = false;
    is_backtrack= false;
    G4int trackID = aStep->GetTrack()->GetTrackID();
    if(trackID != currentTrackID) {
      currentTrackID = trackID;
      /***
      tt_stepping_trackID    -> push_back( trackID );
      tt_stepping_trackPDG   -> push_back( aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() );
      tt_stepping_parentID   -> push_back( aStep->GetTrack()->GetParentID() );
      ++tt_stepping_ntracks;
      ***/
    }
    if(aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() == 11) {
       is_eletrack = true;
       is_postrack = false;
       eDepositAcc_ele += aStep->GetTotalEnergyDeposit(); 
    }
    else if(aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() == -11) {
      is_eletrack = false;
      is_postrack = true;
      eDepositAcc_pos += aStep->GetTotalEnergyDeposit(); 
    }
 
  }
  else {
    is_pvtrack   = false;
    is_eletrack  = false;
    is_postrack  = false;
    is_backtrack = false;
  } 

  if(!is_pvtrack && !is_eletrack && !is_postrack && !is_backtrack) return;

  //return if particle goes out to World 
  if(aStep->GetTrack()->GetCurrentStepNumber() !=1 && 
     aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "World" ) return;
  if(is_backtrack && 
     aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "World" ) return;

  G4StepPoint* point1 = aStep->GetPreStepPoint();
  G4StepPoint* point2 = aStep->GetPostStepPoint();
  if(eventNumber == debugEvent || debugEvent == -1) {
    G4cout << " new step:  current track ID= " << currentTrackID  << ", step number = " 
	   << aStep->GetTrack()->GetCurrentStepNumber() << G4endl;
    G4cout << "       prestep  at " << aStep->GetPreStepPoint()->GetPosition()  << " in volume " 
	   << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()  << G4endl;
    G4cout << "      poststep  at " << aStep->GetPostStepPoint()->GetPosition() << " in volume " 
	   << aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << G4endl;
    G4String thisProc  = "U Limit";
    G4String nextProc  = "U Limit";
    if(point1->GetProcessDefinedStep() !=0) thisProc  = point1->GetProcessDefinedStep()->GetProcessName();
    if(point2->GetProcessDefinedStep() !=0) nextProc  = point2->GetProcessDefinedStep()->GetProcessName();
    G4cout << "       this process: " << thisProc << "    next process: " << nextProc << G4endl;
  }
  if(sel) {
    G4ThreeVector pos1  = point1->GetPosition();
    G4ThreeVector pos2  = point2->GetPosition();
    G4TouchableHandle touch1 = point1->GetTouchableHandle();
    G4TouchableHandle touch2 = point2->GetTouchableHandle();
    G4String thisVolume  = touch1->GetVolume()->GetName();
    G4String nextVolume  = touch2->GetVolume()->GetName();
    //only keep steps outside the calorimeter
    if(thisVolume != "CALDetectorX" && thisVolume != "CALDetectorY" && 
       thisVolume != "CALLayerX"    && thisVolume != "CALLayerY"    && thisVolume != "Payload" ) {
      G4Track* track         = aStep->GetTrack();
      G4int stepNumber = track->GetCurrentStepNumber();
      G4bool enterVolume = (point1->GetStepStatus() == fGeomBoundary);
      G4bool leaveVolume = (point2->GetStepStatus() == fGeomBoundary);

      G4int vindex = -1;
      if(thisVolume == "World") vindex = 0; 
      else if(thisVolume == "CALDetectorX" || thisVolume == "CALDetectorY" )   vindex = 1; 
      else if(thisVolume == "CALLayerX"    || thisVolume == "CALLayerY"    )   vindex = 1; 
      else if(thisVolume == "Converter")      vindex = 2; 
      else if(thisVolume == "ThickConverter") vindex = 3; 
      else if(thisVolume == "Active Tile X" || thisVolume == "Active Tile Y")  vindex = 4; 
      else if(thisVolume == "Plane")          vindex = 5; 
      else if(thisVolume == "TKRDetectorX"  || thisVolume == "TKRDetectorY")   vindex  = 6; 
      else if(thisVolume == "STK")            vindex = 7; 
      else if(thisVolume == "PSD")            vindex = 8; 
      else if(thisVolume == "Payload")        vindex = 9; 
      else if(thisVolume == "PlaneThinW")     vindex = 10; 
      else if(thisVolume == "PlaneThickW")    vindex = 11; 

      G4int vindexN = -1;
      if(nextVolume == "World") vindexN = 0; 
      else if(nextVolume == "CALDetectorX" || nextVolume == "CALDetectorY" )   vindexN = 1; 
      else if(nextVolume == "CALLayerX"    || nextVolume == "CALLayerY"    )   vindexN = 1; 
      else if(nextVolume == "Converter")      vindexN = 2; 
      else if(nextVolume == "ThickConverter") vindexN = 3; 
      else if(nextVolume == "Active Tile X" || nextVolume == "Active Tile Y")  vindexN = 4; 
      else if(nextVolume == "Plane")          vindexN = 5; 
      else if(nextVolume == "TKRDetectorX"  || nextVolume == "TKRDetectorY")   vindexN  = 6; 
      else if(nextVolume == "STK")            vindexN = 7; 
      else if(nextVolume == "PSD")            vindexN = 8; 
      else if(nextVolume == "Payload")        vindexN = 9; 
      else if(nextVolume == "PlaneThinW")     vindexN = 10; 
      else if(nextVolume == "PlaneThickW")    vindexN = 11; 

      if(eventNumber == debugEvent || debugEvent == -1) {
	//G4int thisVolumeCopy = touch1->GetCopyNumber();
	//G4int nextVolumeCopy = touch2->GetCopyNumber();
	//G4double kinEnergy     = track->GetKineticEnergy();
	//G4double globalTime    = track->GetGlobalTime();
	G4int trackID = track->GetTrackID();
     
	G4cout << "   track ID= " << trackID << "  step number= " << stepNumber 
	       << ",  step length= " << aStep->GetStepLength() << ",  track length= " << track->GetTrackLength() << G4endl;
	G4cout << ",  energy depo= " << aStep->GetTotalEnergyDeposit();
	if(thisVolume == "Converter" || thisVolume == "ThickConverter" ) {
	  if(is_pvtrack) {G4cout << " accumulated edep= " << eDepositAcc_pvtrack;}
	  else if(is_eletrack) {G4cout << " accumulated edep= " << eDepositAcc_ele;}
	  else if(is_postrack) {G4cout << " accumulated edep= " << eDepositAcc_pos;}
	  else if(is_backtrack) {G4cout << " accumulated edep= " << eDepositAcc_back;}
	  if( stepNumber==1 || leaveVolume) {G4cout << " SELECTED!" <<  G4endl;}
	  else  {G4cout <<  G4endl;}
	  G4String thisProc  = "Uset Limit";
	  G4String nextProc  = "Uset Limit";
	  if(point1->GetProcessDefinedStep() !=0) thisProc  = point1->GetProcessDefinedStep()->GetProcessName();
	  if(point2->GetProcessDefinedStep() !=0) nextProc  = point2->GetProcessDefinedStep()->GetProcessName();
	  G4cout << "       this process: " << thisProc << "    next process: " << nextProc << G4endl;
	  G4cout << "       point1 momentum (MeV): " <<point1->GetMomentum() << G4endl;
	  G4cout << "       point2 momentum (MeV): " <<point2->GetMomentum() << G4endl;
	  //G4cout << "       track  momentum (MeV): " << track->GetMomentum() << "   kinetic energy (MeV): " << kinEnergy << G4endl;
	  G4cout << "       prestep  at " << pos1 << " in volume " << thisVolume  << "    enter = " << enterVolume  << G4endl;
	  G4cout << "       poststep at " << pos2 << " in volume " << nextVolume  << "    leave = " << leaveVolume  << G4endl;
	}
      }
    
      bool volSel = (thisVolume == "Active Tile X" || thisVolume == "Active Tile Y" || thisVolume == "PSD" ); 
      if(is_backtrack && volSel)   {
	/***	
	if(stepNumber == 1  || nextVolume=="Payload" || (aStep->GetTotalEnergyDeposit()>0 && leaveVolume) ) {
	  if(eventNumber == debugEvent || debugEvent == -1) {
	    G4int trackID = track->GetTrackID();
	    G4cout << "   track ID= " << trackID << "  step number= " << stepNumber 
		   << ",  step length= " << aStep->GetStepLength() << ",  track length= " << track->GetTrackLength() << G4endl;
	    G4cout << ",  energy depo= " << aStep->GetTotalEnergyDeposit();
	    {G4cout << " accumulated edep= " << eDepositAcc_back;}
	    if( stepNumber==1 || leaveVolume) {G4cout << " SELECTED!" <<  G4endl;}
	    else  {G4cout <<  G4endl;}
	    G4String thisProc  = "Uset Limit";
	    G4String nextProc  = "Uset Limit";
	    if(point1->GetProcessDefinedStep() !=0) thisProc  = point1->GetProcessDefinedStep()->GetProcessName();
	    if(point2->GetProcessDefinedStep() !=0) nextProc  = point2->GetProcessDefinedStep()->GetProcessName();
	    G4cout << "       this process: " << thisProc << "    next process: " << nextProc << G4endl;
	    G4cout << "       point1 momentum (MeV): " <<point1->GetMomentum().x() << " " << point1->GetMomentum().y() << " " << point1->GetMomentum().z() << G4endl;
	    G4cout << "       point2 momentum (MeV): " <<point2->GetMomentum().x() << " " << point2->GetMomentum().y() << " " << point2->GetMomentum().z() << G4endl;
	    G4cout << "       prestep  at " << pos1 << " in volume " << thisVolume  << "    enter = " << enterVolume  << G4endl;
	    G4cout << "       poststep at " << pos2 << " in volume " << nextVolume  << "    leave = " << leaveVolume  << G4endl;
	    G4cout << "       PDG code    " <<aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() << G4endl;
	  }
	}
	
	if(stepNumber == 1) {
	  tt_step_back_trackID -> push_back(  aStep->GetTrack()->GetTrackID() );
	  tt_step_back_pdg     -> push_back(  aStep->GetTrack()->GetDynamicParticle()->GetPDGcode()  );
	  tt_step_back_px      -> push_back(  point1->GetMomentum().x()  );
	  tt_step_back_py      -> push_back(  point1->GetMomentum().y()  );
	  tt_step_back_pz      -> push_back(  point1->GetMomentum().z()  );
	  tt_step_back_ekin    -> push_back(  point1->GetKineticEnergy() );
	  tt_step_back_x       -> push_back(  point1->GetPosition().x()  );
	  tt_step_back_y       -> push_back(  point1->GetPosition().y()  );
	  tt_step_back_z       -> push_back(  point1->GetPosition().z()  );
	  tt_step_back_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_back_isEntering    -> push_back( enterVolume  );
	  tt_step_back_thisVolume    -> push_back( thisVolume   );
	  tt_step_back_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_back_thisIndex     -> push_back( vindex       );
	  tt_step_back_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_back_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_back_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_back_energyDeposit -> push_back( eDepositAcc_back );	 
	  ++tt_back_nsteps;
	}
	***/
	//filling steps that leaves the volume and has deposited energy 
	if(leaveVolume) {
	  //if(aStep->GetTotalEnergyDeposit()>0 || nextVolume=="Payload") {
	  if(aStep->GetTotalEnergyDeposit()>0) {
	    tt_step_back_trackID -> push_back(  aStep->GetTrack()->GetTrackID() );
	    tt_step_back_pdg     -> push_back(  aStep->GetTrack()->GetDynamicParticle()->GetPDGcode()  );
	    tt_step_back_px      -> push_back(  point2->GetMomentum().x()  );
	    tt_step_back_py      -> push_back(  point2->GetMomentum().y()  );
	    tt_step_back_pz      -> push_back(  point2->GetMomentum().z()  );
	    tt_step_back_ekin    -> push_back(  point2->GetKineticEnergy() );
	    tt_step_back_x       -> push_back(  point2->GetPosition().x()  );
	    tt_step_back_y       -> push_back(  point2->GetPosition().y()  );
	    tt_step_back_z       -> push_back(  point2->GetPosition().z()  );
	    tt_step_back_stepNumber    -> push_back( stepNumber  );
	    tt_step_back_isEntering    -> push_back( enterVolume );
	    tt_step_back_thisVolume    -> push_back( thisVolume  );
	    tt_step_back_nextVolume    -> push_back( nextVolume  );	  
	    tt_step_back_thisIndex     -> push_back( vindex       );
	    tt_step_back_nextIndex     -> push_back( vindexN       );
	    tt_step_back_stepLength    -> push_back( aStep->GetStepLength()  );
	    tt_step_back_trackLength   -> push_back( track->GetTrackLength() );
	    tt_step_back_energyDeposit -> push_back( eDepositAcc_back );	 
	    ++tt_back_nsteps;
	  }
	}
 
      }

      if(is_pvtrack && volSel)   {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "pvtrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  tt_step_pvtrack_px   -> push_back(  point1->GetMomentum().x()  );
	  tt_step_pvtrack_py   -> push_back(  point1->GetMomentum().y()  );
	  tt_step_pvtrack_pz   -> push_back(  point1->GetMomentum().z()  );
	  tt_step_pvtrack_ekin -> push_back(  point1->GetKineticEnergy() );
	  tt_step_pvtrack_x    -> push_back(  point1->GetPosition().x()  );
	  tt_step_pvtrack_y    -> push_back(  point1->GetPosition().y()  );
	  tt_step_pvtrack_z    -> push_back(  point1->GetPosition().z()  );
	  tt_step_pvtrack_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_pvtrack_isEntering    -> push_back( enterVolume  );
	  tt_step_pvtrack_thisVolume    -> push_back( thisVolume   );
	  tt_step_pvtrack_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_pvtrack_thisIndex     -> push_back( vindex       );
	  tt_step_pvtrack_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_pvtrack_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pvtrack_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pvtrack_energyDeposit -> push_back( eDepositAcc_pvtrack );	 
	  ++tt_pvtrack_nsteps;
	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  tt_step_pvtrack_px   -> push_back(  point2->GetMomentum().x()  );
	  tt_step_pvtrack_py   -> push_back(  point2->GetMomentum().y()  );
	  tt_step_pvtrack_pz   -> push_back(  point2->GetMomentum().z()  );
	  tt_step_pvtrack_ekin -> push_back(  point2->GetKineticEnergy() );
	  tt_step_pvtrack_x    -> push_back(  point2->GetPosition().x()  );
	  tt_step_pvtrack_y    -> push_back(  point2->GetPosition().y()  );
	  tt_step_pvtrack_z    -> push_back(  point2->GetPosition().z()  );
	  tt_step_pvtrack_stepNumber    -> push_back( stepNumber  );
	  tt_step_pvtrack_isEntering    -> push_back( enterVolume );
	  tt_step_pvtrack_thisVolume    -> push_back( thisVolume  );
	  tt_step_pvtrack_nextVolume    -> push_back( nextVolume  );
	  tt_step_pvtrack_thisIndex     -> push_back( vindex       );
	  tt_step_pvtrack_nextIndex     -> push_back( vindexN       );
	  tt_step_pvtrack_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pvtrack_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pvtrack_energyDeposit -> push_back( eDepositAcc_pvtrack );	 
	  ++tt_pvtrack_nsteps;
	}
      }

      if(is_eletrack && volSel)  {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "eletrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
 	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  tt_step_ele_px   -> push_back(  point1->GetMomentum().x()  );
	  tt_step_ele_py   -> push_back(  point1->GetMomentum().y()  );
	  tt_step_ele_pz   -> push_back(  point1->GetMomentum().z()  );
	  tt_step_ele_ekin -> push_back(  point1->GetKineticEnergy() );
	  tt_step_ele_x    -> push_back(  point1->GetPosition().x()  );
	  tt_step_ele_y    -> push_back(  point1->GetPosition().y()  );
	  tt_step_ele_z    -> push_back(  point1->GetPosition().z()  );
	  tt_step_ele_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_ele_isEntering    -> push_back( enterVolume  );
	  tt_step_ele_thisVolume    -> push_back( thisVolume   );
	  tt_step_ele_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_ele_thisIndex     -> push_back( vindex       );
	  tt_step_ele_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_ele_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_ele_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_ele_energyDeposit -> push_back( eDepositAcc_ele );	 
	  ++tt_ele_nsteps;
	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  tt_step_ele_px   -> push_back(  point2->GetMomentum().x()  );
	  tt_step_ele_py   -> push_back(  point2->GetMomentum().y()  );
	  tt_step_ele_pz   -> push_back(  point2->GetMomentum().z()  );
	  tt_step_ele_ekin -> push_back(  point2->GetKineticEnergy() );
	  tt_step_ele_x    -> push_back(  point2->GetPosition().x()  );
	  tt_step_ele_y    -> push_back(  point2->GetPosition().y()  );
	  tt_step_ele_z    -> push_back(  point2->GetPosition().z()  );
	  tt_step_ele_stepNumber    -> push_back( stepNumber  );
	  tt_step_ele_isEntering    -> push_back( enterVolume );
	  tt_step_ele_thisVolume    -> push_back( thisVolume  );
	  tt_step_ele_nextVolume    -> push_back( nextVolume  );	  
	  tt_step_ele_thisIndex     -> push_back( vindex       );
	  tt_step_ele_nextIndex     -> push_back( vindexN       );
	  tt_step_ele_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_ele_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_ele_energyDeposit -> push_back( eDepositAcc_ele );	 
	  ++tt_ele_nsteps;
	}
      }
      if(is_postrack && volSel)  {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "postrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  tt_step_pos_px   -> push_back(  point1->GetMomentum().x()  );
	  tt_step_pos_py   -> push_back(  point1->GetMomentum().y()  );
	  tt_step_pos_pz   -> push_back(  point1->GetMomentum().z()  );
	  tt_step_pos_ekin -> push_back(  point1->GetKineticEnergy() );
	  tt_step_pos_x    -> push_back(  point1->GetPosition().x()  );
	  tt_step_pos_y    -> push_back(  point1->GetPosition().y()  );
	  tt_step_pos_z    -> push_back(  point1->GetPosition().z()  );
	  tt_step_pos_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_pos_isEntering    -> push_back( enterVolume  );
	  tt_step_pos_thisVolume    -> push_back( thisVolume   );
	  tt_step_pos_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_pos_thisIndex     -> push_back( vindex       );
	  tt_step_pos_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_pos_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pos_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pos_energyDeposit -> push_back( eDepositAcc_pos );	 
	  ++tt_pos_nsteps;
	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  tt_step_pos_px   -> push_back(  point2->GetMomentum().x()  );
	  tt_step_pos_py   -> push_back(  point2->GetMomentum().y()  );
	  tt_step_pos_pz   -> push_back(  point2->GetMomentum().z()  );
	  tt_step_pos_ekin -> push_back(  point2->GetKineticEnergy() );
	  tt_step_pos_x    -> push_back(  point2->GetPosition().x()  );
	  tt_step_pos_y    -> push_back(  point2->GetPosition().y()  );
	  tt_step_pos_z    -> push_back(  point2->GetPosition().z()  );
	  tt_step_pos_stepNumber    -> push_back( stepNumber  );
	  tt_step_pos_isEntering    -> push_back( enterVolume );
	  tt_step_pos_thisVolume    -> push_back( thisVolume  );
	  tt_step_pos_nextVolume    -> push_back( nextVolume  );
	  tt_step_pos_thisIndex     -> push_back( vindex       );
	  tt_step_pos_nextIndex     -> push_back( vindexN       );
	  tt_step_pos_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pos_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pos_energyDeposit -> push_back( eDepositAcc_pos );	 
	  ++tt_pos_nsteps;
	}
      }

    }
  }

}

void DmpRootNtupleManager::FillEvent(const G4Event* evt)
{  
  //fill even info here, also filter and save ntuple
  bool toKeep = true;

  if(eventNumber == debugEvent || debugEvent == -1) {
    G4int nVertex = evt->GetNumberOfPrimaryVertex();
    G4cout << " Number of PrimaryVertex: " << nVertex << G4endl;
    for ( G4int j = 0; j < nVertex; j++) { 
      evt->GetPrimaryVertex(j)->Print();
      G4cout << "   vetex " << j << " position " << evt->GetPrimaryVertex(j)->GetPosition() << G4endl;
      G4int nPart =  evt->GetPrimaryVertex(j)->GetNumberOfParticle(); 
      G4cout << "   Number of PrimaryParticles in this vertex: " << nPart << G4endl;
      for ( G4int i = 0; i < nPart; i++) {
	G4cout << "   particle " << i << " momentum " << evt->GetPrimaryVertex(j)->GetPrimary(i)->GetMomentum() << G4endl;
      }
    }
  }
  
  tt_run   = -1;
  tt_event = evt->GetEventID();
  tt_npv   = evt->GetNumberOfPrimaryVertex();
  if(tt_npv>1) G4cout << " WARNING: Number of PrimaryVertex more than 1: " << tt_npv << G4endl;

  tt_pv_x = evt->GetPrimaryVertex(0)->GetPosition().x();
  tt_pv_y = evt->GetPrimaryVertex(0)->GetPosition().y();
  tt_pv_z = evt->GetPrimaryVertex(0)->GetPosition().z();

  tt_npvpart   =  evt->GetPrimaryVertex(0)->GetNumberOfParticle(); 
  if(tt_npvpart>1) G4cout << " WARNING: Number of PrimaryParticle more than 1: " << tt_npvpart << G4endl;

  tt_pvpart_px   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().x();
  tt_pvpart_py   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().y();
  tt_pvpart_pz   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().z();
  tt_pvpart_ekin = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetKineticEnergy();
  tt_pvpart_q    = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetCharge();
  tt_pvpart_pdg  = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetPDGcode();


  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  G4Navigator* navigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();

  //dumpinmg some trajectories
  /***
  G4cout << "Number of trajectories in this event =  " << n_trajectories << G4endl;
  G4VTrajectoryPoint* firstpoint = 0;
  G4VTrajectoryPoint*  lastpoint = 0;
  G4int nsteps = 0;
  G4VPhysicalVolume* firstvolume;
  G4VPhysicalVolume* lastvolume;

  for (G4int i=0; i<n_trajectories; i++) { G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
      firstpoint  = trj->GetPoint(0);
      firstvolume = navigator->LocateGlobalPointAndSetup(firstpoint->GetPosition());
      
      //if(firstvolume->GetName() == "CALDetectorX" || firstvolume->GetName() == "CALDetectorY") {
      //  nsteps = trj->GetPointEntries();
	//lastpoint = trj->GetPoint(nsteps-1);
	//lastvolume = navigator->LocateGlobalPointAndSetup(lastpoint->GetPosition());
	//if(lastvolume->GetName() == "CALDetectorX" || lastvolume->GetName() == "CALDetectorY") continue;
	//if(lastvolume->GetName() == "World" && (lastpoint->GetPosition().z() < firstpoint->GetPosition().z()) ) continue;
      //}
      

      G4cout << "   trajectory ID= " << trj->GetTrackID() << "  parent ID= " << trj->GetParentID() 
	     << "  PDG code= " << trj->GetPDGEncoding () << "  particle name= " << trj->GetParticleName () 
	     << "  charge= " << trj->GetCharge() <<  G4endl;
      G4cout << "       Initial momentum (MeV): " << trj->GetInitialMomentum().x() << " " <<  trj->GetInitialMomentum().y() 
	     << " " << trj->GetInitialMomentum().z() << G4endl;
      G4cout << "       Initial kinetic energy (MeV): " << ((G4Trajectory*) trj)->GetInitialKineticEnergy() << G4endl;
      G4cout << "       first step at " << firstpoint->GetPosition() << " in volume " << firstvolume->GetName() << G4endl;
      nsteps = trj->GetPointEntries();
      lastpoint  = trj->GetPoint(nsteps-1);
      lastvolume = navigator->LocateGlobalPointAndSetup(lastpoint->GetPosition());
      G4cout << "        last step at " << lastpoint->GetPosition() << " in volume " << lastvolume->GetName() << G4endl;
      //trj->ShowTrajectory();
      G4cout << G4endl;
      G4cout << G4endl;

  }
  ***/

  G4VTrajectory* trjPrimary = 0;
  for (G4int i=0; i<n_trajectories; i++) { 
    G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
    if(trj->GetParentID()==0) {
      trjPrimary = trj;
      continue;
    }
  }

  tt_pvtrj_trackID = -1;
  tt_pvtrj_stop_vo = "";
  tt_pvtrj_stop_x = 0;
  tt_pvtrj_stop_y = 0;
  tt_pvtrj_stop_z = 0;

  tt_ele_trackID = -1;
  tt_ele_parentID = -1;
  tt_ele_stop_vo = "";
  tt_ele_stop_x = 0;
  tt_ele_stop_y = 0;
  tt_ele_stop_z = 0;

  tt_pos_trackID = -1;
  tt_pos_parentID = -1;
  tt_pos_stop_vo = "";
  tt_pos_stop_x = 0;
  tt_pos_stop_y = 0;
  tt_pos_stop_z = 0;

  if(trjPrimary) {
    G4String stopAt = navigator->LocateGlobalPointAndSetup(trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())->GetName();
    G4int vindex = -1;
    if(stopAt == "World") vindex = 0; 
    else if(stopAt == "CALDetectorX" || stopAt == "CALDetectorY" )   vindex = 1; 
    else if(stopAt == "Converter")      vindex = 2; 
    else if(stopAt == "ThickConverter") vindex = 3; 
    else if(stopAt == "Active Tile X" || stopAt == "Active Tile Y")  vindex = 4; 
    else if(stopAt == "Plane")          vindex = 5; 
    else if(stopAt == "TKRDetectorX"  || stopAt == "TKRDetectorY")   vindex  = 6; 
    else if(stopAt == "STK")            vindex = 7; 
    else if(stopAt == "PSD")            vindex = 8; 
    else if(stopAt == "Payload")        vindex = 9; 
    else if(stopAt == "PlaneThinW")       vindex = 10; 
    else if(stopAt == "PlaneThickW")    vindex = 11; 

    
    tt_pvtrj_trackID = trjPrimary->GetTrackID();
    tt_pvtrj_stop_index = vindex;
    tt_pvtrj_stop_vo    = stopAt;
    tt_pvtrj_stop_x = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().x();
    tt_pvtrj_stop_y = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().y();
    tt_pvtrj_stop_z = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().z();

    G4VTrajectory* trjEle = 0;
    G4VTrajectory* trjPos = 0;
    for (G4int i=0; i<n_trajectories; i++) { 
      G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
      if(trj->GetParentID()==trjPrimary->GetTrackID() && trjPrimary->GetPDGEncoding()==22) {
	if(trj->GetPDGEncoding()==11)  trjEle = trj;
	if(trj->GetPDGEncoding()==-11) trjPos = trj;
      }
    }
    //G4cout << "   primary particle stops at : " << tt_pvtrj_stop_x << " " << tt_pvtrj_stop_y << " " << tt_pvtrj_stop_z << ", volume: " << tt_pvtrj_stop_vo  << G4endl;

    if(trjEle) {
      tt_ele_px   = trjEle->GetInitialMomentum().x();
      tt_ele_py   = trjEle->GetInitialMomentum().y();
      tt_ele_pz   = trjEle->GetInitialMomentum().z();
      tt_ele_ekin = ((G4Trajectory*) trjEle)->GetInitialKineticEnergy();
      //check starting point
      if( trjEle->GetPoint(0)->GetPosition() !=trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())
	G4cout << "WARNING from HistoManager: Event " << evt->GetEventID() << " conversion position not matching for electron!!!! " << trjEle->GetPoint(0)->GetPosition() << " " << trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition() << G4endl;

      G4String stopAt = navigator->LocateGlobalPointAndSetup(trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition())->GetName();
      G4int vindex = -1;
      if(stopAt == "World") vindex = 0; 
      else if(stopAt == "CALDetectorX" || stopAt == "CALDetectorY" )   vindex = 1; 
      else if(stopAt == "Converter")      vindex = 2; 
      else if(stopAt == "ThickConverter") vindex = 3; 
      else if(stopAt == "Active Tile X" || stopAt == "Active Tile Y")  vindex = 4; 
      else if(stopAt == "Plane")          vindex = 5; 
      else if(stopAt == "TKRDetectorX"  || stopAt == "TKRDetectorY")   vindex  = 6; 
      else if(stopAt == "STK")            vindex = 7; 
      else if(stopAt == "PSD")            vindex = 8; 
      else if(stopAt == "Payload")        vindex = 9; 
      else if(stopAt == "PlaneThinW")       vindex = 10; 
      else if(stopAt == "PlaneThickW")    vindex = 11; 

      tt_ele_trackID  = trjEle->GetTrackID();
      tt_ele_parentID = trjEle->GetParentID();
      tt_ele_stop_index = vindex;
      tt_ele_stop_vo = stopAt;
      tt_ele_stop_x = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().x();
      tt_ele_stop_y = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().y();
      tt_ele_stop_z = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().z();

    }

    if(trjPos) {
      tt_pos_px   = trjPos->GetInitialMomentum().x();
      tt_pos_py   = trjPos->GetInitialMomentum().y();
      tt_pos_pz   = trjPos->GetInitialMomentum().z();
      tt_pos_ekin = ((G4Trajectory*) trjPos)->GetInitialKineticEnergy();
      if( trjPos->GetPoint(0)->GetPosition() !=trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())
	G4cout << "WARNING from HistoManager: Event " << evt->GetEventID() << " conversion position not matching for positron!!!! " << trjPos->GetPoint(0)->GetPosition() << " " << trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition() << G4endl;

      G4String stopAt = navigator->LocateGlobalPointAndSetup(trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition())->GetName();
      G4int vindex = -1;
      if(stopAt == "World") vindex = 0; 
      else if(stopAt == "CALDetectorX" || stopAt == "CALDetectorY" )   vindex = 1; 
      else if(stopAt == "Converter")      vindex = 2; 
      else if(stopAt == "ThickConverter") vindex = 3; 
      else if(stopAt == "Active Tile X" || stopAt == "Active Tile Y")  vindex = 4; 
      else if(stopAt == "Plane")          vindex = 5; 
      else if(stopAt == "TKRDetectorX"  || stopAt == "TKRDetectorY")   vindex  = 6; 
      else if(stopAt == "STK")            vindex = 7; 
      else if(stopAt == "PSD")            vindex = 8; 
      else if(stopAt == "Payload")        vindex = 9; 
      else if(stopAt == "PlaneThinW")       vindex = 10; 
      else if(stopAt == "PlaneThickW")    vindex = 11; 

      tt_pos_trackID = trjPos->GetTrackID();
      tt_pos_parentID = trjPos->GetParentID();
      tt_pos_stop_index = vindex;
      tt_pos_stop_vo = stopAt;
      tt_pos_stop_x = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().x();
      tt_pos_stop_y = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().y();
      tt_pos_stop_z = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().z();
    }

  }
  /***
  G4cout << "Dumping ntuple variable ......  " << G4endl;
  G4cout << "   primary vertex position: " << tt_pv_x << " " <<  tt_pv_y << " " << tt_pv_z << G4endl;
  G4cout << "   primary vertex momentum, ekin, charg, pdg: " << tt_pvpart_px << " " << tt_pvpart_py << " " << tt_pvpart_pz 
	 << " " << tt_pvpart_ekin << " " << tt_pvpart_q << " " << tt_pvpart_pdg << G4endl;
  G4cout << "   electron momentum, ekin: " << tt_ele_px << " " << tt_ele_py << " " << tt_ele_pz << " " << tt_ele_ekin << G4endl;
  G4cout << "   electron stops at : " << tt_ele_stop_x << " " << tt_ele_stop_y << " " << tt_ele_stop_z << ", volume: " << tt_ele_stop_vo  << G4endl;
  G4cout << "   positron momentum, ekin: " << tt_pos_px << " " << tt_pos_py << " " << tt_pos_pz << " " << tt_pos_ekin << G4endl;
  G4cout << "   positron stops at : " << tt_pos_stop_x << " " << tt_pos_stop_y << " " << tt_pos_stop_z << ", volume: " << tt_pos_stop_vo  << G4endl;
  ***/

  //Tracker hits
  DmpSimuStkHitsCollection* THC = 0;

  //Calorimeter hits
  DmpSimuBgoHitsCollection* CHC = 0;
  G4SDManager * SDman = G4SDManager::GetSDMpointer();  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

  if (HCE) {
    THC = (DmpSimuStkHitsCollection*)     (HCE->GetHC(SDman->GetCollectionID("TrackerCollection")));
    CHC = (DmpSimuBgoHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("BGOHitCollection")));
  }

  if (THC) {
    int n_hit = THC->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of track hits in this event =  " << n_hit << G4endl;
      G4cout << "  edp  " << "  strip " << " plane " << " type " 
	     << "  x    " << "   y    " << "     z    " <<  G4endl;       
    }   
    G4double ESil=0;
    G4double ESilPrim=0;
    G4ThreeVector pos;
    G4int NStrip, NPlane, IsX;
    tt_SiHit_n = 0;
    for (int i=0;i<n_hit;i++) {
      ESil     = (*THC)[i]->GetEdepSil();
      ESilPrim = (*THC)[i]->GetEdepSilPrim();
      NStrip = (*THC)[i]->GetNStrip();
      NPlane = (*THC)[i]->GetNSilPlane();
      IsX    = (*THC)[i]->GetPlaneType();
      pos    = (*THC)[i]->GetPos();
      tt_SiHit_e      -> push_back(ESil);
      tt_SiHit_e_prim -> push_back(ESilPrim);
      tt_SiHit_x -> push_back(pos.x());
      tt_SiHit_y -> push_back(pos.y());
      tt_SiHit_z -> push_back(pos.z());
      tt_SiHit_strip   -> push_back(IsX*1000000 + NPlane*100000 + NStrip);
      tt_SiHit_id      -> push_back(i);
      tt_SiHit_trackID -> push_back((*THC)[i]->GetPrimTrackID());
      tt_SiHit_trackID1 -> push_back((*THC)[i]->GetTrackID1());
      tt_SiHit_trackID2 -> push_back((*THC)[i]->GetTrackID());
      tt_SiHit_ntracks -> push_back((*THC)[i]->GetNtracks());
      tt_SiHit_ntracksBack -> push_back((*THC)[i]->GetNtracksBack());
      tt_SiHit_ntracksPrim -> push_back((*THC)[i]->GetNtracksPrim());
      ++tt_SiHit_n;
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << ESil/MeV <<  "   "  << NStrip << "    " << NPlane <<  "    " << IsX << "    " 
	       << (*THC)[i]->GetTrackID()
	       << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }        
    }
  }

  if (CHC) {
    int n_hit = CHC->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of calorimeter hits in this event =  " << n_hit << G4endl;
      G4cout << "  edp  " << "  bar " << " plane " << " type " 
	     << "  x    " << "   y    " << "     z    " <<  G4endl;       
    }   
    
    G4RunManager* runManager = G4RunManager::GetRunManager();
    DmpDetectorConstruction* dmpDetector =
      (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

    G4int NbOfCALLayers = 7;
    //G4int NbOfCALBars    = 12;
    if(NbOfCALLayers != dmpDetector->GetBgoDetectorDescription()->GetNbOfCALLayers()) G4cout<< "WARNING NbOfCALLayers is not "<< NbOfCALLayers<< "!!!"<< G4endl;

    G4double xLayerSum  [7] = {0.0};
    G4double xLayerSumW [7] = {0.0};
    G4double xLayerSumW2[7] = {0.0};
    G4double yLayerSum  [7] = {0.0};
    G4double yLayerSumW [7] = {0.0};
    G4double yLayerSumW2[7] = {0.0};
    G4double xLayerSum_1MeV   [7] = {0.0};
    G4double xLayerSumW_1MeV  [7] = {0.0};
    G4double xLayerSumW2_1MeV [7] = {0.0};
    G4double yLayerSum_1MeV   [7] = {0.0};
    G4double yLayerSumW_1MeV  [7] = {0.0};
    G4double yLayerSumW2_1MeV [7] = {0.0};
    

    G4double Edep=0;
    G4ThreeVector pos;
    G4int CALBarNumber, CALPlaneNumber, CALType;
    for (int i=0;i<n_hit;i++) {
      Edep           = (*CHC)[i]->GetEdepCAL();
      pos            = (*CHC)[i]->GetPos();
      CALBarNumber   = (*CHC)[i]->GetCALBarNumber();
      CALPlaneNumber = (*CHC)[i]->GetCALPlaneNumber();
      CALType        = (*CHC)[i]->GetCALType();
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << Edep/MeV <<  "   "  << CALBarNumber << "    " << CALPlaneNumber <<  "    " << CALType 
	       << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }        
      tt_cal_totE += Edep;
      if(Edep>1./MeV)  tt_cal_totE_1MeV  += Edep;
      if(Edep>10./MeV) tt_cal_totE_10MeV += Edep;
      if(CALType==1) { // x layers
	xLayerSum   [CALPlaneNumber] += Edep;
	xLayerSumW  [CALPlaneNumber] += Edep*CALBarNumber;
	xLayerSumW2 [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	if(Edep>1./MeV) {
	  xLayerSum_1MeV   [CALPlaneNumber] += Edep;
	  xLayerSumW_1MeV  [CALPlaneNumber] += Edep*CALBarNumber;
	  xLayerSumW2_1MeV [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	}
      }
      else if(CALType==0) { // y layers
	yLayerSum   [CALPlaneNumber] += Edep;
	yLayerSumW  [CALPlaneNumber] += Edep*CALBarNumber;
	yLayerSumW2 [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	if(Edep>1./MeV) {
	  yLayerSum_1MeV   [CALPlaneNumber] += Edep;
	  yLayerSumW_1MeV  [CALPlaneNumber] += Edep*CALBarNumber;
	  yLayerSumW2_1MeV [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	}
      }
      else {
	G4cout << "WARNING wrong CALType!!! " << CALType << G4endl;
      }
    }

    tt_CalLayer_nlayer = 0;
    tt_CalLayer_nlayer_1MeV = 0;
    for (int i=0;i<NbOfCALLayers;i++) {
      if(xLayerSum[i] > 0) {
	double pos = xLayerSumW[i]/xLayerSum[i];
	tt_CalLayer_centroid -> push_back(pos);
	tt_CalLayer_e        -> push_back(xLayerSum[i]);
	tt_CalLayer_sumw2    -> push_back(xLayerSumW2[i]); //width = sqrt(sumw2/e-centroid**2)
	tt_CalLayer_index    -> push_back(100+i);
	++tt_CalLayer_nlayer;
      }
      if(yLayerSum[i] > 0) {
	double pos = yLayerSumW[i]/yLayerSum[i];
	tt_CalLayer_centroid -> push_back(pos);
	tt_CalLayer_e        -> push_back(yLayerSum[i]);
	tt_CalLayer_sumw2    -> push_back(yLayerSumW2[i]); //width = sqrt(sumw2/e-centroid**2)
	tt_CalLayer_index    -> push_back(i);
	++tt_CalLayer_nlayer;
      }

      if(xLayerSum_1MeV[i] > 0) {
	double pos = xLayerSumW_1MeV[i]/xLayerSum_1MeV[i];
	tt_CalLayer_centroid_1MeV -> push_back(pos);
	tt_CalLayer_e_1MeV        -> push_back(xLayerSum_1MeV[i]);
	tt_CalLayer_sumw2_1MeV    -> push_back(xLayerSumW2_1MeV[i]);
	tt_CalLayer_index_1MeV    -> push_back(100+i);
	++tt_CalLayer_nlayer_1MeV;
      }
      if(yLayerSum_1MeV[i] > 0) {
	double pos = yLayerSumW_1MeV[i]/yLayerSum_1MeV[i];
	tt_CalLayer_centroid_1MeV -> push_back(pos);
	tt_CalLayer_e_1MeV        -> push_back(yLayerSum_1MeV[i]);
	tt_CalLayer_sumw2_1MeV    -> push_back(yLayerSumW2_1MeV[i]);
	tt_CalLayer_index_1MeV    -> push_back(i);
	++tt_CalLayer_nlayer_1MeV;
      }

      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << " xLayer " << i << " " << " esum " << xLayerSum[i] << " esumW " << xLayerSumW[i] << G4endl;
	G4cout << " yLayer " << i << " " << " esum " << yLayerSum[i] << " esumW " << yLayerSumW[i] << G4endl;
	G4cout << " 1MeV xLayer " << i << " " << " esum " << xLayerSum_1MeV[i] << " esumW " << xLayerSumW_1MeV[i] << G4endl;
	G4cout << " 1MeV yLayer " << i << " " << " esum " << yLayerSum_1MeV[i] << " esumW " << yLayerSumW_1MeV[i] << G4endl;
      }
    }

    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << " total energy deposited: " << tt_cal_totE << " " << tt_cal_totE_1MeV << " "
	     << tt_cal_totE_10MeV << G4endl;
    }

  }

  G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  //G4int myDigiCollID = fDM->GetDigiCollectionID("DigitsCollection");    
  G4int myDigiCollID = fDM->GetDigiCollectionID("STKDigitsCollection");    
  DmpSimuStkDigitsCollection * DC = (DmpSimuStkDigitsCollection*)fDM->GetDigiCollection( myDigiCollID );

  DmpSimuStkDigitizer * myDM = 
    (DmpSimuStkDigitizer*)fDM->FindDigitizerModule( "DmpSimuStkDigitizer" );

  G4int *ThitID = myDM->GetThitID();

  if(DC) {
    G4cout << "Total Digits " << DC->entries() << G4endl;
    G4cout << G4endl;
    if(DC->entries() ==0 && THC->entries() >0) {
      G4cout << "  oooooooooo Digits is " << DC->entries() << " but Hits is " << THC->entries() << " in event " <<  evt->GetEventID() << G4endl;
    }
    
    G4int NbOfTKRChannels =  73728;
    /***
    for (G4int i=0;i<NbOfTKRChannels ;i++) {
      G4int j = (ThitID)[i];
      if(j!=-1) G4cout << "digit on channel " << i << " at collection location " << j << "  energy  " << (*DC)[j]->GetEnergy() <<  G4endl;
    }
    ***/
    //G4cout << " i|X|Lay|C|E|Eprim/Id   " <<G4endl;

    //G4int n_digi =  DC->entries();
    G4int NStrip, NPlane, IsX;
    //G4double Energy_Threshold = 10.*keV;
    G4double Energy_Threshold = 0.*keV;
    //for (G4int i=0;i<n_digi;i++) {
    for (G4int j=0;j<NbOfTKRChannels;j++) {
      //SiDigit
      G4int i = (ThitID)[j];
      if(i==-1) continue;
      if((*DC)[i]->GetDigiType()!=0) continue;

      G4double EChannel     = (*DC)[i]->GetEnergy();
      // energy threhold
      if(EChannel < Energy_Threshold) continue;
      NStrip = (*DC)[i]->GetStripNumber();
      NPlane = (*DC)[i]->GetPlaneNumber();
      IsX    = (*DC)[i]->GetPlaneType();
      G4double EChannelPrim = (*DC)[i]->GetEnergyPrim();
      tt_SiDigit_e       -> push_back(EChannel);
      tt_SiDigit_e_prim  -> push_back(EChannelPrim);
      tt_SiDigit_strip   -> push_back(IsX*1000000 + NPlane*100000 + NStrip);
      tt_SiDigit_trackID -> push_back((*DC)[i]->GetPrimTrackID());
      tt_SiDigit_ntracks     -> push_back((*DC)[i]->GetNtracks());
      tt_SiDigit_ntracksBack -> push_back((*DC)[i]->GetNtracksBack());
      tt_SiDigit_ntracksPrim -> push_back((*DC)[i]->GetNtracksPrim());
      tt_SiDigit_nhits       -> push_back((*DC)[i]->GetNhits());
      tt_SiDigit_nhitsBack   -> push_back((*DC)[i]->GetNhitsBack());
      tt_SiDigit_hitID       -> push_back((*DC)[i]->GetHitID());
      tt_SiDigit_hitID1      -> push_back((*DC)[i]->GetHitID1());
      tt_SiDigit_hitID2      -> push_back((*DC)[i]->GetHitID2());
      ++tt_SiDigit_n;
      //G4cout << " " << IsX << "|" << NPlane  << "|" << NStrip << "|"  << EChannel 
      //	     << "|"  << EChannelPrim << "|"  << (*DC)[i]->GetPrimTrackID() << G4endl;
      //G4int NChannel = NStrip + (NPlane*2 + IsX)*6144;
      //G4cout << " location " << i << "  strip number in layer " << NStrip << " channel number "  << NChannel  << G4endl;

    }
  }
  //G4cout << "Total Silicon Digits " << tt_SiDigit_n << G4endl;
  if(tt_cal_totE < 4500.) toKeep = false;
  if (tree && toKeep) tree->Fill();

}






