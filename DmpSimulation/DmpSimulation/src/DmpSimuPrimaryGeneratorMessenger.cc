// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpSimuPrimaryGeneratorAction
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpSimuPrimaryGeneratorMessenger.hh"

#include "DmpSimuPrimaryGeneratorAction.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"

DmpSimuPrimaryGeneratorMessenger::DmpSimuPrimaryGeneratorMessenger
(DmpSimuPrimaryGeneratorAction* action)
  :dmpSimuPrimaryGeneratorAction(action)
{ 
  //not used
  RndmCmd = new G4UIcmdWithAString("/gun/random",this);
  RndmCmd->SetGuidance("Shoot randomly the incident particle.");
  RndmCmd->SetGuidance("  Choice : on(default), off");
  RndmCmd->SetParameterName("choice",true);
  RndmCmd->SetDefaultValue("on");
  RndmCmd->SetCandidates("on off");
  RndmCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SourceTypeCmd = new G4UIcmdWithAnInteger("/gun/sourceType",this);
  SourceTypeCmd->SetGuidance("Select the type of incident flux.");
  SourceTypeCmd->SetGuidance("  Choice : 0(default), 1(isotropic sphere), 2(isotropic 90-45 degree incident angle), 3(wide parallel beam)");
  SourceTypeCmd->SetParameterName("choice",true);
  SourceTypeCmd->SetDefaultValue((G4int)0);
  SourceTypeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VertexRadiusCmd = new G4UIcmdWithADoubleAndUnit("/gun/vertexRadius",this);
  VertexRadiusCmd->SetGuidance("Radius (and unit) of sphere for vertices of incident flux.");
  VertexRadiusCmd->SetParameterName("choice",true);
  VertexRadiusCmd->SetDefaultValue((G4double)1.*cm);
  VertexRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SpectrumTypeCmd = new G4UIcmdWithAnInteger("/gun/spectrumType",this);
  SpectrumTypeCmd->SetGuidance("Select the type of incident spectrum.");
  SpectrumTypeCmd->SetGuidance("  Choice : 0(default), 1(), 2(E^{-gamma}), 3()");
  SpectrumTypeCmd->SetParameterName("choice",true);
  SpectrumTypeCmd->SetDefaultValue((G4int)0);
  SpectrumTypeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SourceGenCmd = new G4UIcmdWithABool("/gun/sourceGen",this);
  SourceGenCmd->SetGuidance("Select the native Generation");
  SourceGenCmd->SetGuidance("  Choice : true(native), false(GPS)");
  SourceGenCmd->SetParameterName("choice",true);
  SourceGenCmd->SetDefaultValue((G4bool)true);
  SourceGenCmd->AvailableForStates(G4State_PreInit);

}

DmpSimuPrimaryGeneratorMessenger::~DmpSimuPrimaryGeneratorMessenger()
{
  delete RndmCmd;
  delete SourceTypeCmd;
  delete VertexRadiusCmd;
  delete SpectrumTypeCmd;
  delete SourceGenCmd;
}

void DmpSimuPrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  if( command == RndmCmd )
    { dmpSimuPrimaryGeneratorAction->SetRndmFlag(newValue);}
  
  if( command == SourceTypeCmd )
    { dmpSimuPrimaryGeneratorAction->SetSourceType(SourceTypeCmd->GetNewIntValue(newValue));}
  
  if( command == VertexRadiusCmd )
    { dmpSimuPrimaryGeneratorAction->SetVertexRadius(VertexRadiusCmd->GetNewDoubleValue(newValue));}
  
  if( command == SpectrumTypeCmd )
    { dmpSimuPrimaryGeneratorAction->SetSpectrumType(SpectrumTypeCmd->GetNewIntValue(newValue));}

  if( command == SourceGenCmd )
    { dmpSimuPrimaryGeneratorAction->SetSourceGen(SourceGenCmd->GetNewBoolValue(newValue));}
}













