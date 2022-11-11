#pragma once

#include "IHighResolutionClock.h"

namespace ConsoleGame
{
   class HighResolutionClockWrapper : public IHighResolutionClock
   {
   public:
      long long Now() override;
   };
}
