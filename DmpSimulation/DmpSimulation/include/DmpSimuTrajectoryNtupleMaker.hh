#ifndef DmpSimuTrajectoryNtupleMaker_h
#define DmpSimuTrajectoryNtupleMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimuTrajectoryNtupleMaker
{
public:
  
  DmpSimuTrajectoryNtupleMaker();
  ~DmpSimuTrajectoryNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree*   tree;    
  G4int  debugEvent;
  G4int  eventNumber;

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


};


#endif
