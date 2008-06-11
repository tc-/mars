#include "memory.h"

namespace bot
{

Memory::Memory( unsigned int size )
{
	m_size = size;
	m_data = new char[size];
}


Memory::~Memory()
{
	delete m_data;
}


char Memory::readChar( unsigned int index ) throw ( std::invalid_argument )
{
	if ( index >= m_size ) throw std::invalid_argument("index >= size");
	return m_data[index];
}


void Memory::writeChar( unsigned int index, const char& data ) throw ( std::invalid_argument )
{
	if ( index >= m_size ) throw std::invalid_argument("index >= size");
	m_data[index] = data;
}


void Memory::clear()
{
	for ( unsigned int i = 0; i < m_size; i++ ) m_data[i] = 0;
}


void Memory::resize( unsigned int size )
{
	char* tmp = m_data;
	m_data = new char[size];
	unsigned int copysize = m_size < size ? m_size : size;
	m_size = size;

	for ( int i = 0; i < copysize; i++ ) m_data[i] = tmp[i];

	delete tmp;
}

}
