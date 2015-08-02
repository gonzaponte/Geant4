/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol     hector.alvarez@usc.es
//*-- Date: 03/2006
//*-- Last Update: 14/10/13 by Hector Alvarez Pol
// --------------------------------------------------------------
// Description:
//   Physics List Messenger
//
// --------------------------------------------------------------
// Comments:
//
//  06/03/06 Included after full physics revision. Migrated to geant4.8
//           Based on examples/extended/medical/GammaTherapy
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaPhysicsListMessenger.hh"

#include "practicaPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4LossTableManager.hh"


practicaPhysicsListMessenger::practicaPhysicsListMessenger(practicaPhysicsList* pPhys)
:pPhysicsList(pPhys){
  //
  // Constructor with commands definition
  //
  physDir = new G4UIdirectory("/practica/phys/");
  physDir->SetGuidance("physics list commands");
   
}


practicaPhysicsListMessenger::~practicaPhysicsListMessenger(){
  //
  // Destructor
  //
  delete physDir;  
}


void practicaPhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue) {
  //
  // Setting the values from the messenger
  //       
}
