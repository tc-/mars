#include "coreio.h"
#include <assert.h>

namespace vm
{


CoreIO::CoreIO()
{
    m_vm = 0;
}

CoreIO::~CoreIO()
{
  delete m_vm;
}


IO* CoreIO::createCoreIOPart(Setting& sett )
{
  unsigned int memorySize = 1024;
  unsigned int cpuSpeed = 10;

  CoreIO* ret = new CoreIO();

  sett.lookupValue("memorysize", memorySize);
  sett.lookupValue("cpuspeed", cpuSpeed);

  Memory* m = new Memory(memorySize);
  ret->setVM( new VM(*m, cpuSpeed, 0, ret) );

  return ret;
}


int CoreIO::update( bot::Bot& bot )
{
  assert(m_vm != 0);
  m_vm->update();
  return 0;
}


vmByte CoreIO::readByte( unsigned int index )
{
  return 0;
}


void CoreIO::writeByte( unsigned int index, const vmByte& data )
{
}


}

