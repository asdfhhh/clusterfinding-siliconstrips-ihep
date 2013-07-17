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
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
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
  //Initialize G4 kernel
	runManager->Initialize();
// get the pointer to the User Interface manager 
	G4UImanager* UI = G4UImanager::GetUIpointer(); 
   
	G4UIsession* session = 0;
	session = new G4UIterminal(new G4UItcsh);      
	//UI->ApplyCommand("/control/execute vis.mac");
	session->SessionStart();
	delete session;
   // Job termination
  delete ntupleMgr;       
         
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  return 0;
}
