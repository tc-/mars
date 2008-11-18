#include "coreio.h"
#include <assert.h>


#define IO_BLOCK_SIZE 1024
#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_CPU_SPEED 16

namespace vm
{


CoreIO::CoreIO(): m_vm(0)
{
}

CoreIO::~CoreIO()
{
}


IO* CoreIO::createCoreIOPart(Setting& sett )
{
  unsigned int memorySize = DEFAULT_MEM_SIZE;
  unsigned int cpuSpeed = DEFAULT_CPU_SPEED;

  sett.lookupValue("memorysize", memorySize);
  sett.lookupValue("cpuspeed", cpuSpeed);

  Memory* memory = new Memory(memorySize);
  CoreIO* ret = new CoreIO();
  VM* vm =  new VM(*memory, cpuSpeed, 0, *ret);
  ret->setVM( vm );

  return ret;
}


int CoreIO::update( bot::Bot& bot )
{
  unsigned int t = 0;
  assert(m_vm != 0);
  m_vm->update();
  for ( int unsigned i = 0; i < m_ios.size(); i++ ) {
    t += m_ios[i]->update( bot );
  }
  //m_vm-> // Update vm time left with t
  return 0;
}


VM& CoreIO::vm()
{
  assert(m_vm != 0);
  return *m_vm;
}


void CoreIO::setVM( VM* newVM )
{
  m_vm = newVM;
}


vmByte CoreIO::readByte( unsigned int index )
{
  unsigned int ioindex = index / IO_BLOCK_SIZE;
  if ( ioindex == 0 ) {

  } else {
    ioindex--;
    if ( ioindex < m_ios.size() ) return m_ios[ioindex]->readByte( index - ioindex * IO_BLOCK_SIZE );
  }
  return 0;
}


void CoreIO::writeByte( unsigned int index, const vmByte& data )
{
  unsigned int ioindex = index / IO_BLOCK_SIZE;
  if ( ioindex == 0 ) {

  } else {
    ioindex--;
    if ( ioindex < m_ios.size() ) m_ios[ioindex]->writeByte( index - ioindex * IO_BLOCK_SIZE, data );
  }
}

void CoreIO::clearIOList()
{
  m_ios.clear();
}


void CoreIO::addIO( IO& io )
{
  m_ios.push_back( &io );
}


}

