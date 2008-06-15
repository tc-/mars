#ifndef IO_H
#define IO_H

#include "vm/vmtypes.h"

namespace bot
{

class IO
{
	public:

		virtual vmByte readByte( unsigned int index ) = 0;
		virtual vmInt readInt( unsigned int index );
		virtual vmUInt readUInt( unsigned int index );
		virtual vmFloat readFloat( unsigned int index );
		virtual vmBool readBool( unsigned int index );
		virtual vmSByte readSByte( unsigned int index );

		virtual void writeByte( unsigned int index, const vmByte& data ) = 0;
		virtual void writeInt( unsigned int index, const vmInt& data );
		virtual void writeUInt( unsigned int index, const vmUInt& data );
		virtual void writeFloat( unsigned int index, const vmFloat& data );
		virtual void writeBool( unsigned int index, const vmBool& data );
		virtual void writeSByte( unsigned int index, const vmSByte& data );

};

}

#endif // IO_H
