#ifndef IO_H
#define IO_H

#include <string>
#include <map>
#include "vm/vmtypes.h"
#include <libconfig.h++>

using namespace libconfig;

namespace bot { class Bot; }

namespace vm
{

class IO;

typedef IO* (*iofactoryfunc)(Setting&);
typedef std::map<std::string,iofactoryfunc> FactoryMap;

class IO
{
	public:

    virtual std::string className() = 0;

    virtual int update( bot::Bot& bot ) = 0;

    virtual bool isPublic() { return false; }

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

  private:


};


class NullIO: public IO
{
  public:
    std::string className() { return "Null"; }
    bool isPublic() { return true; }

    int update( bot::Bot& bot ) { return 0; }

    vmByte readByte( unsigned int index ) { return 0; }
    void writeByte( unsigned int index, const vmByte& data ) {}

    static NullIO& nullIO();
    static IO* createIOPart(Setting& sett ) { return new NullIO; }
};


class IOFactory
{
  public:
    IO* createIO( Setting& sett );
    void addIOClass( const std::string& className, iofactoryfunc factory );
    void clearIOClasses();
  private:
    FactoryMap m_factorymap;
};


}

#endif // IO_H
