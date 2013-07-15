// $Id: DmpSimu.cc,v 1.00 2013-07-09 17:42:50 xin Exp $
//
// 
// ------------------------------------------------------------
//      GEANT 4 main program
//      DPNC U. Geneva Switzerland
//
//
//      ------------ DmpSimu main program ------
//           by X.Wu, (9 July 2013)
//  09.07.13 X.Wu: DAMPE detector simulation executable based on GammaRayTel 
//                     
// ************************************************************

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "DmpRootNtupleManager.hh"

//#include "DmpSimuPhysicsList.hh"

#include "DmpDetectorConstruction.hh"
#include "DmpSimuPrimaryGeneratorAction.hh"
#include "DmpSimuRunAction.hh"
#include "DmpSimuTrackingAction.hh"
#include "DmpSimuSteppingAction.hh"
#include "DmpSimuEventAction.hh"

#include "QGSP_BIC.hh"
//#include "QGSP_BERT.hh"

// This is the main function 
int main(int argc, char** argv)
{
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;
  
  // set an ROOT ntuple manager
  DmpRootNtupleManager*  ntupleMgr = new DmpRootNtupleManager();
  
  // Set mandatory user initialization classes
  DmpDetectorConstruction* detector = new DmpDetectorConstruction;
  runManager->SetUserInitialization(detector);
 
  // DmpSimuPhysicsList to be implemented   
  //runManager->SetUserInitialization(new DmpSimuPhysicsList);
  //runManager->SetUserInitialization(new QGSP_BERT);
  runManager->SetUserInitialization(new QGSP_BIC);

  
  // Set mandatory user action classes
  runManager->SetUserAction(new DmpSimuPrimaryGeneratorAction);

  // Set optional user action classes
  DmpSimuRunAction* runAction = new DmpSimuRunAction(ntupleMgr);
  runManager->SetUserAction(runAction);
  
  DmpSimuEventAction* eventAction = new DmpSimuEventAction(ntupleMgr);
  runManager->SetUserAction(eventAction);
  
  DmpSimuTrackingAction* tracking_action = new DmpSimuTrackingAction();
  runManager->SetUserAction(tracking_action);
  
  DmpSimuSteppingAction* stepping_action = new DmpSimuSteppingAction(ntupleMgr);
  runManager->SetUserAction(stepping_action);
  
  // Set visualization (not tested)
#ifdef G4VIS_USE
  // Visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif  
  
  // Get the pointer to the UI manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  G4String command = "/control/execute ";
  for (int i=2; i<=argc; i++) 
    {
      G4String macroFileName = argv[i-1];
      UImanager->ApplyCommand(command+macroFileName);
    }

  // Job termination
  delete ntupleMgr;       
         
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  return 0;
}
