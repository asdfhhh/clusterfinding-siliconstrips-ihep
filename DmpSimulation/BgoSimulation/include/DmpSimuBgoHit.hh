#ifndef DmpSimuBgoHit_h
#define DmpSimuBgoHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuBgoHit : public G4VHit
{
public:
  
  DmpSimuBgoHit();
  ~DmpSimuBgoHit();
  DmpSimuBgoHit(const DmpSimuBgoHit&);
  const DmpSimuBgoHit& operator=(const DmpSimuBgoHit&);
  int operator==(const DmpSimuBgoHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4double EdepCAL;      // Energy deposited on the BGO bar
  G4ThreeVector pos;     // Position of the hit
  G4int CALBarNumber;    // Number of the BGO bars
  G4int CALPlaneNumber;  // Number of the BGO planes
  G4int IsCALPlane;      // Type of the plane (0 X, 1 Y)

public:
  
  inline void AddEnergy(G4double de) {EdepCAL += de;};
  inline void SetCALBarNumber(G4int i) {CALBarNumber = i;};
  inline void SetCALPlaneNumber(G4int i) {CALPlaneNumber = i;};
  inline void SetCALType(G4int i) {IsCALPlane = i;};
  inline void SetPos(G4ThreeVector xyz){ pos = xyz; }
  
  inline G4double GetEdepCAL()     { return EdepCAL; };
  inline G4int    GetCALBarNumber()   { return CALBarNumber; };
  inline G4int    GetCALPlaneNumber()   { return CALPlaneNumber; };
  inline G4int    GetCALType()   {return IsCALPlane;};      
  inline G4ThreeVector GetPos() { return pos; };
  
};

typedef G4THitsCollection<DmpSimuBgoHit> DmpSimuBgoHitsCollection;

extern G4Allocator<DmpSimuBgoHit> DmpSimuBgoHitAllocator;

inline void* DmpSimuBgoHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) DmpSimuBgoHitAllocator.MallocSingle();
  return aHit;
}

inline void DmpSimuBgoHit::operator delete(void* aHit)
{
  DmpSimuBgoHitAllocator.FreeSingle((DmpSimuBgoHit*) aHit);
}

#endif










