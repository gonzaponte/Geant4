#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MySteppingAction.hh"

MyActionInitialization::MyActionInitialization() :
G4VUserActionInitialization()
{ }

MyActionInitialization::~MyActionInitialization()
{ }

void MyActionInitialization::BuildForMaster() const
{
    SetUserAction(new MyRunAction);
}


void MyActionInitialization::Build() const
{
    SetUserAction(new MyPrimaryGeneratorAction);
    SetUserAction(new MyRunAction);
    
    MyEventAction* evtAction = new MyEventAction;
    SetUserAction( evtAction );
    SetUserAction( new MySteppingAction( evtAction ) );
}
