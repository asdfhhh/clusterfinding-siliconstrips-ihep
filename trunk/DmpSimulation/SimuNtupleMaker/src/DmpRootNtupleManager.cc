// Description: manager for output data to a ROOT ntuple
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpRootNtupleManager.hh"

#include "DmpSimuRunEventNtupleMaker.hh"
#include "DmpSimuPrimariesNtupleMaker.hh"
#include "DmpSimuStkStepNtupleMaker.hh"
#include "DmpSimuTrajectoryNtupleMaker.hh"
#include "DmpSimuBgoHitNtupleMaker.hh"
#include "DmpSimuStkHitNtupleMaker.hh"
#include "DmpSimuStkDigiNtupleMaker.hh"

#include "TFile.h"
#include "TTree.h"

DmpRootNtupleManager::DmpRootNtupleManager()
:rootFile(0),tree(0)
{
      
  dmpSimuRunEventNtupleMaker     = new DmpSimuRunEventNtupleMaker();
  dmpSimuPrimariesNtupleMaker    = new DmpSimuPrimariesNtupleMaker();
  dmpSimuStkStepNtupleMaker      = new DmpSimuStkStepNtupleMaker();
  dmpSimuTrajectoryNtupleMaker   = new DmpSimuTrajectoryNtupleMaker();
  dmpSimuBgoHitNtupleMaker       = new DmpSimuBgoHitNtupleMaker();
  dmpSimuStkHitNtupleMaker       = new DmpSimuStkHitNtupleMaker();
  dmpSimuStkDigiNtupleMaker      = new DmpSimuStkDigiNtupleMaker();

}

DmpRootNtupleManager::~DmpRootNtupleManager()
{
  if ( rootFile ) delete rootFile;
  delete dmpSimuRunEventNtupleMaker;
  delete dmpSimuPrimariesNtupleMaker;
  delete dmpSimuStkStepNtupleMaker;
  delete dmpSimuTrajectoryNtupleMaker;
  delete dmpSimuBgoHitNtupleMaker;
  delete dmpSimuStkHitNtupleMaker;
  delete dmpSimuStkDigiNtupleMaker;

}

void DmpRootNtupleManager::book(const G4Run* aRun)
{ 
 
 // Creating a tree container to handle histograms and ntuples.
 // This tree is associated to an output file.
 //
 G4String fileName = "DmpSimu.root";
 rootFile = new TFile(fileName,"RECREATE");
 if(!rootFile) {
   G4cout << " DmpRootNtupleManager::book : problem creating the ROOT TFile " << G4endl;
   return;
 }
 G4cout << "\n----> Output ntuple file is opened in " << fileName << G4endl;


 // create 1 ntuple in subdirectory "tuples"
 tree = new TTree("dampe", "dampe tracker");

 //book ntuple branches and define ntuple data vectors here 
 dmpSimuRunEventNtupleMaker    ->book(aRun, tree);
 dmpSimuPrimariesNtupleMaker   ->book(aRun, tree);
 dmpSimuStkStepNtupleMaker     ->book(aRun, tree);
 dmpSimuTrajectoryNtupleMaker  ->book(aRun, tree);
 dmpSimuBgoHitNtupleMaker      ->book(aRun, tree);
 dmpSimuStkHitNtupleMaker      ->book(aRun, tree);
 dmpSimuStkDigiNtupleMaker     ->book(aRun, tree);

}

void DmpRootNtupleManager::beginEvent(const G4Event* evt)
{
  //clear all ntuple data vectors here
  dmpSimuRunEventNtupleMaker    ->beginEvent(evt);
  dmpSimuPrimariesNtupleMaker   ->beginEvent(evt);
  dmpSimuStkStepNtupleMaker     ->beginEvent(evt);
  dmpSimuTrajectoryNtupleMaker  ->beginEvent(evt);
  dmpSimuBgoHitNtupleMaker      ->beginEvent(evt);
  dmpSimuStkHitNtupleMaker      ->beginEvent(evt);
  dmpSimuStkDigiNtupleMaker     ->beginEvent(evt);

}

void DmpRootNtupleManager::save()
{ 
  if (rootFile) {
    rootFile->Write();        // Writing the histograms to the file
    rootFile->Close();        // and closing the tree (and the file)
    G4cout << "\n----> ntuple Tree is saved \n" << G4endl;
  }
}

void DmpRootNtupleManager::FillStep(const G4Step* aStep)
{
  dmpSimuStkStepNtupleMaker ->FillStep(aStep);
}

void DmpRootNtupleManager::FillEvent(const G4Event* evt)
{  
  //fill even info here, also filter and save ntuple
  bool toKeep = true;

  dmpSimuRunEventNtupleMaker    ->FillEvent(evt);
  dmpSimuPrimariesNtupleMaker   ->FillEvent(evt);
  dmpSimuTrajectoryNtupleMaker  ->FillEvent(evt);
  dmpSimuBgoHitNtupleMaker      ->FillEvent(evt);
  dmpSimuStkHitNtupleMaker      ->FillEvent(evt);
  dmpSimuStkDigiNtupleMaker     ->FillEvent(evt);

  if(!dmpSimuBgoHitNtupleMaker->passTotalEnergyCut(4500.)) toKeep = false;
  if (tree && toKeep) tree->Fill();

}






