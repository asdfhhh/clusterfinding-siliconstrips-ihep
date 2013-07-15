#ifndef DmpRootNtupleManager_h
#define DmpRootNtupleManager_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"

 class TFile;
 class TTree;
 class TH1D;

class DmpRootNtupleManager
{
  public:
  
    DmpRootNtupleManager();
   ~DmpRootNtupleManager();
   
    void book();
    void save();

    void beginEvent(const G4Event* evt);
    void FillStep(const G4Step* aStep);
    void FillEvent(const G4Event* evt);        

 private:
  
  TFile*   rootFile;
  TTree*   tree;    

  G4int  debugEvent;

  G4int  eventNumber;

  G4bool is_pvtrack;
  G4bool is_eletrack;
  G4bool is_postrack;
  G4bool is_backtrack;
  G4int  pvtrackID;
  G4int  eletrackID;
  G4int  postrackID;
  G4int  currentTrackID;

  int tt_run;
  int tt_event;
  int tt_nhits;
  int tt_npv;

  G4double tt_cal_totE;
  G4double tt_cal_totE_1MeV;
  G4double tt_cal_totE_10MeV;

  G4double tt_pv_x, tt_pv_y, tt_pv_z;
  int tt_npvpart;
  G4double tt_pvpart_px, tt_pvpart_py, tt_pvpart_pz, tt_pvpart_ekin, tt_pvpart_q;
  int tt_pvpart_pdg;

  G4double tt_pvtrj_stop_x, tt_pvtrj_stop_y, tt_pvtrj_stop_z;
  int tt_pvtrj_trackID;
  std::string tt_pvtrj_stop_vo;
  int tt_pvtrj_stop_index;

  G4double tt_ele_px, tt_ele_py, tt_ele_pz, tt_ele_ekin;
  G4double tt_ele_stop_x, tt_ele_stop_y, tt_ele_stop_z;
  int tt_ele_trackID, tt_ele_parentID;
  std::string tt_ele_stop_vo;
  int tt_ele_stop_index;

  G4double tt_pos_px, tt_pos_py, tt_pos_pz, tt_pos_ekin;
  G4double tt_pos_stop_x, tt_pos_stop_y, tt_pos_stop_z;
  int tt_pos_trackID, tt_pos_parentID; 
  std::string tt_pos_stop_vo;
  int tt_pos_stop_index;

  G4double eDepositAcc_pvtrack;
  G4double eDepositAcc_ele;
  G4double eDepositAcc_pos;
  G4double eDepositAcc_back;
  int tt_stepping_ntracks;
  std::vector<int>*       tt_stepping_trackID;
  std::vector<int>*       tt_stepping_trackPDG;
  std::vector<int>*       tt_stepping_parentID;
 
  int tt_pvtrack_nsteps;
  std::vector<double>*    tt_step_pvtrack_px;
  std::vector<double>*    tt_step_pvtrack_py;
  std::vector<double>*    tt_step_pvtrack_pz;
  std::vector<double>*    tt_step_pvtrack_ekin;
  std::vector<double>*    tt_step_pvtrack_x;
  std::vector<double>*    tt_step_pvtrack_y;
  std::vector<double>*    tt_step_pvtrack_z;
  std::vector<double>*    tt_step_pvtrack_stepLength;
  std::vector<double>*    tt_step_pvtrack_trackLength;
  std::vector<double>*    tt_step_pvtrack_energyDeposit;
  std::vector<int>*       tt_step_pvtrack_stepNumber;
  std::vector<G4bool>*    tt_step_pvtrack_isEntering;
  std::vector<int>*       tt_step_pvtrack_thisIndex;
  std::vector<int>*       tt_step_pvtrack_nextIndex;
  std::vector<std::string>*  tt_step_pvtrack_thisVolume;
  std::vector<std::string>*  tt_step_pvtrack_nextVolume;

  int tt_back_nsteps;
  std::vector<int>*       tt_step_back_pdg;
  std::vector<int>*       tt_step_back_trackID;
  std::vector<double>*    tt_step_back_px;
  std::vector<double>*    tt_step_back_py;
  std::vector<double>*    tt_step_back_pz;
  std::vector<double>*    tt_step_back_ekin;
  std::vector<double>*    tt_step_back_x;
  std::vector<double>*    tt_step_back_y;
  std::vector<double>*    tt_step_back_z;
  std::vector<int>*       tt_step_back_stepNumber;
  std::vector<G4bool>*    tt_step_back_isEntering;
  std::vector<int>*       tt_step_back_thisIndex;
  std::vector<int>*       tt_step_back_nextIndex;
  std::vector<std::string>*  tt_step_back_thisVolume;
  std::vector<std::string>*  tt_step_back_nextVolume;
  std::vector<double>*    tt_step_back_stepLength;
  std::vector<double>*    tt_step_back_trackLength;
  std::vector<double>*    tt_step_back_energyDeposit;

  int tt_ele_nsteps;
  std::vector<double>*    tt_step_ele_px;
  std::vector<double>*    tt_step_ele_py;
  std::vector<double>*    tt_step_ele_pz;
  std::vector<double>*    tt_step_ele_ekin;
  std::vector<double>*    tt_step_ele_x;
  std::vector<double>*    tt_step_ele_y;
  std::vector<double>*    tt_step_ele_z;
  std::vector<int>*       tt_step_ele_stepNumber;
  std::vector<G4bool>*    tt_step_ele_isEntering;
  std::vector<int>*       tt_step_ele_thisIndex;
  std::vector<int>*       tt_step_ele_nextIndex;
  std::vector<std::string>*  tt_step_ele_thisVolume;
  std::vector<std::string>*  tt_step_ele_nextVolume;
  std::vector<double>*    tt_step_ele_stepLength;
  std::vector<double>*    tt_step_ele_trackLength;
  std::vector<double>*    tt_step_ele_energyDeposit;

  int tt_pos_nsteps;
  std::vector<double>*    tt_step_pos_px;
  std::vector<double>*    tt_step_pos_py;
  std::vector<double>*    tt_step_pos_pz;
  std::vector<double>*    tt_step_pos_ekin;
  std::vector<double>*    tt_step_pos_x;
  std::vector<double>*    tt_step_pos_y;
  std::vector<double>*    tt_step_pos_z;
  std::vector<int>*       tt_step_pos_stepNumber;
  std::vector<G4bool>*    tt_step_pos_isEntering;
  std::vector<int>*       tt_step_pos_thisIndex;
  std::vector<int>*       tt_step_pos_nextIndex;
  std::vector<std::string>*  tt_step_pos_thisVolume;
  std::vector<std::string>*  tt_step_pos_nextVolume;
  std::vector<double>*    tt_step_pos_stepLength;
  std::vector<double>*    tt_step_pos_trackLength;
  std::vector<double>*    tt_step_pos_energyDeposit;

  int tt_CalLayer_nlayer;
  std::vector<double>*    tt_CalLayer_centroid;
  std::vector<double>*    tt_CalLayer_e;
  std::vector<double>*    tt_CalLayer_sumw2;
  std::vector<int>*       tt_CalLayer_index;

  int tt_CalLayer_nlayer_1MeV;
  std::vector<double>*    tt_CalLayer_centroid_1MeV;
  std::vector<double>*    tt_CalLayer_e_1MeV;
  std::vector<double>*    tt_CalLayer_sumw2_1MeV;
  std::vector<int>*       tt_CalLayer_index_1MeV;

  int tt_SiHit_n;
  std::vector<int>*    tt_SiHit_strip;
  std::vector<int>*    tt_SiHit_id;
  std::vector<unsigned int>*    tt_SiHit_trackID;
  std::vector<unsigned int>*    tt_SiHit_trackID1;
  std::vector<unsigned int>*    tt_SiHit_trackID2;
  std::vector<int>*    tt_SiHit_ntracks;
  std::vector<int>*    tt_SiHit_ntracksBack;
  std::vector<int>*    tt_SiHit_ntracksPrim;
  std::vector<double>* tt_SiHit_e;
  std::vector<double>* tt_SiHit_e_prim;
  std::vector<double>* tt_SiHit_x;
  std::vector<double>* tt_SiHit_y;
  std::vector<double>* tt_SiHit_z;

  int tt_SiDigit_n;
  std::vector<int>*    tt_SiDigit_strip;
  std::vector<unsigned int>*    tt_SiDigit_trackID;
  std::vector<double>* tt_SiDigit_e;
  std::vector<double>* tt_SiDigit_e_prim;
  std::vector<int>*    tt_SiDigit_ntracks;
  std::vector<int>*    tt_SiDigit_ntracksBack;
  std::vector<int>*    tt_SiDigit_ntracksPrim;
  std::vector<int>*    tt_SiDigit_nhits;
  std::vector<int>*    tt_SiDigit_nhitsBack;
  std::vector<int>*    tt_SiDigit_hitID;
  std::vector<int>*    tt_SiDigit_hitID1;
  std::vector<int>*    tt_SiDigit_hitID2;

};


#endif

