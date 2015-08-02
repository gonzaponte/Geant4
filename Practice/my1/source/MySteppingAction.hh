#ifndef _MySteppingAction_h
#define _MySteppingAction_h

#include "G4UserSteppingAction.hh"

class MyEventAction;
class G4LogicalVolume;

class MySteppingAction : public G4UserSteppingAction
{
public:
    MySteppingAction( MyEventAction* evtAction );
    virtual ~MySteppingAction();
    
    // method from the base class
    virtual void UserSteppingAction( const G4Step* );
    
private:
    MyEventAction*   _evtAction;
    G4LogicalVolume* _scoringVolume;
};

#endif
