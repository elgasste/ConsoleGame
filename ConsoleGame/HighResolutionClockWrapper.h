#pragma once

#include "IHighResolutionClock.h"

namespace ConsoleGame
{
   class HighResolutionClockWrapper : public IHighResolutionClock
   {
   public:
      HighResolutionClockWrapper();
      ~HighResolutionClockWrapper();

      long long Now() override;
   };
}
