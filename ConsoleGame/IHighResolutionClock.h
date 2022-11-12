#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IHighResolutionClock
   {
   public:
      virtual long long Now() = 0;
   };
}
