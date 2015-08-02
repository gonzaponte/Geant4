#include "MyEventAction.hh"
#include "MyRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

MyEventAction::MyEventAction() : G4UserEventAction(), _edep(0.)
{ }

MyEventAction::~MyEventAction()
{ }

void MyEventAction::BeginOfEventAction( const G4Event* )
{
    _edep = 0.;
}

void MyEventAction::EndOfEventAction( const G4Event* )
{
    // accumulate statistics in MyRun
    MyRun* run = static_cast<MyRun*>
    (G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    run->AddEdep(_edep);
}



