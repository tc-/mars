#ifndef ENGINEIO_H
#define ENGINEIO_H

#include "vm/io.h"

#define TrackedEngineIODataSize 24
#define TrackedEngineIORWDataSize 8

#define TrackedEngineSpeedRight 0
#define TrackedEngineSpeedLeft 4
#define TrackedEngineCurrentSpeedRight 8
#define TrackedEngineCurrentSpeedLeft 12
#define TrackedEngineMaxForwardSpeed 16
#define TrackedEngineMaxReverseSpeed 20


namespace bot
{

class TrackedEngineIO: public vm::IO
{

  public:
    TrackedEngineIO( const float& forwardSpeed, const float& backwardSpeed );
    TrackedEngineIO( char* data, const float& forwardSpeed, const float& backwardSpeed );
    ~TrackedEngineIO();

    std::string className() { return "TrackedEngine"; }

    int update( bot::Bot& bot );

    vmByte readByte( unsigned int index );
    void writeByte( unsigned int index, const vmByte& data );

    unsigned int size() { return TrackedEngineIODataSize; }

    static vm::IO* createIOPart( Setting& sett, char* botMemory, unsigned int maxLength );

  protected:

    char* m_data;
    bool m_own_data;

    void init( const float& forwardSpeed, const float& backwardSpeed );

};

}

#endif // ENGINEIO_H
