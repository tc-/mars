
#include "engineio.h"
#include <assert.h>

#define IOFloat(pos) (*((float*)&m_data[pos]))


namespace bot
{

TrackedEngineIO::TrackedEngineIO( const float& forwardSpeed, const float& backwardSpeed )
{
  m_own_data = true;
  m_data = new char[TrackedEngineIODataSize];
  init( forwardSpeed, backwardSpeed );
}


TrackedEngineIO::TrackedEngineIO( char* data, const float& forwardSpeed, const float& backwardSpeed )
{
  m_own_data = false;
  m_data = data;
  init( forwardSpeed, backwardSpeed );
}


void TrackedEngineIO::init( const float& forwardSpeed, const float& backwardSpeed )
{
  IOFloat(TrackedEngineSpeedRight) = 0.0;
  IOFloat(TrackedEngineSpeedLeft) = 0.0;
  IOFloat(TrackedEngineCurrentSpeedRight) = 0.0;
  IOFloat(TrackedEngineCurrentSpeedLeft) = 0.0;
  IOFloat(TrackedEngineMaxForwardSpeed) = forwardSpeed;
  IOFloat(TrackedEngineMaxReverseSpeed) = backwardSpeed;
}


TrackedEngineIO::~TrackedEngineIO()
{
  if ( m_own_data ) delete[] m_data;
}


vm::IO* TrackedEngineIO::createIOPart( Setting& sett, char* botMemory, unsigned int maxLength )
{
  if ( maxLength < TrackedEngineIODataSize ) return 0;
  float f = 8.0;
  float r = 2.0;

  sett.lookupValue("maxForwardSpeed", f);
  sett.lookupValue("maxReverseSpeed", r);

  return new TrackedEngineIO( botMemory, f, r );
}


int TrackedEngineIO::update( bot::Bot& bot )
{

  return 0;
}


vmByte TrackedEngineIO::readByte( unsigned int index )
{
  assert( index < TrackedEngineIODataSize );
  return m_data[index];
}


void TrackedEngineIO::writeByte( unsigned int index, const vmByte& data )
{
  if ( index >= TrackedEngineIORWDataSize ) return;
  m_data[index] =  data;
}


}

