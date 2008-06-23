
#include <limits.h>
#include <assert.h>
#include <iostream>

#include "vm.h"

#define incPC(num) pc+=num
#define incSP(num) sp+=num

#define readInt(index) (*((vmInt*)&data[index]))
#define intRef(index) (*((vmInt*)&data[index]))

#define readUInt(index) (*((vmUInt*)&data[index]))

#define readSByte(index) (*((vmSByte*)&data[index]))
#define sbyteRef(index) (*((vmSByte*)&data[index]))

#define readByte(index) (data[index])
#define byteRef(index) (data[index])

#define isValidIntMemPos(index) (index+sizeof(vmInt)<memsize)

#define callInterrupt(intType) m_pc=pc;m_sp=sp;interrupt(intType);pc=m_pc;sp=m_sp

namespace vm
{

VM::VM( Memory& memory, unsigned int cpu_speed, unsigned int sp ) :
  m_memory(memory),
  m_speed(cpu_speed),
  m_pc(0),
  m_sp(sp),
  m_bos(sp),
  m_time_left(0)
{
}


VM::~VM()
{
}


void VM::reset( unsigned int pc, unsigned int sp )
{
	setPC(pc);
	setSP(sp);
	m_bos = m_sp;
	m_time_left = 0;
	for( unsigned int i = 0; i < numInterruptVectors; i++ ) m_ints[i] = UINT_MAX;
}


void VM::interrupt( Interrupts interrupt )
{

}


void VM::step()
{
	unsigned int speed = m_speed;
	m_speed = 1;
	m_time_left = 0;
	update();
	m_speed = speed;
}


void VM::step( unsigned int steps )
{
	for ( unsigned int i = 0; i < steps; i++ ) step();
}


void VM::printState()
{
	std::cout << "pc: " << m_pc << " next instruction: " + m_memory.disasm(m_pc,m_pc);
	std::cout << "sp: " << (m_sp - m_bos) << std::endl;
}


void VM::load( std::istream& data )
{
	if ( !data.good() ) throw std::runtime_error("Instream not good.");

	char magic[4] = "BOT";
  unsigned char c = 0;
	for (int i = 0; i < 3; i++ ) {
		data >> c;
		if ( c != magic[i] ) {
			throw std::runtime_error("Magic signature does not match 'BOT'.");
		}
	}

	unsigned int pc, sp, bos, memSize;
	data.read( (char*)&pc, sizeof(unsigned int) );
	data.read( (char*)&bos, sizeof(unsigned int) );
	data.read( (char*)&sp, sizeof(unsigned int) );
	data.read( (char*)&memSize, sizeof(unsigned int) );
	//data >> pc >> bos >> sp >> memSize;

	if ( !data.good() ) throw std::runtime_error("Could not read header.");

	if ( m_memory.size() < memSize ) throw std::runtime_error("Memory space too small to load file.");

	m_memory.load(data);

	reset( pc, bos );
	setSP(sp);
}


void VM::save( std::ostream& data )
{
	data << 'B' << 'O' << 'T';
	data << m_pc << m_bos << m_sp << m_memory.size();
	m_memory.save(data);
}


void nop()
{
}


void VM::update()
{
	m_time_left += m_speed;

	unsigned int memsize = m_memory.size();;
	vmByte* data = m_memory.data;
	vmUInt pos;
	int time_left = m_time_left;
	unsigned int pc = m_pc;
	unsigned int sp = m_sp;

	while ( time_left-- > 0 ) {

		switch ( data[pc++] ) {

/* --------------------------------------- NOP GROUP ------------------------------------- */

			case 0: // nop
				nop();
			break;
			case 1: nop(); break;
			case 2: nop(); break;
			case 3: nop(); break;

/* --------------------------------------- ICONST GROUP ------------------------------------- */

			case 4: // iconst
				intRef(sp) = readInt(pc);
				incSP(sizeof(vmInt));
				incPC(sizeof(vmInt));
			break;

			case 5: // iconst_0
				intRef(sp) = 0;
				incSP(sizeof(vmInt));
			break;
			case 6: // iconst_1
				intRef(sp) = 1;
				incSP(sizeof(vmInt));
			break;
			case 7: // iconst_m1
				intRef(sp) = -1;
				incSP(sizeof(vmInt));
			break;

/* --------------------------------------- ILOAD GROUP ------------------------------------- */

			case 8: // iload_b
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
			case 10: nop(); break;
			case 11: nop(); break;

/* --------------------------------------- ISTOR GROUP ------------------------------------- */

			case 12: // istor_b
				nop();
			break;
			case 13: // istor
				nop();
			break;
			case 14: nop(); break;
			case 15: nop(); break;

/* --------------------------------------- JUMP GROUP ------------------------------------- */

			case 16: // goto_b
				incPC(readSByte(pc));
			break;
			case 17: // goto
				incPC(readInt(pc));
			break;
			case 18: // jump
				pc = readUInt(pc);
			break;
			case 19: nop(); break;

/* --------------------------------------- IOPS GROUP ------------------------------------- */

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
			case 26: nop(); break;
			case 27: nop(); break;

/* --------------------------------------- BRA GROUP ------------------------------------- */

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
			case 34: nop(); break;
			case 35: nop(); break;

/* --------------------------------------- STACK GROUP ------------------------------------- */

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
			case 39: nop(); break;

/* --------------------------------------- LOGIC GROUP ------------------------------------- */

			case 40: // or
				nop();
			break;
			case 41: // and
				nop();
			break;
			case 42: nop(); break;
			case 43: nop(); break;

/* --------------------------------------- CALL GROUP ------------------------------------- */

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

/* --------------------------------------- MEM GROUP ------------------------------------- */

			case 48: // imemstor
				nop();
			break;
			case 49: // imemload
				nop();
			break;
			case 50: nop(); break;
			case 51: nop(); break;

/* --------------------------------------- PORT GROUP ------------------------------------- */

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

/* ------------------------------------ INTERRUPT GROUP ---------------------------------- */

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

/* ------------------------------------ CMP GROUP ---------------------------------- */

			case 60: // icmp
				if ( readInt( sp-sizeof(vmInt) ) == readInt( sp-2*sizeof(vmInt) ) ) sbyteRef( sp-2*sizeof(vmInt) ) = 0;
				else if ( readInt( sp-sizeof(vmInt) ) > readInt( sp-2*sizeof(vmInt) ) ) sbyteRef( sp-2*sizeof(vmInt) ) = 1;
				else sbyteRef( sp-2*sizeof(vmInt) ) = -1;
				incSP(sizeof(vmSByte)-2*sizeof(vmUInt));
			break;
			case 61: // iucmp
				if ( readUInt( sp-sizeof(vmUInt) ) == readUInt( sp-2*sizeof(vmUInt) ) ) sbyteRef( sp-2*sizeof(vmUInt) ) = 0;
				else if ( readUInt( sp-sizeof(vmUInt) ) > readUInt( sp-2*sizeof(vmUInt) ) ) sbyteRef( sp-2*sizeof(vmUInt) ) = 1;
				else sbyteRef( sp-2*sizeof(vmInt) ) = -1;
				incSP(sizeof(vmSByte)-2*sizeof(vmUInt));
			break;
			case 62: // itest
				if ( readInt( sp-sizeof(vmInt) ) == 0 ) sbyteRef( sp-sizeof(vmInt) ) = 0;
				else if ( readInt( sp-sizeof(vmInt) ) > 0 ) sbyteRef( sp-sizeof(vmInt) ) = 1;
				else sbyteRef( sp-sizeof(vmInt) ) = -1;
				incSP(sizeof(vmSByte)-sizeof(vmUInt));
			break;
			case 63: nop(); break;

			case 64: nop(); break;
			case 65: nop(); break;
			case 66: nop(); break;
			case 67: nop(); break;

			case 68: nop(); break;
			case 69: nop(); break;
			case 70: nop(); break;
			case 71: nop(); break;
			case 72: nop(); break;
			case 73: nop(); break;
			case 74: nop(); break;
			case 75: nop(); break;
			case 76: nop(); break;
			case 77: nop(); break;
			case 78: nop(); break;
			case 79: nop(); break;
			case 80: nop(); break;
			case 81: nop(); break;
			case 82: nop(); break;
			case 83: nop(); break;
			case 84: nop(); break;
			case 85: nop(); break;
			case 86: nop(); break;
			case 87: nop(); break;
			case 88: nop(); break;
			case 89: nop(); break;
			case 90: nop(); break;
			case 91: nop(); break;
			case 92: nop(); break;
			case 93: nop(); break;
			case 94: nop(); break;
			case 95: nop(); break;
			case 96: nop(); break;
			case 97: nop(); break;
			case 98: nop(); break;
			case 99: nop(); break;

			case 100: nop(); break;
			case 101: nop(); break;
			case 102: nop(); break;
			case 103: nop(); break;
			case 104: nop(); break;
			case 105: nop(); break;
			case 106: nop(); break;
			case 107: nop(); break;
			case 108: nop(); break;
			case 109: nop(); break;
			case 110: nop(); break;
			case 111: nop(); break;
			case 112: nop(); break;
			case 113: nop(); break;
			case 114: nop(); break;
			case 115: nop(); break;
			case 116: nop(); break;
			case 117: nop(); break;
			case 118: nop(); break;
			case 119: nop(); break;
			case 120: nop(); break;
			case 121: nop(); break;
			case 122: nop(); break;
			case 123: nop(); break;
			case 124: nop(); break;
			case 125: nop(); break;
			case 126: nop(); break;
			case 127: nop(); break;
			case 128: nop(); break;
			case 129: nop(); break;
			case 130: nop(); break;
			case 131: nop(); break;
			case 132: nop(); break;
			case 133: nop(); break;
			case 134: nop(); break;
			case 135: nop(); break;
			case 136: nop(); break;
			case 137: nop(); break;
			case 138: nop(); break;
			case 139: nop(); break;
			case 140: nop(); break;
			case 141: nop(); break;
			case 142: nop(); break;
			case 143: nop(); break;
			case 144: nop(); break;
			case 145: nop(); break;
			case 146: nop(); break;
			case 147: nop(); break;
			case 148: nop(); break;
			case 149: nop(); break;
			case 150: nop(); break;
			case 151: nop(); break;
			case 152: nop(); break;
			case 153: nop(); break;
			case 154: nop(); break;
			case 155: nop(); break;
			case 156: nop(); break;
			case 157: nop(); break;
			case 158: nop(); break;
			case 159: nop(); break;
			case 160: nop(); break;
			case 161: nop(); break;
			case 162: nop(); break;
			case 163: nop(); break;
			case 164: nop(); break;
			case 165: nop(); break;
			case 166: nop(); break;
			case 167: nop(); break;
			case 168: nop(); break;
			case 169: nop(); break;
			case 170: nop(); break;
			case 171: nop(); break;
			case 172: nop(); break;
			case 173: nop(); break;
			case 174: nop(); break;
			case 175: nop(); break;
			case 176: nop(); break;
			case 177: nop(); break;
			case 178: nop(); break;
			case 179: nop(); break;
			case 180: nop(); break;
			case 181: nop(); break;
			case 182: nop(); break;
			case 183: nop(); break;
			case 184: nop(); break;
			case 185: nop(); break;
			case 186: nop(); break;
			case 187: nop(); break;
			case 188: nop(); break;
			case 189: nop(); break;
			case 190: nop(); break;
			case 191: nop(); break;
			case 192: nop(); break;
			case 193: nop(); break;
			case 194: nop(); break;
			case 195: nop(); break;
			case 196: nop(); break;
			case 197: nop(); break;
			case 198: nop(); break;
			case 199: nop(); break;

			case 200: nop(); break;
			case 201: nop(); break;
			case 202: nop(); break;
			case 203: nop(); break;
			case 204: nop(); break;
			case 205: nop(); break;
			case 206: nop(); break;
			case 207: nop(); break;
			case 208: nop(); break;
			case 209: nop(); break;
			case 210: nop(); break;
			case 211: nop(); break;
			case 212: nop(); break;
			case 213: nop(); break;
			case 214: nop(); break;
			case 215: nop(); break;
			case 216: nop(); break;
			case 217: nop(); break;
			case 218: nop(); break;
			case 219: nop(); break;
			case 220: nop(); break;
			case 221: nop(); break;
			case 222: nop(); break;
			case 223: nop(); break;
			case 224: nop(); break;
			case 225: nop(); break;
			case 226: nop(); break;
			case 227: nop(); break;
			case 228: nop(); break;
			case 229: nop(); break;
			case 230: nop(); break;
			case 231: nop(); break;
			case 232: nop(); break;
			case 233: nop(); break;
			case 234: nop(); break;
			case 235: nop(); break;
			case 236: nop(); break;
			case 237: nop(); break;
			case 238: nop(); break;
			case 239: nop(); break;
			case 240: nop(); break;
			case 241: nop(); break;
			case 242: nop(); break;
			case 243: nop(); break;
			case 244: nop(); break;
			case 245: nop(); break;
			case 246: nop(); break;
			case 247: nop(); break;
			case 248: nop(); break;
			case 249: nop(); break;
			case 250: nop(); break;
			case 251: nop(); break;

/* --------------------------------------- EXT GROUP ------------------------------------- */

			case 252: nop(); break;
			case 253: nop(); break;
			case 254: nop(); break;
			case 255: // extended
				if ( data[pc] != 255 ) {
					incPC(sizeof(vmByte));
				}
			break;

		}

		pc = pc<memsize?pc:0;
		sp = sp<memsize?sp:0;

	}

	m_time_left = time_left;
	m_pc = pc;
	m_sp = sp;
}


}
