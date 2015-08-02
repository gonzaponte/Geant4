#include "MySteppingAction.hh"
#include "MyEventAction.hh"
#include "MyDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

MySteppingAction::MySteppingAction( MyEventAction* evtAction )
: G4UserSteppingAction(), _evtAction( evtAction ), _scoringVolume(0)
{ }

MySteppingAction::~MySteppingAction()
{ }

void MySteppingAction::UserSteppingAction( const G4Step* step )
{
    if (! _scoringVolume )
    {
        const MyDetectorConstruction* detectorConstruction =
        static_cast<const MyDetectorConstruction*> ( G4RunManager::GetRunManager()->GetUserDetectorConstruction() );
        _scoringVolume = detectorConstruction->GetScoringVolume();
    }
    
    // get volume of the current step
    G4LogicalVolume* currentLogVolume = step->GetPreStepPoint()->GetTouchableHandle()
    ->GetVolume()->GetLogicalVolume();
    
    // check if we are in scoring volume
    if ( currentLogVolume != _scoringVolume) return;
    
    // collect energy deposited in this step
    G4double edep_step = step->GetTotalEnergyDeposit();
    _evtAction->AddEdep( edep_step );
}



