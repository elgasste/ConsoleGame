#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IGame
   {
   public:
      virtual void Tick() = 0;
   };
}
