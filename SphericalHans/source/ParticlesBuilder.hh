/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol     hapol@fpddux.usc.es
//*-- Date: 03/2006
//*-- Last Update: 01/02/07 by Hector Alvarez Pol
// --------------------------------------------------------------
// Description:
//   Physics List -- Particle builder
//
// --------------------------------------------------------------
// Comments:
//
//  06/03/06 Included after full physics revision. Migrated to geant4.8
//           Based on examples/extended/medical/GammaTherapy
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __ParticlesBuilder
#define __ParticlesBuilder

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"


class ParticlesBuilder : public G4VPhysicsConstructor {
public:
  ParticlesBuilder(const G4String& name = "particles");
  virtual ~ParticlesBuilder();

  // This method will be invoked in the Construct() method.
  // each particle type will be instantiated
  virtual void ConstructParticle();

  // This method is dummy.
  virtual void ConstructProcess() {};

};
#endif








