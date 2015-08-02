#ifndef _MyPrimaryGeneratorAction_h
#define _MyPrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

class G4ParticleGun;
class G4Event;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    
public:
    MyPrimaryGeneratorAction( const G4String& particleName = "geantino",
                              G4double energy = 10. * GeV,
                              G4ThreeVector position = G4ThreeVector( 0., 0., 0. ),
                              G4ThreeVector momentumDirection = G4ThreeVector( 0., 0., 1. ) );
    
    ~MyPrimaryGeneratorAction();
    
    // methods
    virtual void GeneratePrimaries( G4Event* );
    const G4ParticleGun* GetParticleGun() const;
    
private:
    // data members
    G4ParticleGun*  _particleGun; //pointer a to G4 service class
};

inline const G4ParticleGun* MyPrimaryGeneratorAction::GetParticleGun() const { return _particleGun; }

#endif

