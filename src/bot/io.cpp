#include "io.h"

namespace bot
{

int IO::readInt( unsigned int index )
{
	unsigned int size = sizeof(int);
	char data[size];
	for ( unsigned int i = 0; i < size; i++ ) data[i] = readChar(index+i);
	int* i = reinterpret_cast<int*>(data);
	return *i;
}


unsigned int IO::readUInt( unsigned int index )
{
	unsigned int size = sizeof(unsigned int);
	char data[size];
	for ( unsigned int i = 0; i < size; i++ ) data[i] = readChar(index+i);
	unsigned int* ui = reinterpret_cast<unsigned int*>(data);
	return *ui;
}


float IO::readFloat( unsigned int index )
{
	unsigned int size = sizeof(float);
	char data[size];
	for ( unsigned int i = 0; i < size; i++ ) data[i] = readChar(index+i);
	float* f = reinterpret_cast<float*>(data);
	return *f;
}


void IO::writeInt( unsigned int index, const int& data )
{
	const char* c = reinterpret_cast<const char*>(&data);
	for ( unsigned int i = 0; i < sizeof(data); i++ ) writeChar(index+i, c[i] );
}


void IO::writeUInt( unsigned int index, const unsigned int& data )
{
	const char* c = reinterpret_cast<const char*>(&data);
	for ( unsigned int i = 0; i < sizeof(data); i++ ) writeChar(index+i, c[i] );
}


void IO::writeFloat( unsigned int index, const float& data )
{
	const char* c = reinterpret_cast<const char*>(&data);
	for ( unsigned int i = 0; i < sizeof(data); i++ ) writeChar(index+i, c[i] );
}

}
