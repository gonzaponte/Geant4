#ifndef _MyActionInitialization_h
#define _MyActionInitialization_h

#include "G4VUserActionInitialization.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
    ~MyActionInitialization();
    void BuildForMaster() const;
    void Build() const;
};

#endif
