#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) ISleeper
   {
   public:
      virtual void Sleep( unsigned long milliseconds ) = 0;
   };
}
