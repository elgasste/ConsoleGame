#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) ISleeper
   {
   public:
      virtual void Sleep( long long nanoseconds ) = 0;
   };
}
