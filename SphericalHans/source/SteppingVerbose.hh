/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Controls the verbosity during the step (please, not too much:-)
//
// --------------------------------------------------------------
// Comments:
//   - 30/11/04 Created based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

class SteppingVerbose;

#ifndef __SteppingVerbose
#define __SteppingVerbose

#include "G4SteppingVerbose.hh"

class SteppingVerbose : public G4SteppingVerbose
{
 public:   

   SteppingVerbose();
  ~SteppingVerbose();

   void StepInfo();
   void TrackingStarted();

};

#endif
