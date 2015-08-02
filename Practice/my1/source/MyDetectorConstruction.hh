#ifndef _MyDetectorConstruction_h
#define _MyDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"

class G4Sphere;
class G4Material;
class G4LogicalVolume;
class G4VPhysicalVolume;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const;
    
private:
    G4double _rinner;
    G4double _router;
    G4double _thickness;
    G4String _material;
    G4LogicalVolume* _scoringVolume;
};

inline G4LogicalVolume* MyDetectorConstruction::GetScoringVolume() const { return _scoringVolume; }

#endif

