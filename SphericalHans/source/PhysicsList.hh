/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol  hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   General physics package
//
// --------------------------------------------------------------
// Comments:
//   
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __PhysicsList
#define __PhysicsList

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

/// Modular physics list
///
/// It includes the folowing physics builders
/// - G4DecayPhysics
/// - G4RadioactiveDecayPhysics
/// - G4EmStandardPhysics

class PhysicsListMessenger;

class PhysicsList: public G4VModularPhysicsList {

private:

  PhysicsListMessenger* PLMessenger;
  
public:
  PhysicsList();
  virtual ~PhysicsList();
  
  virtual void SetCuts();
};

#endif



