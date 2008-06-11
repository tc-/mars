#ifndef IO_H
#define IO_H

namespace bot
{

class IO
{
	public:

		virtual char readChar( unsigned int index ) = 0;
		virtual int readInt( unsigned int index );
		virtual unsigned int readUInt( unsigned int index );
		virtual float readFloat( unsigned int index );

		virtual void writeChar( unsigned int index, const char& data ) = 0;
		virtual void writeInt( unsigned int index, const int& data );
		virtual void writeUInt( unsigned int index, const unsigned int& data );
		virtual void writeFloat( unsigned int index, const float& data );

};

}

#endif // IO_H
