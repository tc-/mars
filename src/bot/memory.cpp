#include "memory.h"

#include <cmath>
#include <sstream>

namespace bot
{

Memory::Memory( unsigned int size )
{
	m_size = size;
	data = new vmByte[size+32];
	data = &data[15];
}


Memory::~Memory()
{
	data = &data[-15];
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
	data = new unsigned char[size+32];
	data = &data[15];
	unsigned int copysize = m_size < size ? m_size : size;
	m_size = size;

	for ( unsigned int i = 0; i < copysize; i++ ) data[i] = tmp[i];

	tmp = &tmp[-15];
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
	unsigned int stopPos = std::min(m_size-1, startPos+length);
	for ( unsigned int i = startPos; i <= stopPos; i++ ) {
		if (!stream.good())
			break;
		stream.put(data[i]);
	}
}


template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream s;
	s << t;
	return s.str();
}


std::string asmLine( const int& pos, const std::string& nem, const std::string& params = "", const std::string& comment = "", const std::string& label = "" )
{
	std::string ret = to_string(pos) + ":";
	ret += label + "\t\t";
	ret += nem + "\t";
	ret += params;
	if ( comment != "" ) {
		ret += "\t# ";
		ret += comment;
	}
	return ret + "\n";
}


std::string Memory::disasm( unsigned int startPos, unsigned int endPos )
{
	if ( endPos > startPos ) {
		unsigned int tmp = endPos;
		endPos = startPos;
		startPos = tmp;
	}
	endPos = std::min(m_size-1, endPos );
	unsigned int i = std::min( startPos, endPos );

	std::string ret = "";
	int pos;

	while ( i <= endPos ) {

		switch ( data[i++] ) {

			case 0: // nop
				ret += asmLine( i-1, "NOP" );
			break;

			case 4: // iconst
				ret += asmLine( i-1, "ICONST", to_string( *((int*)&data[i])) );
				i += sizeof(vmInt);
			break;

			case 5: // iconst_0
				ret += asmLine( i-1, "ICONST", "0" );
			break;
			case 6: // iconst_1
				ret += asmLine( i-1, "ICONST", "1" );
			break;
			case 7: // iconst_m1
				ret += asmLine( i-1, "ICONST", "-1" );
			break;

/*			case 8: // iload_b
				pos = sp - readSByte(pc);
				if ( isValidIntMemPos(pos) ) intRef(sp) = readInt( pos );
				incSP(sizeof(vmInt));
				incPC(sizeof(vmSByte));
			break;
			case 9: // iload
				pos = m_bos + readInt(pc);
				if ( isValidIntMemPos(pos) ) intRef(sp) = readInt( pos );
				incSP(sizeof(vmInt));
				incPC(sizeof(vmInt));
			break;

			case 12: // istor_b
				nop();
			break;
			case 13: // istor
				nop();
			break;

			case 16: // goto_b
				incPC(readSByte(pc));
			break;
			case 17: // goto
				incPC(readInt(pc));
			break;
			case 18: // jump
				pc = readUInt(pc);
			break;

			case 20: // iadd
				intRef( sp-2*sizeof(vmInt) ) += readInt( sp-sizeof(vmInt) );
				incSP(-sizeof(vmInt));
			break;
			case 21: // imul
				intRef( sp-2*sizeof(vmInt) ) *= readInt( sp-sizeof(vmInt) );
				incSP(-sizeof(vmInt));
			break;
			case 22: // idiv
				if ( readInt( sp-sizeof(vmInt) ) != 0 ) {
					intRef( sp-2*sizeof(vmInt) ) /= readInt( sp-sizeof(vmInt) );
					incSP(-sizeof(vmInt));
				} else {
					intRef( sp-2*sizeof(vmInt) ) = INT_MAX;
					incSP(-sizeof(vmInt));
					callInterrupt(intDivideByZero);
				}
			break;
			case 23: // imod
				if ( readInt( sp-sizeof(vmInt) ) != 0 ) {
					intRef( sp-2*sizeof(vmInt) ) %= readInt( sp-sizeof(vmInt) );
					incSP(-sizeof(vmInt));
				} else {
					intRef( sp-2*sizeof(vmInt) ) = 0;
					incSP(-sizeof(vmInt));
					callInterrupt(intDivideByZero);
				}
			break;

			case 24: // iinc
				intRef( sp-sizeof(vmInt) ) += readInt(pc);
				incPC(sizeof(vmInt));
			break;
			case 25: //iinc_1
				intRef( sp-sizeof(vmInt) )++;
			break;

			case 28: // bne
				nop();
			break;
			case 29: // beq
				nop();
			break;
			case 30: // blt
				nop();
			break;
			case 31: // bgt
				nop();
			break;

			case 32: // bge
				nop();
			break;
			case 33: // ble
				nop();
			break;

			case 36: // pop
				incSP(-1);
			break;
			case 37: // pop_4
				incSP(-4);
			break;
			case 38: // incsp
				incSP(readSByte(pc));
				incPC(sizeof(vmByte));
			break;

			case 40: // or
				nop();
			break;
			case 41: // and
				nop();
			break;

			case 44: // jsr_b
				nop();
			break;
			case 45: // jsr
				nop();
			break;
			case 46: nop(); break;
			case 47: // ret
				nop();
			break;

			case 48: // imemstor
				nop();
			break;
			case 49: // imemload
				nop();
			break;

			case 52: // port_r
				nop();
			break;
			case 53: // port_w
				nop();
			break;
			case 54: // iport_r
				nop();
			break;
			case 55: // iport_w
				nop();
			break;

			case 56: // swi
				nop();
			break;
			case 57: // seti
				nop();
			break;
			case 58: // unseti
				nop();
			break;
			case 59: // reti
				nop();
			break;

			case 255: // extended
				if ( data[pc] != 255 ) {
					incPC(sizeof(vmByte));
				}
			break;*/
			default:
			pos = data[i-1];
				ret += asmLine( i-1, "DB", to_string(pos) );
			break;

		}

	}

	return ret;

}

}
