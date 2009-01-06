#include "coreio.h"
#include "bot/bot.h"
#include "util/debug.h"

#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_CPU_SPEED 16

#define CoreIODataSize 16

namespace vm
{


CoreIO::CoreIO(): m_vm(0), lastIOPos(CoreIODataSize), m_ios(8)
{
}

CoreIO::~CoreIO()
{
}


IO* CoreIO::createCoreIOPart(Setting& sett )
{
  unsigned int memorySize = DEFAULT_MEM_SIZE;
  unsigned int cpuSpeed = DEFAULT_CPU_SPEED;

  sett.lookupValue("memory", memorySize);
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
  assert(m_vm != 0, "CoreIO::update( bot::Bot& bot ): m_vm is null.");
  m_vm->update();
  for ( int unsigned i = 0; i < m_ios.count(); i++ ) {
    IO* io = m_ios.get(i);
    if ( io == 0 ) continue;
    t += io->update( bot );
  }
  //TODO: m_vm-> // Update vm time left with t
  return 0;
}


VM& CoreIO::vm()
{
  assert(m_vm != 0, "CoreIO::vm(): m_vm is null.");
  return *m_vm;
}


void CoreIO::setVM( VM* newVM )
{
  m_vm = newVM;
  if ( m_vm != 0 ) m_vm->reset(0,0);
}


Memory& CoreIO::memory()
{
  assert(m_vm != 0, "CoreIO::memory(): m_vm is null.");
  return m_vm->memory();
}


vmByte CoreIO::readByte( unsigned int index )
{
  if ( index < CoreIODataSize ) {

  } else if ( index < lastIOPos ) {
  } else {
    return m_vm->memory().data[index];
  }
  return 0;
}


void CoreIO::writeByte( unsigned int index, const vmByte& data )
{

}

void CoreIO::clearIOList()
{
  m_ios.clear(); // TODO: Fix memleak here.
}


void CoreIO::addIO( Setting& s )
{
  vm::IO* io = bot::Bot::s_iof.createIO(s, (char*)&m_vm->memory().data[lastIOPos], m_vm->memory().size() - lastIOPos );
  if ( io != 0 ) {
    m_ios.add( io, io->size() );
    //lastIOPos += ; TODO
  }
}


}

