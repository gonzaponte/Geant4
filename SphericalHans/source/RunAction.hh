/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Controls the actions to perform before and after a run.
//
// --------------------------------------------------------------
// Comments:
//   - 30/11/04 Created based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __RunAction
#define __RunAction

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class RunAction : public G4UserRunAction {

private:
  
//  G4int  multichannel[4096]; //12 bits
//  G4double  range; 
  
public:
  RunAction();
  ~RunAction();
  
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  
//  void StoreEnergy(G4double energy);
//  void SetRange(G4double aValue){range = aValue;}

};


#endif

