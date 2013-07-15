// Description: This class hinerits from  G4VHit. It is used to
// store the MC hit information of the BGO 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "DmpSimuBgoHit.hh"

G4Allocator<DmpSimuBgoHit> DmpSimuBgoHitAllocator;

DmpSimuBgoHit::DmpSimuBgoHit()
{
  EdepCAL = 0.; 
  CALBarNumber = 0;
  CALPlaneNumber = 0;
  IsCALPlane = 0;
  pos = G4ThreeVector(0.,0.,0.);
}

DmpSimuBgoHit::~DmpSimuBgoHit()
{;}

DmpSimuBgoHit::DmpSimuBgoHit(const DmpSimuBgoHit& right)
  :G4VHit()
{
  EdepCAL = right.EdepCAL; 
  CALBarNumber = right.CALBarNumber;
  CALPlaneNumber = right.CALPlaneNumber;
  IsCALPlane = right.IsCALPlane;
  pos = right.pos;
}

const DmpSimuBgoHit& DmpSimuBgoHit::operator=(const DmpSimuBgoHit& right)
{
  EdepCAL = right.EdepCAL; 
  CALBarNumber = right.CALBarNumber;
  CALPlaneNumber = right.CALPlaneNumber;
  IsCALPlane = right.IsCALPlane;
  pos = right.pos;
  return *this;
}

int DmpSimuBgoHit::operator==(const DmpSimuBgoHit& right) const
{
  return((EdepCAL==right.EdepCAL)&&(CALBarNumber==right.CALBarNumber)&&(CALPlaneNumber==right.CALPlaneNumber)&&(IsCALPlane==right.IsCALPlane)&& (pos==right.pos));
}

void DmpSimuBgoHit::Draw()
{;}

void DmpSimuBgoHit::Print()
{;}











