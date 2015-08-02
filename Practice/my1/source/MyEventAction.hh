#ifndef _MyEventAction_h
#define _MyEventAction_h

#include "G4UserEventAction.hh"
#include "globals.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction();
    virtual ~MyEventAction();
    
    virtual void BeginOfEventAction( const G4Event* event );
    virtual void EndOfEventAction  ( const G4Event* event );
    
    void AddEdep( G4double edep );
    
private:
    G4double  _edep;
};

inline void MyEventAction::AddEdep( G4double edep ) { _edep += edep; }

#endif
