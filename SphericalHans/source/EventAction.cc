/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Actions to be performed before or after each event
//
// --------------------------------------------------------------
// Comments:
//
//   - 30/11/04 Created based on example/novice/N03 structure
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaEventAction.hh"
#include "practicaEventActionMessenger.hh"

#include "practicaRunAction.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

practicaEventAction::practicaEventAction(practicaRunAction* run)
  : drawFlag("all"), printModulo(1000), runAction(run) {
  //
  // Constructor
  //

  eventMessenger = new practicaEventActionMessenger(this);
}


practicaEventAction::~practicaEventAction() {
  //
  // Destructor
  //
  delete eventMessenger;
}


void practicaEventAction::BeginOfEventAction(const G4Event* evt){
  //
  // At the beginning...
  //  
  G4int evtNb = evt->GetEventID();
  if (evtNb%printModulo == 0) { 
    G4cout << "##################################################################"
	   << G4endl
	   << "########    practicaEventAction::BeginOfEventAction()   ##########"
	   << G4endl
	   << "#### Begin of event: " << evtNb << G4endl;
    CLHEP::HepRandom::showEngineStatus();
    G4cout << "##################################################################"
	   << G4endl;
  }

  // initialisation per event
  energyInDetector = 0.;
  trackLInDetector = 0.;
  
}


void practicaEventAction::EndOfEventAction(const G4Event* evt) {
  //
  //  After the end of the event...
  //
  G4int evtNb = evt->GetEventID();
  
  if (evtNb%printModulo == 0){ 
    G4cout << "##################################################################"
	   << G4endl
	   << "#########    practicaEventAction::EndOfEventAction()   #########"
	   << G4endl
	   << "#### End of event: " << evtNb << G4endl;	
    G4cout << "##################################################################"
	   << G4endl;
  }

  //At the end of the event the values of the energy deposited are sent to the RunAction
  runAction->StoreEnergy(energyInDetector);

  // extract the trajectories and draw them
  
  // You can get a default drawing without this code by using, e.g.,
  // /vis/scene/add/trajectories 1000
  // The code here adds sophistication under control of drawFlag.
  
  // See comments in G4VTrajectory::DrawTrajectory for the
  // interpretation of the argument, 1000.
  
  /*
  G4VVisManager* pVisManager = G4VVisManager::GetConcreteInstance();
  if (pVisManager)
    {
      G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
      G4int n_trajectories = 0;
      if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
      for (G4int i=0; i<n_trajectories; i++) 
        { G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
	if (drawFlag == "all") pVisManager->Draw(*trj,1000);
	else if ((drawFlag == "charged")&&(trj->GetCharge() != 0.))
	  pVisManager->Draw(*trj,1000);
	else if ((drawFlag == "neutral")&&(trj->GetCharge() == 0.))
	  pVisManager->Draw(*trj,1000);
        }
    }
  */
}  

