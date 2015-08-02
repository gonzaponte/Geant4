#ifndef _MyRun_h
#define _MyRun_h

#include "G4Run.hh"

class G4Event;

class MyRun : public G4Run
{
public:
    MyRun();
    virtual ~MyRun();
    
    // method from the base class
    virtual void Merge( const G4Run* );
    
    void AddEdep ( G4double edep );
    
    // get methods
    G4double GetEdep()  const;
    G4double GetEdep2() const;
    
private:
    G4double  _edep;
    G4double  _edep2;
};

inline G4double MyRun::GetEdep()  const { return _edep; }
inline G4double MyRun::GetEdep2() const { return _edep2; }


#endif

