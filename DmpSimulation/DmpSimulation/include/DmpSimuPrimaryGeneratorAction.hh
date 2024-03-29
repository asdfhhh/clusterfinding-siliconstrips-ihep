#ifndef DmpSimuPrimaryGeneratorAction_h
#define DmpSimuPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"

class G4Event;
class DmpDetectorConstruction;
class DmpSimuPrimaryGeneratorMessenger;
class G4GeneralParticleSource;

class DmpSimuPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:

  DmpSimuPrimaryGeneratorAction();    
  ~DmpSimuPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);
  void SetRndmFlag(G4String val)     { rndmFlag      = val;}
  void SetSourceType(G4int val)      { nSourceType   = val;}
  void SetSpectrumType(G4int val)    { nSpectrumType = val;}
  void SetVertexRadius(G4double val) { dVertexRadius = val;}
  void SetSourceGen(G4bool val)      { sourceGen     = val;}
  G4ParticleDefinition* GetParticleDefinition() {
    return particleGun->GetParticleDefinition();
  }

private:
  G4ParticleGun*                particleGun;
  G4GeneralParticleSource*      particleSource;	  
  DmpDetectorConstruction*      dmpDetector;  
  DmpSimuPrimaryGeneratorMessenger* gunMessenger; 
  G4String                      rndmFlag;    //flag for a random impact point (not used)
  G4int                         nSourceType;
  G4double                      dVertexRadius;
  G4int                         nSpectrumType;
  G4bool                        sourceGen; // false for GeneralParticleSource
  
};

#endif



