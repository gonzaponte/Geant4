#include "MyDetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


MyDetectorConstruction::MyDetectorConstruction() :
G4VUserDetectorConstruction(),
_rinner( 1.00 * m ),
_router( 1.01 * m ),
_thickness( 1.0 * mm ),
_material( "G4_Xe" ),
_scoringVolume(0)
{ }

MyDetectorConstruction::~MyDetectorConstruction()
{ }

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();
    G4Material*     air = nist->FindOrBuildMaterial("G4_AIR");
    
    
    //
    //
    //    WORLD
    //
    //
    G4double size = 1.5 * _router;
    G4Box* world = new G4Box( "World", size, size, size );
    G4LogicalVolume* logWorld = new G4LogicalVolume( world, air, "logWorld" );
    G4VPhysicalVolume* physWorld = new G4PVPlacement( 0, G4ThreeVector(), // rotation, pos
                                                      logWorld, "physWorld", // name
                                                      0, false, // mother volume, bool operations
                                                      0, true );// copy number, check overlaping

    
    //
    //
    //    INNER SPHERE
    //
    //
    
    G4Material* iron = nist->FindOrBuildMaterial("G4_Fe");
    G4VSolid* innerSphere = new G4Sphere( "innersphere", _rinner, _rinner + _thickness,
                                          0. * rad, twopi * rad, 0. * rad,    pi * rad );
    
    G4LogicalVolume*  innerlog = new G4LogicalVolume( innerSphere, iron, "innerlog" );

    new G4PVPlacement( 0, G4ThreeVector(),
                       innerlog, "innerphys",
                       logWorld, false, 0, true );
    //
    //
    //    OUTER SPHERE
    //
    //
    G4VSolid* outerSphere = new G4Sphere( "outersphere", _router, _router + _thickness,
                                          0. * rad, twopi * rad, 0. * rad,    pi * rad );
    
    G4LogicalVolume*  outerlog = new G4LogicalVolume( outerSphere, iron, "outerlog" );
    
    new G4PVPlacement( 0, G4ThreeVector(),
                       outerlog, "outerphys",
                       logWorld, false, 0, true );

    //
    //
    //    DETECTION VOLUME
    //
    //
    G4Material* lAr = nist->FindOrBuildMaterial( _material );
    G4VSolid* detectionMaterial = new G4Sphere( "detection", _rinner + _thickness, _router,
                                                0. * rad, twopi * rad, 0. * rad,    pi * rad );
    
    G4LogicalVolume*  detectionlog = new G4LogicalVolume( detectionMaterial, lAr, "detectionlog" );
    
    new G4PVPlacement( 0, G4ThreeVector(),
                       detectionlog, "detectionphys",
                       logWorld, false, 0, true );

    
    
    _scoringVolume = detectionlog;
    return physWorld;
    
}

