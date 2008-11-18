#ifndef COREIO_H
#define COREIO_H

#include "vm/io.h"
#include "vm/vm.h"
#include "vm/memory.h"
#include <vector>


namespace bot { class Bot; }

namespace vm
{

typedef std::vector<IO*> IOVector;

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

    VM& vm();
    void setVM( VM* newVM );

    void clearIOList();
    void addIO( IO& io );

  protected:

    VM* m_vm;
    IOVector m_ios;

};


}

#endif // COREIO_H
