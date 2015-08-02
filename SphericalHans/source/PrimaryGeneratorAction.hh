/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol  hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
//*-- Modified by 
// --------------------------------------------------------------
// Description:
//   Actions to perform to generate a primary vertex
//
// --------------------------------------------------------------
// Comments:
//   - 25/11/04 Created based on example/novice/N01 structure
// 
// --------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////

#ifndef __PrimaryGeneratorAction
#define __PrimaryGeneratorAction

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Ions.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleMomentum.hh"
#include "globals.hh"

class G4Event;
class PrimaryGeneratorMessenger;
class DetectorConstruction;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
private:

  G4ParticleGun* particleGun;  
  G4ParticleTable* particleTable;
  PrimaryGeneratorMessenger* gunMessenger; // pointer to messenger 

  DetectorConstruction* detector;  //to get some geometrical info

  G4String distributionFlag;
  
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();
  
  void GeneratePrimaries(G4Event* anEvent);

  void SetDistributionFlag(G4String val) { distributionFlag = val;}
  
  void SetParticleDefinition(G4ParticleDefinition * aParticleDefinition)
     { particleGun->SetParticleDefinition(aParticleDefinition);}
  inline void SetParticleMomentum(G4ParticleMomentum aMomentum)
     { particleGun->SetParticleMomentum(aMomentum);}
  inline void SetParticleMomentumDirection(G4ParticleMomentum aMomentumDirection)
     { particleGun->SetParticleMomentumDirection(aMomentumDirection); }
  inline void SetParticleEnergy(G4double aKineticEnergy)
     { particleGun->SetParticleEnergy(aKineticEnergy); }
  inline void SetParticleCharge(G4double aCharge)
     { particleGun->SetParticleCharge(aCharge); }
  inline void SetParticlePolarization(G4ThreeVector aVal)
     { particleGun->SetParticlePolarization(aVal); }
  inline void SetParticlePosition(G4ThreeVector aPos)
     { particleGun->SetParticlePosition(aPos); }
  inline void SetParticleTime(G4double aTime)
     { particleGun->SetParticleTime(aTime); }
  inline void SetNumberOfParticles(G4int i)
     { particleGun->SetNumberOfParticles(i); }

  inline G4ParticleDefinition* GetParticleDefinition()
     { return particleGun->GetParticleDefinition(); }
  inline G4ParticleMomentum GetParticleMomentumDirection()
     { return particleGun->GetParticleMomentumDirection(); }
  inline G4double GetParticleEnergy()
     { return particleGun->GetParticleEnergy(); }
  inline G4double GetParticleCharge()
     { return particleGun->GetParticleCharge(); }
  inline G4ThreeVector GetParticlePolarization()
     { return particleGun->GetParticlePolarization(); }
  inline G4ThreeVector GetParticlePosition()
     { return particleGun->GetParticlePosition(); }
  inline G4int GetParticleTime()
     { return particleGun->GetParticleTime(); }
  inline G4int GetNumberOfParticles()
     { return particleGun->GetNumberOfParticles(); }

};

#endif


