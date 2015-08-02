/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol     hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07 by Hector Alvarez Pol
// --------------------------------------------------------------
// Description:
//   Physics List 
//
// --------------------------------------------------------------
// Comments:
//
//  04/03/06 Full physics revision. Migrated to geant4.8
//           Based on examples/extended/medical/GammaTherapy
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaPhysicsList.hh"
#include "practicaPhysicsListMessenger.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
//#include "G4EmLivermorePhysics.hh"
//#include "G4EmPenelopePhysics.hh"


practicaPhysicsList::practicaPhysicsList():  G4VModularPhysicsList(){  
  //
  // Constructor. Initializing values
  //

  SetVerboseLevel(1);

  // Default physics
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());
  //RegisterPhysics(new G4EmLivermorePhysics());
  //RegisterPhysics(new G4EmPenelopePhysics());
  
  pMessenger = new practicaPhysicsListMessenger(this);
}


practicaPhysicsList::~practicaPhysicsList() {
  //
  // Destructor. Nothing to do
  //  
}

void practicaPhysicsList::SetCuts(){
  //

  G4VUserPhysicsList::SetCuts();
}

