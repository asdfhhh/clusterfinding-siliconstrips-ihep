#ifndef DmpSimuDigitization_h
#define DmpSimuDigitization_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimuStkDigi.hh"
#include "DmpSimuPsdDigi.hh"
#include "globals.hh"
//#include "g4std/vector"

class DmpSimuDigitizationMessenger;
class DmpDetectorConstruction;

class DmpSimuDigitization : public G4VDigitizerModule
{
public:
  
  DmpSimuDigitization(G4String name);
  ~DmpSimuDigitization();
  
  void Digitize();
  void SetThreshold(G4double val) { Energy_Threshold = val;}
  //  inline G4int* GetThitID() {return ThitID;}

private:
  
  DmpSimuStkDigitsCollection*  DigitsCollection;
  DmpSimuPsdDigitsCollection*  PSDDigitsCollection;

  G4double Energy_Threshold; // for TKR digi
  DmpSimuDigitizationMessenger* digiMessenger;

  DmpDetectorConstruction* dmpDetector;
  /***
  G4int (*ThitID);
  
  G4int NbOfTKRLayers;
  G4int NbOfTKRStrips;
  G4int NbOfTKRChannels;
  G4int NbOfTKRChannelsL;
  ***/
};

#endif








