#ifndef MEMORY_H
#define MEMORY_H

#include <stdexcept>
#include <iostream>
#include <climits>
#include <string.h>

#include "io.h"

namespace bot { class Bot; }

namespace vm
{

class Memory: public IO
{
	public:

		Memory( unsigned int size );
		~Memory();

    std::string className() { return "Memory"; }

    int update( bot::Bot& bot );

		vmByte readByte( const unsigned int& index ) throw ( std::invalid_argument );
		void writeByte( const unsigned int& index, const vmByte& data ) throw ( std::invalid_argument );

		void clear();
		void clearArea(unsigned int start, unsigned int stop );
		void resize( unsigned int size );

		inline unsigned int size() { return m_size; }
		vmByte* data;

		void load( std::istream& stream, const unsigned int& toLocation = 0 ) throw ( std::invalid_argument );
		void save( std::ostream& stream, const unsigned int& startPos = 0, const unsigned int& length = UINT_MAX ) throw ( std::invalid_argument );

		std::string disasm( unsigned int startPos = 0, unsigned int endPos = UINT_MAX );
	private:

		unsigned int m_size;

};

}

#endif // MEMORY_H
