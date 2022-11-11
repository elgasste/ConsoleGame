#pragma once

#include <chrono>

namespace ConsoleGame
{
   class __declspec( novtable ) IHighResolutionClock
   {
   public:
      virtual std::chrono::steady_clock::time_point Now() = 0;
   };
}
