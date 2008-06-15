
#include <assert.h>
#include <iostream>

#include "vm.h"

#define incPC(num) m_pc+=num
#define incSP(num) m_sp+=num

#define readInt(index) (*((vmInt*)&data[index]))
#define getIntRef(index) (*((vmInt*)&data[index]))

#define readUInt(index) (*((vmUInt*)&data[index]))

#define readSByte(index) (*((vmSByte*)&data[index]))

#define isValidIntMemPos(index) (index+sizeof(vmInt)<memsize)


namespace interpreter
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
}

// 3796650 -> 4001600 -> 5084575 -> 6040825 -> 7549540
void VM::update()
{
	m_time_left += m_speed;

	unsigned int memsize = m_memory.size();;
	vmByte* data = m_memory.data;
	vmUInt pos;

	while ( m_time_left-- > 0 ) {

		switch ( data[m_pc++] ) {

/* --------------------------------------- NOP GROUP ------------------------------------- */

			case 0: // nop
			break;
			case 1: break;
			case 2: break;
			case 3: break;

/* --------------------------------------- ICONST GROUP ------------------------------------- */

			case 4: // iconst
				getIntRef(m_sp) = readInt(m_pc);
				m_sp += sizeof(vmInt);
				m_pc += sizeof(vmInt);
			break;

			case 5: // iconst_0
			break;
			case 6: // iconst_1
			break;
			case 7: // iconst_m1
			break;

/* --------------------------------------- ILOAD GROUP ------------------------------------- */

			case 8: // iload_b
				pos = m_bos + readUInt(m_pc);
				if ( isValidIntMemPos(pos) ) getIntRef(m_sp) = readInt( pos );
				incSP(sizeof(vmInt));
				incPC(sizeof(vmInt));
			break;
			case 9: // iload
			break;
			case 10: break;
			case 11: break;

/* --------------------------------------- ISTOR GROUP ------------------------------------- */

			case 12: // istor_b
			break;
			case 13: // istor
			break;
			case 14: break;
			case 15: break;

/* --------------------------------------- JUMP GROUP ------------------------------------- */

			case 16: // goto_b
				incPC(readSByte(m_pc));
			break;
			case 17: // goto
			break;
			case 18: // jump
			break;
			case 19: break;

/* --------------------------------------- IOPS GROUP ------------------------------------- */

			case 20: // iadd
			break;
			case 21: // imul
			break;
			case 22: // idiv
			break;
			case 23: // imod
			break;

			case 24: // iinc
				getIntRef( m_sp-sizeof(vmInt) ) += readInt(m_pc);
				incPC(sizeof(vmInt));
			break;
			case 25: break;
			case 26: break;
			case 27: break;

/* --------------------------------------- BRA GROUP ------------------------------------- */

			case 28: // bne
			break;
			case 29: // beq
			break;
			case 30: // blt
			break;
			case 31: // bgt
			break;

			case 32: // bge
			break;
			case 33: // ble
			break;
			case 34: break;
			case 35: break;

/* --------------------------------------- STACK GROUP ------------------------------------- */

			case 36: // pop
				incSP(-1);
			break;
			case 37: // pop_4
				incSP(-4);
			break;
			case 38: // incsp
				incSP(readSByte(m_pc));
				incPC(sizeof(vmByte));
			break;
			case 39: break;

/* --------------------------------------- LOGIC GROUP ------------------------------------- */

			case 40: // or
			break;
			case 41: // and
			break;
			case 42: break;
			case 43: break;

/* --------------------------------------- CALL GROUP ------------------------------------- */

			case 44: // jsr_b
			break;
			case 45: // jsr
			break;
			case 46: break;
			case 47: // ret
			break;

/* --------------------------------------- MEM GROUP ------------------------------------- */

			case 48: // imemstor
			break;
			case 49: // imemload
			break;
			case 50: break;
			case 51: break;

/* --------------------------------------- PORT GROUP ------------------------------------- */

			case 52: // port_r
			break;
			case 53: // port_w
			break;
			case 54: // iport_r
			break;
			case 55: // iport_w
			break;

/* ------------------------------------ UNDEFINED GROUP ---------------------------------- */

			case 56: break;
			case 57: break;
			case 58: break;
			case 59: break;

			case 60: break;
			case 61: break;
			case 62: break;
			case 63: break;

			case 64: break;
			case 65: break;
			case 66: break;
			case 67: break;

			case 68: break;
			case 69: break;
			case 70: break;
			case 71: break;
			case 72: break;
			case 73: break;
			case 74: break;
			case 75: break;
			case 76: break;
			case 77: break;
			case 78: break;
			case 79: break;
			case 80: break;
			case 81: break;
			case 82: break;
			case 83: break;
			case 84: break;
			case 85: break;
			case 86: break;
			case 87: break;
			case 88: break;
			case 89: break;
			case 90: break;
			case 91: break;
			case 92: break;
			case 93: break;
			case 94: break;
			case 95: break;
			case 96: break;
			case 97: break;
			case 98: break;
			case 99: break;

			case 100: break;
			case 101: break;
			case 102: break;
			case 103: break;
			case 104: break;
			case 105: break;
			case 106: break;
			case 107: break;
			case 108: break;
			case 109: break;
			case 110: break;
			case 111: break;
			case 112: break;
			case 113: break;
			case 114: break;
			case 115: break;
			case 116: break;
			case 117: break;
			case 118: break;
			case 119: break;
			case 120: break;
			case 121: break;
			case 122: break;
			case 123: break;
			case 124: break;
			case 125: break;
			case 126: break;
			case 127: break;
			case 128: break;
			case 129: break;
			case 130: break;
			case 131: break;
			case 132: break;
			case 133: break;
			case 134: break;
			case 135: break;
			case 136: break;
			case 137: break;
			case 138: break;
			case 139: break;
			case 140: break;
			case 141: break;
			case 142: break;
			case 143: break;
			case 144: break;
			case 145: break;
			case 146: break;
			case 147: break;
			case 148: break;
			case 149: break;
			case 150: break;
			case 151: break;
			case 152: break;
			case 153: break;
			case 154: break;
			case 155: break;
			case 156: break;
			case 157: break;
			case 158: break;
			case 159: break;
			case 160: break;
			case 161: break;
			case 162: break;
			case 163: break;
			case 164: break;
			case 165: break;
			case 166: break;
			case 167: break;
			case 168: break;
			case 169: break;
			case 170: break;
			case 171: break;
			case 172: break;
			case 173: break;
			case 174: break;
			case 175: break;
			case 176: break;
			case 177: break;
			case 178: break;
			case 179: break;
			case 180: break;
			case 181: break;
			case 182: break;
			case 183: break;
			case 184: break;
			case 185: break;
			case 186: break;
			case 187: break;
			case 188: break;
			case 189: break;
			case 190: break;
			case 191: break;
			case 192: break;
			case 193: break;
			case 194: break;
			case 195: break;
			case 196: break;
			case 197: break;
			case 198: break;
			case 199: break;

			case 200: break;
			case 201: break;
			case 202: break;
			case 203: break;
			case 204: break;
			case 205: break;
			case 206: break;
			case 207: break;
			case 208: break;
			case 209: break;
			case 210: break;
			case 211: break;
			case 212: break;
			case 213: break;
			case 214: break;
			case 215: break;
			case 216: break;
			case 217: break;
			case 218: break;
			case 219: break;
			case 220: break;
			case 221: break;
			case 222: break;
			case 223: break;
			case 224: break;
			case 225: break;
			case 226: break;
			case 227: break;
			case 228: break;
			case 229: break;
			case 230: break;
			case 231: break;
			case 232: break;
			case 233: break;
			case 234: break;
			case 235: break;
			case 236: break;
			case 237: break;
			case 238: break;
			case 239: break;
			case 240: break;
			case 241: break;
			case 242: break;
			case 243: break;
			case 244: break;
			case 245: break;
			case 246: break;
			case 247: break;
			case 248: break;
			case 249: break;
			case 250: break;
			case 251: break;

/* --------------------------------------- EXT GROUP ------------------------------------- */

			case 252: break;
			case 253: break;
			case 254: break;
			case 255: // extended
				if ( m_memory.data[m_pc] != 255 ) {
					incPC(sizeof(vmByte));
				}
			break;

		}

		// Normalize m_pc
		if ( m_pc >= memsize ) m_pc = 0;
		else if ( m_pc < 0 ) m_pc = 0;

		// Normalize m_sp
		if ( m_sp >= memsize ) m_sp = memsize;
		else if ( m_sp < 0 ) m_sp = 0;

	}

}


}
