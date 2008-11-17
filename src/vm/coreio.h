#ifndef COREIO_H
#define COREIO_H

#include "vm/io.h"

namespace vm
{

class CoreIO : public IO
{
  public:
    CoreIO();
    ~CoreIO();

    std::string className() { return "Core"; }

  protected:
  private:
};


}

#endif // COREIO_H
