#ifndef COREIO_H
#define COREIO_H

#include "vm/io.h"
#include "vm/vm.h"
#include "vm/memory.h"

namespace bot { class Bot; }

namespace vm
{

class CoreIO : public IO
{
  public:
    CoreIO();
    ~CoreIO();
    static IO* createCoreIOPart(Setting& sett );

    std::string className() { return "Core"; }

    int update( bot::Bot& bot );

    vmByte readByte( unsigned int index );
		void writeByte( unsigned int index, const vmByte& data );

    VM* vm() { return m_vm; }
    void setVM( VM* newVM ) { m_vm = newVM; }

  protected:

    VM* m_vm;

};


}

#endif // COREIO_H
