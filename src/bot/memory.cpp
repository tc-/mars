#include "memory.h"

#include <cmath>

namespace bot
{

Memory::Memory( unsigned int size )
{
	m_size = size;
	data = new vmByte[size];
}


Memory::~Memory()
{
	delete data;
}


vmByte Memory::readByte( unsigned int index ) throw ( std::invalid_argument )
{
	if ( index >= m_size ) throw std::invalid_argument("index >= size");
	return data[index];
}


void Memory::writeByte( unsigned int index, const vmByte& indata ) throw ( std::invalid_argument )
{
	if ( index >= m_size ) throw std::invalid_argument("index >= size");
	data[index] = indata;
}


void Memory::clear()
{
	for ( unsigned int i = 0; i < m_size; i++ ) data[i] = 0;
}


void Memory::resize( unsigned int size )
{
	unsigned char* tmp = data;
	data = new unsigned char[size];
	unsigned int copysize = m_size < size ? m_size : size;
	m_size = size;

	for ( unsigned int i = 0; i < copysize; i++ ) data[i] = tmp[i];

	delete tmp;
}


void Memory::load( std::istream& stream, const unsigned int& toLocation ) throw ( std::invalid_argument )
{
	if ( toLocation >= m_size ) throw std::invalid_argument("Memory::save(): startPos >= m_size");
	for ( unsigned int i = toLocation; i < m_size; i++ ) {
		if (!stream.good()) break;
		data[i] = stream.get();
	}
}


void Memory::save( std::ostream& stream, const unsigned int& startPos, const unsigned int& length ) throw ( std::invalid_argument )
{
	if ( startPos >= m_size ) throw std::invalid_argument("Memory::save(): startPos >= m_size");
	unsigned int stopPos = std::max(m_size, startPos+length);
	for ( unsigned int i = startPos; i < stopPos; i++ ) {
		if (!stream.good()) break;
		stream.put(data[i]);
	}
}


}
