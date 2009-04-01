#ifndef IO_H
#define IO_H

#include <string>
#include <map>
#include "vm/vmtypes.h"
#include <libconfig.h++>

using namespace libconfig;

namespace bot
{
class Bot;
}

namespace vm
{

class IO;
class VM;

typedef IO* ( *iofactoryfunc )( Setting&, VM& );
typedef std::map<std::string, iofactoryfunc> FactoryMap;

class IO
{
	public:

		virtual std::string className() = 0;

		virtual int update( bot::Bot& bot ) = 0;

		virtual bool isPublic() {
			return false;
		}
		virtual unsigned int size() = 0;

		virtual vmByte readByte( const unsigned int& index ) = 0;
		virtual vmInt readInt( const unsigned int& index );
		virtual vmUInt readUInt( const unsigned int& index );
		virtual vmFloat readFloat( const unsigned int& index );
		virtual vmBool readBool( const unsigned int& index );
		virtual vmSByte readSByte( const unsigned int& index );

		virtual void writeByte( const unsigned int& index, const vmByte& data ) = 0;
		virtual void writeInt( const unsigned int& index, const vmInt& data );
		virtual void writeUInt( const unsigned int& index, const vmUInt& data );
		virtual void writeFloat( const unsigned int& index, const vmFloat& data );
		virtual void writeBool( const unsigned int& index, const vmBool& data );
		virtual void writeSByte( const unsigned int& index, const vmSByte& data );

	private:


};


class NullIO: public IO
{
	public:
		std::string className() {
			return "Null";
		}
		bool isPublic() {
			return true;
		}

		int update( bot::Bot& bot ) {
			return 0;
		}

		unsigned int size() {
			return 0;
		}

		vmByte readByte( const unsigned int& index ) {
			return 0;
		}
		void writeByte( const unsigned int& index, const vmByte& data ) {}

		static NullIO& nullIO();
		static IO* createIOPart( Setting& sett, VM& vm) {
			return new NullIO;
		}
		static unsigned int IOSize( Setting& sett ) {
			return 0;
		}
};


class IOFactory
{
	public:
		IO* createIO( Setting& sett, VM& vm );
		void addIOClass( const std::string& className, iofactoryfunc factory );
		void clearIOClasses();
	private:
		FactoryMap m_factorymap;
};


}

#endif // IO_H
