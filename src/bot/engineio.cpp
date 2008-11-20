
#include "engineio.h"


namespace bot
{

TrackedEngineIO::TrackedEngineIO( const float& forwardSpeed, const float& backwardSpeed )
{
  m_fspeed = forwardSpeed;
  m_rspeed = backwardSpeed;
  m_right_track_speed = 0;
  m_left_track_speed = 0;
}


TrackedEngineIO::~TrackedEngineIO()
{
}


vm::IO* TrackedEngineIO::createIOPart( Setting& sett )
{
  float f = 8.0;
  float r = 2.0;

  sett.lookupValue("maxForwardSpeed", f);
  sett.lookupValue("maxReverseSpeed", r);

  return new TrackedEngineIO( f, r );;
}


int TrackedEngineIO::update( bot::Bot& bot )
{

  return 0;
}


vmByte TrackedEngineIO::readByte( unsigned int index )
{
  return 0;
}


void TrackedEngineIO::writeByte( unsigned int index, const vmByte& data )
{
  switch (index) {
    case 0: break;
  }
}


}

