#ifndef COREIO_H
#define COREIO_H

#include "vm/io.h"
#include "vm/memory.h"
#include "vm/vm.h"
#include "util/debug.h"

#include <vector>



namespace bot { class Bot; }

namespace vm
{


typedef unsigned char IOIndex;

typedef std::vector<IO*> IOVector;
typedef std::vector<IO*>::iterator IOVectorIter;
typedef std::vector<IO*>::const_iterator IOVectorCIter;


class CoreIO : public IO
{
  public:
    CoreIO();
    ~CoreIO();
    static IO* createCoreIOPart( Setting& sett );

    inline std::string className() { return "Core"; }

    int update( bot::Bot& bot );

    vmByte readByte( const unsigned int& index );
    void writeByte( const unsigned int& index, const vmByte& data );

    inline IO& getIO( const IOIndex& index )
    {
      if (m_ios.size() <= index) return m_nullIO;
      return *m_ios[index];
    }

    inline unsigned int size() { return memory().size(); }

    inline VM& vm();
    inline void setVM( VM* newVM );


    inline Memory& memory()
    {
      assert(m_vm != 0, "CoreIO::memory(): m_vm is null.");
      return m_vm->memory();
    }

    void clearIOList();
    IOIndex addIO( Setting& s );

  protected:

    VM* m_vm;
    IOVector m_ios;
    NullIO m_nullIO;

};


}

#endif // COREIO_H
