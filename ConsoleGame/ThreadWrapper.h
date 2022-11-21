#pragma once

#include "IThread.h"

namespace ConsoleGame
{
   class ThreadWrapper : public IThread
   {
   public:
      bool SetThisThreadToHighestPriority() const override;
   };
}
