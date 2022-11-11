#pragma once

#include "ISleeper.h"

namespace ConsoleGame
{
   class SleeperWrapper : public ISleeper
   {
   public:
      void Sleep( unsigned long milliseconds ) override;
   };
}
