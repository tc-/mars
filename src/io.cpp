#include "io.h"


int IO::readInt( unsigned int index )
{
	int size = sizeof(int);
	int data[size];
	for ( unsigned int i = 0; i < size; i++ ) data[i] = readChar(index+i);
	return (int)data[0];
}


unsigned int IO::readUInt( unsigned int index )
{
	int size = sizeof(unsigned int);
	int data[size];
	for ( unsigned int i = 0; i < size; i++ ) data[i] = readChar(index+i);
	return (unsigned int)data[0];
}


float IO::readFloat( unsigned int index )
{
	int size = sizeof(float);
	int data[size];
	for ( unsigned int i = 0; i < size; i++ ) data[i] = readChar(index+i);
	return (float)data[0];
}


void IO::writeInt( unsigned int index, const int& data )
{
	int size = sizeof(int);
	for ( int i = 0; i < size; i++ ) writeChar(index+i, ((char*)&data)[i] );
}


void IO::writeUInt( unsigned int index, const unsigned int& data )
{
	int size = sizeof(unsigned int);
	for ( int i = 0; i < size; i++ ) writeChar(index+i, ((char*)&data)[i] );
}


void IO::writeFloat( unsigned int index, const float& data )
{
	int size = sizeof(float);
	for ( int i = 0; i < size; i++ ) writeChar(index+i, ((char*)&data)[i] );
}

