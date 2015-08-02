#ifndef _MyRunAction_h
#define _MyRunAction_h

#include "G4UserRunAction.hh"

class G4Run;
class G4LogicalVolume;

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    virtual ~MyRunAction();
    
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction( const G4Run* );
    virtual void   EndOfRunAction( const G4Run* );
};

#endif

