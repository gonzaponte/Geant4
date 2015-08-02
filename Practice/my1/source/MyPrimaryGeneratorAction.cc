#include "MyPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"


MyPrimaryGeneratorAction::MyPrimaryGeneratorAction( const G4String& particleName,
                                                    G4double energy,
                                                    G4ThreeVector position,
                                                    G4ThreeVector momentumDirection)
: G4VUserPrimaryGeneratorAction(), _particleGun(0)
{
    G4int nparticles = 1;
    _particleGun  = new G4ParticleGun(nparticles);
    
    // default particle kinematic
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle( particleName );
    
    _particleGun->SetParticleDefinition( particle );
    _particleGun->SetParticleEnergy( energy );
    _particleGun->SetParticlePosition( position );
    _particleGun->SetParticleMomentumDirection( momentumDirection );
}


MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete _particleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt)
{
    // this function is called at the begining of event
    _particleGun->GeneratePrimaryVertex( evt );
}

