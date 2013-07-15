#ifndef DmpSimuDigitizationMessenger_h
#define DmpSimuDigitizationMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DmpSimuDigitization;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class DmpSimuDigitizationMessenger: public G4UImessenger
{
public:
  DmpSimuDigitizationMessenger(DmpSimuDigitization*);
  ~DmpSimuDigitizationMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpSimuDigitization* dmpSimuDigitizer; 
  G4UIcmdWithADoubleAndUnit*  ThresholdCmd;

};

#endif


