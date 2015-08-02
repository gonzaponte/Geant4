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

#ifndef __PhysicsListMessenger
#define __PhysicsListMessenger

#include "globals.hh"
#include "G4UImessenger.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;


class PhysicsListMessenger: public G4UImessenger {
private:
  
  PhysicsList*               pPhysicsList;
    
  G4UIdirectory*             physDir;    
   
public:
  
  PhysicsListMessenger(PhysicsList* );
  ~PhysicsListMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
};
#endif

