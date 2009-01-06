#ifndef COREIO_H
#define COREIO_H

#include "vm/io.h"
#include "vm/vm.h"
#include "vm/memory.h"
#include "util/intervalvector.h"


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

    unsigned int size() { return memory().size(); }

    VM& vm();
    void setVM( VM* newVM );

    Memory& memory();

    void clearIOList();
    void addIO( Setting& s );

  protected:

    VM* m_vm;
    unsigned int lastIOPos;
    util::IntervalVector<IO> m_ios;

};


}

#endif // COREIO_H
