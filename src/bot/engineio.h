#ifndef ENGINEIO_H
#define ENGINEIO_H

#include "vm/io.h"

namespace bot
{

class TrackedEngineIO : public vm::IO
{
  public:
    TrackedEngineIO( const float& forwardSpeed, const float& backwardSpeed );
    ~TrackedEngineIO();

    std::string className() { return "TrackedEngine"; }

    int update( bot::Bot& bot );

    vmByte readByte( unsigned int index );
    void writeByte( unsigned int index, const vmByte& data );

    static vm::IO* createIOPart(Setting& sett );

  protected:
    float m_fspeed;
    float m_rspeed;
    int m_right_track_speed;
    int m_left_track_speed;
};

}

#endif // ENGINEIO_H
