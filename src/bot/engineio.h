#ifndef ENGINEIO_H
#define ENGINEIO_H

#include "vm/io.h"

namespace bot
{

class EngineIO : public vm::IO
{
  public:
    EngineIO();
    ~EngineIO();

    virtual void update() = 0;

  protected:
  private:
};

}

#endif // ENGINEIO_H
