#include "engineio.h"
#include "util/debug.h"

#define IOFloat(pos) (*((float*)&m_data[pos]))


namespace bot
{


TrackedEngineIO::TrackedEngineIO( vm::VM& vm, const float& acceleration, const float& breakSpeed )
{
	m_own_data = false;
	//m_data = data;
	init( acceleration, breakSpeed );
}


void TrackedEngineIO::init( const float& acceleration, const float& breakSpeed )
{
	IOFloat( TrackedEngineAccelerationRight ) = 0.0;
	IOFloat( TrackedEngineAccelerationLeft ) = 0.0;
	IOFloat( TrackedEngineCurrentSpeedRight ) = 0.0;
	IOFloat( TrackedEngineCurrentSpeedLeft ) = 0.0;
	IOFloat( TrackedEngineMaxAcceleration ) = acceleration;
	IOFloat( TrackedEngineMaxBreakSpeed ) = breakSpeed;
}


TrackedEngineIO::~TrackedEngineIO()
{
	if ( m_own_data ) delete[] m_data;
}


vm::IO* TrackedEngineIO::createIOPart( Setting& sett, vm::VM& vm )
{
	float f = 8.0;
	float r = 2.0;
	float b = 16.0;

	sett.lookupValue( "maxForwardSpeed", f );
	sett.lookupValue( "maxReverseSpeed", r );
	sett.lookupValue( "breakSpeed", b );

	return new TrackedEngineIO( vm, f, r );
}


int TrackedEngineIO::update( bot::Bot& bot )
{
	if ( IOFloat( TrackedEngineAccelerationRight ) > IOFloat( TrackedEngineMaxAcceleration ) ) {
		IOFloat( TrackedEngineAccelerationRight ) = IOFloat( TrackedEngineMaxAcceleration );
	} else if ( IOFloat( TrackedEngineAccelerationRight ) < -IOFloat( TrackedEngineMaxBreakSpeed ) ) {
		IOFloat( TrackedEngineAccelerationRight ) = -IOFloat( TrackedEngineMaxBreakSpeed );
	}
	if ( IOFloat( TrackedEngineAccelerationLeft ) > IOFloat( TrackedEngineMaxAcceleration ) ) {
		IOFloat( TrackedEngineAccelerationLeft ) = IOFloat( TrackedEngineMaxAcceleration );
	} else if ( IOFloat( TrackedEngineAccelerationLeft ) < -IOFloat( TrackedEngineMaxBreakSpeed ) ) {
		IOFloat( TrackedEngineAccelerationLeft ) = -IOFloat( TrackedEngineMaxBreakSpeed );
	}

	IOFloat( TrackedEngineCurrentSpeedRight ) += IOFloat( TrackedEngineAccelerationRight ) - IOFloat( TrackedEngineCurrentSpeedRight ) * 0.1;
	IOFloat( TrackedEngineCurrentSpeedLeft ) += IOFloat( TrackedEngineAccelerationLeft ) - IOFloat( TrackedEngineCurrentSpeedLeft ) * 0.1;

	return 0;
}


vmByte TrackedEngineIO::readByte( const unsigned int& index )
{
	assert( index < TrackedEngineIODataSize, "TrackedEngineIO::readByte( unsigned int index ): read out of bounds." );
	return m_data[index];
}


void TrackedEngineIO::writeByte( const unsigned int& index, const vmByte& data )
{
	if ( index >= TrackedEngineIORWDataSize ) return;
	m_data[index] =  data;
}


}

