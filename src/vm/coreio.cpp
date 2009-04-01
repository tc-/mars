#include "coreio.h"
#include "bot/bot.h"
#include "util/debug.h"


#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_CPU_SPEED 16

#define CoreIODataSize 16

namespace vm
{


CoreIO::CoreIO(): m_vm(0)
{
  m_ios.push_back(this);
}

CoreIO::~CoreIO()
{
  clearIOList();
}


IO* CoreIO::createCoreIOPart( Setting& sett )
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
  for ( IOVectorCIter i = m_ios.begin(); i != m_ios.end(); i++ ) {
    if ( *i == 0 ) continue;
    t += (*i)->update( bot );
  }
  m_vm->setTimeLeftD(-t);
  return t;
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


vmByte CoreIO::readByte( const unsigned int& index )
{
  return 0;
}


void CoreIO::writeByte( const unsigned int& index, const vmByte& data )
{

}


void CoreIO::clearIOList()
{
  assert(false, "CoreIO::clearIOList(): Plox fix memleak here.");
  m_ios.clear(); /// @TODO Fix memleak here.
}


IOIndex CoreIO::addIO( Setting& s )
{
  vm::IO* io = bot::Bot::s_iof.createIO(s, *m_vm );
  if ( io != 0 ) {
    m_ios.push_back( io );
    return m_ios.size() - 1;
  }
  return 0;
}


}

