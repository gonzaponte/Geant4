/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol  (hapol@fpddux.usc.es)
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
//*-- Modified by 
// --------------------------------------------------------------
// Description:
//   Actions to perform to generate a primary vertex
//
// --------------------------------------------------------------
// Comments:
//   - 27/01/05 Cleaning and improving calculations
//   - 25/11/04 Created based on example/novice/N01 structure
// 
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaPrimaryGeneratorAction.hh"

#include "practicaDetectorConstruction.hh"
#include "practicaPrimaryGeneratorMessenger.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Gamma.hh"
#include "G4Geantino.hh"
#include "globals.hh"
#include "Randomize.hh"

# include <cstdlib>
# include <iostream>
# include <fstream>
using namespace std;

practicaPrimaryGeneratorAction::practicaPrimaryGeneratorAction() {
  //
  // Constructor: init values are filled
  //

  //Initial Values
  G4ThreeVector zero;
  particleTable = G4ParticleTable::GetParticleTable();

  //create a particleGun
  particleGun = new G4ParticleGun(1);

  //create a messenger for this class
  gunMessenger = new practicaPrimaryGeneratorMessenger(this);
  
  G4ParticleDefinition* pd = particleTable->FindParticle("gamma");
    if(pd != 0)
    particleGun->SetParticleDefinition(pd);
  particleGun->SetParticlePosition(zero);
  particleGun->SetParticleTime(0.0);
  //particleGun->SetParticlePolarization(zero); //requires a ThreeVector in new G4
  particleGun->SetParticleCharge(0); 
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));

    // Por defecto a enerxia do gamma menos enerxetico.
    particleGun->SetParticleEnergy(1.173*MeV);
}

practicaPrimaryGeneratorAction::~practicaPrimaryGeneratorAction() {
  //
  // Simple destructor
  //
  delete particleGun;
  delete gunMessenger;
}

void practicaPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  //
  // Generate most of the primary physics. See the comments on each possible case
  //
  
  //REMOVE IF NOT NEEDED!!!!!!
  const G4int verboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();
  //G4cout << G4endl << " ______ VerboseLevel  _______" <<verboseLevel<< G4endl;

  G4ThreeVector zero;
  G4ThreeVector vertexPosition;       //zero, to be calculated if flatDistributionFlag is on
  
  if(flatDistributionFlag == "on") {

    G4double maxRadius = 60*mm;
    G4double z0 = 0*mm;     
    G4double x0, y0;
    
    do{
      x0 = (G4UniformRand() * maxRadius) - maxRadius/2;
      y0 = (G4UniformRand() * maxRadius) - maxRadius/2;
    }while( (x0*x0+y0*y0)>(maxRadius*maxRadius) );
      
    //Next code could be used for a beam-like gaussian behavior
    //Some beam parameters, still hardcoded. Move to a messenger if dynamic interaction is required
    /*
    G4double FWHM  = 1.*cm;
    G4double sigma = FWHM/2.35;

    //gaussian profile for the beam (usually limited by an arbitrary beamWindow)
    G4double beamWindow = 100*mm;
    G4double R= fabs(CLHEP::RandGauss::shoot(0.*cm,sigma));
    while(R > beamWindow )
      R= fabs(CLHEP::RandGauss::shoot(0.*cm,sigma));
    G4double tarPhi = G4UniformRand() * twopi;
    
    G4double z0 = -100*mm;     //check if this value is OK, or set a command in messenger for it
    G4double x0 = R*cos(tarPhi);
    G4double y0 = R*sin(tarPhi);
    */

    vertexPosition.setX(x0);
    vertexPosition.setY(y0);
    vertexPosition.setZ(z0);
  }

  particleGun->SetParticlePosition(vertexPosition);
  particleGun->GeneratePrimaryVertex(anEvent);     
  
    // Enerxia do foton de baixa enerxia do 60Co. Lanzo un aleatorio
    // plano entre 0 e 1 que decide se emite ese foton ou o outro mais
    // enerxetico. O criterio de seleccion ven dado polo branching ratio.
    particleGun->SetParticleEnergy(1.173*MeV);
    if ( G4UniformRand() > 0.4997493742019194)
        particleGun->SetParticleEnergy(1.332*MeV);
  
}

