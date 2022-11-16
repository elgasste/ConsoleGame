#pragma once

#include "ISleeper.h"

namespace ConsoleGame
{
   class SleeperWrapper : public ISleeper
   {
   public:
      void Sleep( long long nanoseconds ) override;
   };
}
