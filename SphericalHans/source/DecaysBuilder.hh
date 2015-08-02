/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol     hapol@fpddux.usc.es
//*-- Date: 03/2006
//*-- Last Update: 01/02/07 by Hector Alvarez Pol
// --------------------------------------------------------------
// Description:
//   Physics List -- Decays builder
//
// --------------------------------------------------------------
// Comments:
//
//  06/03/06 Included after full physics revision. Migrated to geant4.8
//           Based on examples/extended/medical/GammaTherapy
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef DecaysBuilder
#define DecaysBuilder

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"


class DecaysBuilder : public G4VPhysicsConstructor {
private:

   // hide assignment operator
  DecaysBuilder & operator=(const DecaysBuilder &right);
  DecaysBuilder(const DecaysBuilder&);

public:

  DecaysBuilder(const G4String& name = "decays");
  virtual ~DecaysBuilder();

  // This method is dummy for physics
  virtual void ConstructParticle();

  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type
  virtual void ConstructProcess();

};
#endif








