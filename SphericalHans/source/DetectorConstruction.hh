/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Detector construction and complementary definitions
//
// --------------------------------------------------------------
// Comments:
//
//   - 24/05/05 Created based on calGamma simulation
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __DetectorBuilder
#define __DetectorBuilder

#include "G4VUserDetectorBuilder.hh"

#include "globals.hh"

class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4LogicalVolume;
class G4VPhysicalVolume;
class DetectorMessenger;
class GasSD;

class DetectorBuilder : public G4VUserDetectorBuilder {  
private:

  // Volumes
  G4Box* solidWorld;

  // Logical volumes
  G4LogicalVolume* worldLog;      //pointer to logic world
  
  // Physical volumes
  G4VPhysicalVolume* worldPhys;   //pointer to physical world

  // Physical volumes
  G4VPhysicalVolume* detectorPhys;   //pointer to physical converter

  // Materials
  G4Material* mediumMaterial;
  G4Material* detectorMaterial;
  G4Material* defaultMaterial;

  // detector features
  G4double detectorOuterRadius;
  G4double detectorHalfLengthZ;  

  DetectorMessenger* DMessenger;  //pointer to the Messenger

  void DefineMaterials();
  G4VPhysicalVolume* ConstructSetup();

public:
  
  DetectorBuilder();
  ~DetectorBuilder();
  
  G4VPhysicalVolume* Construct();
  
  void SetDetectorMaterial(G4String);     
  void SetMediumMaterial(G4String);

  void SetDetectorOuterRadius(G4double val){detectorOuterRadius = val;}
  void SetDetectorHalfLengthZ(G4double val){detectorHalfLengthZ = val;}

  void UpdateGeometry();

  const G4VPhysicalVolume* GetDetectorPhys() {return detectorPhys;};

  G4Material* GetDetectorMaterial() {return detectorMaterial;};
  G4Material* GetMediumMaterial() {return mediumMaterial;};
  
  void PrintDetectorParameters();
};

#endif

