#pragma once

#include "IHighResolutionClock.h"

namespace ConsoleGame
{
   class HighResolutionClockWrapper : public IHighResolutionClock
   {
   public:
      std::chrono::steady_clock::time_point Now() override
      {
         return std::chrono::high_resolution_clock::now();
      }
   };
}
