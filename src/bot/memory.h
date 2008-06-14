#ifndef MEMORY_H
#define MEMORY_H

#include <stdexcept>
#include "io.h"

namespace bot
{

class Memory: public IO
{
	public:

		Memory( unsigned int size );
		~Memory();

		vmByte readByte( unsigned int index ) throw ( std::invalid_argument );
		void writeByte( unsigned int index, const vmByte& data ) throw ( std::invalid_argument );

		void clear();
		void resize( unsigned int size );

		unsigned int size() { return m_size; }

	private:

		unsigned int m_size;
		vmByte* m_data;
};

}

#endif // MEMORY_H
