#ifndef DmpRootNtupleManager_h
#define DmpRootNtupleManager_h 1

#include <vector>
#include "globals.hh"
#include "G4Run.hh"
#include "G4Event.hh"

class DmpSimuRunEventNtupleMaker;
class DmpSimuPrimariesNtupleMaker;
class DmpSimuStkStepNtupleMaker;
class DmpSimuTrajectoryNtupleMaker;
class DmpSimuBgoHitNtupleMaker;
class DmpSimuStkHitNtupleMaker;
class DmpSimuStkDigiNtupleMaker;

class TFile;
class TTree;
class TH1D;

class DmpRootNtupleManager
{
  public:
  
    DmpRootNtupleManager();
   ~DmpRootNtupleManager();
   
    void book(const G4Run* aRun);
    void save();

    void beginEvent(const G4Event* evt);
    void FillStep(const G4Step* aStep);
    void FillEvent(const G4Event* evt);        

 private:
  
  DmpSimuRunEventNtupleMaker*     dmpSimuRunEventNtupleMaker;
  DmpSimuPrimariesNtupleMaker*    dmpSimuPrimariesNtupleMaker;
  DmpSimuStkStepNtupleMaker*      dmpSimuStkStepNtupleMaker;
  DmpSimuTrajectoryNtupleMaker*   dmpSimuTrajectoryNtupleMaker;
  DmpSimuBgoHitNtupleMaker*       dmpSimuBgoHitNtupleMaker;
  DmpSimuStkHitNtupleMaker*       dmpSimuStkHitNtupleMaker;
  DmpSimuStkDigiNtupleMaker*      dmpSimuStkDigiNtupleMaker;

  TFile*   rootFile;
  TTree*   tree;    

};


#endif

