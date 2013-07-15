// Description: This class hinerits from G4VSensitiveDetector. It is used to
// build the PSD sensitive area geometry and produce DmpSimuPsdHit collection
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "G4RunManager.hh"
#include "DmpPsdSensitiveDetector.hh"
#include "DmpSimuPsdHit.hh"
#include "DmpDetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DmpPsdSensitiveDetector::DmpPsdSensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{
  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
  NbOfACDTopTiles      =  (dmpDetector->GetPsdDetectorDescription())->GetNbOfPSDTopTiles(); 

  HitTopID = new G4int[NbOfACDTopTiles];
  collectionName.insert("PSDHitCollection");
}

DmpPsdSensitiveDetector::~DmpPsdSensitiveDetector()
{
  delete [] HitTopID;
}

void DmpPsdSensitiveDetector::Initialize(G4HCofThisEvent*)
{
  PSDHitCollection = new DmpSimuPsdHitsCollection
    (SensitiveDetectorName,collectionName[0]);
   
  for (G4int j=0;j<NbOfACDTopTiles;j++) 
    {
      
      HitTopID[j] = -1;
    };
}

G4bool DmpPsdSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{ 

  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      
  
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* acd_tile = theTouchable->GetVolume();  

  G4int StripNumber=acd_tile->GetCopyNo();
  G4String PSDName = acd_tile->GetName();
  
  //G4cout << PSDTileName << " " << edep/keV << G4endl;

  if (PSDName == "PSD" )
    {
      // This is a new hit
      if (HitTopID[StripNumber]==-1)
	{       
	  DmpSimuPsdHit* PSSDHit = new DmpSimuPsdHit;
	  PSSDHit->AddEnergy(edep);
	  PSSDHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  PSSDHit->SetStripNumber(StripNumber);
	  HitTopID[StripNumber] = 
	    PSDHitCollection->insert(PSSDHit) -1;
	}
      else // This is not new
	{
	  (*PSDHitCollection)
	    [HitTopID[StripNumber]]->AddEnergy(edep);
	}
    }
 
  return true;
}

void DmpPsdSensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE)
{
  static G4int HCID = -1;
  if(HCID<0)
    { 
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
  HCE->AddHitsCollection(HCID,PSDHitCollection);

  for (G4int j=0;j<NbOfACDTopTiles;j++) 
    {
      HitTopID[j] = -1;
    };

}

void DmpPsdSensitiveDetector::clear()
{} 

void DmpPsdSensitiveDetector::DrawAll()
{} 

void DmpPsdSensitiveDetector::PrintAll()
{} 















