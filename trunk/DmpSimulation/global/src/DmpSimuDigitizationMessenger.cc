// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpSimuDigitization
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpSimuDigitizationMessenger.hh"

#include "DmpSimuDigitization.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DmpSimuDigitizationMessenger::DmpSimuDigitizationMessenger
(DmpSimuDigitization* digitizer)
  :dmpSimuDigitizer(digitizer)
{ 
  ThresholdCmd = new G4UIcmdWithADoubleAndUnit("/digitizer/Threshold",this);
  ThresholdCmd->SetGuidance("Energy deposition threshold for TKR digi generation");
  ThresholdCmd->SetParameterName("choice",true);
  ThresholdCmd->SetDefaultValue((G4double)20.*keV);
  ThresholdCmd->SetRange("Threshold >=0.");
  ThresholdCmd->SetUnitCategory("Energy");  
  ThresholdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DmpSimuDigitizationMessenger::~DmpSimuDigitizationMessenger()
{
  delete ThresholdCmd;
}

void DmpSimuDigitizationMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  if( command == ThresholdCmd )
    { 
      dmpSimuDigitizer->SetThreshold
	(ThresholdCmd->GetNewDoubleValue(newValue));
    }
}












