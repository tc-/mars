#ifndef ENGINEIO_H
#define ENGINEIO_H

#include "vm/io.h"
#include "vm/vm.h"

#define TrackedEngineIODataSize 24
#define TrackedEngineIORWDataSize 8

#define TrackedEngineAccelerationRight 0
#define TrackedEngineAccelerationLeft 4
#define TrackedEngineCurrentSpeedRight 8
#define TrackedEngineCurrentSpeedLeft 12
#define TrackedEngineMaxAcceleration 16
#define TrackedEngineMaxBreakSpeed 20


namespace bot
{

class TrackedEngineIO: public vm::IO
{

  public:
    TrackedEngineIO( vm::VM& vm, const float& acceleration, const float& breakSpeed );
    ~TrackedEngineIO();

    std::string className() { return "TrackedEngine"; }

    int update( bot::Bot& bot );

    vmByte readByte( const unsigned int& index );
    void writeByte( const unsigned int& index, const vmByte& data );

    unsigned int size() { return TrackedEngineIODataSize; }

    static vm::IO* createIOPart( Setting& sett, vm::VM& vm );

  protected:

    char* m_data;
    bool m_own_data;

    void init( const float& acceleration, const float& breakSpeed );

};

}

#endif // ENGINEIO_H
