/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol (hapol@fpddux.usc.es)
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Controls the actions to perform during the steps. Note
// that unneeded code lines at this point will affect performance.
//
// --------------------------------------------------------------
// Comments:
//   - 30/11/04 Created based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaSteppingAction.hh"

#include "practicaDetectorConstruction.hh"
#include "practicaEventAction.hh"

#include "G4Track.hh"

practicaSteppingAction::practicaSteppingAction(practicaDetectorConstruction* det,
					       practicaEventAction* evt)
  :detector(det), eventaction(evt) {
  //
  //
  //
 }


practicaSteppingAction::~practicaSteppingAction() {
  //
  //
  //
}


void practicaSteppingAction::UserSteppingAction(const G4Step* aStep) {
  //
  //G4 actions to perform every step. All actions moved to
  // ROOT analysis classes for easier ROOT output
  //

  const G4Track* track = aStep->GetTrack();
  G4VPhysicalVolume* volume = track->GetVolume();
     
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();

  G4double stepl = 0.;
  if (track->GetDefinition()->GetPDGCharge() != 0. && track->GetParentID()==0)
    stepl = aStep->GetStepLength();
  else stepl = 0;
  
  if ((edep!=0. && volume == detector->GetDetectorPhys())) 
    eventaction->AddDetector(edep,stepl);
  else ;   // eventaction->AddMedium(edep,stepl);
  
  // save the random number seed of this event, under condition
  // if(condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();
}




