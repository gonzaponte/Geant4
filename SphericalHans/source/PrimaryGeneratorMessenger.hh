/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol  (hapol@fpddux.usc.es)
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
//*-- Modified by Hector Alvarez-Pol
// --------------------------------------------------------------
// Description:
//   Messenger for the primary generator.
//
// --------------------------------------------------------------
// Comments:
//   - 03/12/04 Created based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __PrimaryGeneratorMessenger
#define __PrimaryGeneratorMessenger

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4ParticleTable;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithoutParameter;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class PrimaryGeneratorMessenger: public G4UImessenger {
private:
  PrimaryGeneratorAction* actarSimActionGun;
  G4ParticleTable* particleTable;

  G4UIdirectory*               gunDir; 
  G4UIcmdWithoutParameter*     listCmd;
  G4UIcmdWithAString*          particleCmd; 
  G4UIcmdWithAString*          distributionCmd;
  G4UIcmdWithADoubleAndUnit*   energyCmd;
//  G4UIcmdWith3Vector*          directionCmd;
//  G4UIcmdWith3VectorAndUnit*   positionCmd;
//  G4UIcmdWithADoubleAndUnit*   timeCmd;
  G4UIcmdWith3Vector*          polCmd;
  G4UIcmdWithAnInteger*        numberCmd;
//  G4UIcommand*                 ionCmd;

  // for ion shooting
  G4bool   fShootIon; 
  G4int    fAtomicNumber;
  G4int    fAtomicMass;
  G4int    fIonCharge;
  G4double fIonExciteEnergy;

private:
  void IonCommand(G4String newValues);

public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
  ~PrimaryGeneratorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  G4String GetCurrentValue(G4UIcommand * command);

};

#endif

