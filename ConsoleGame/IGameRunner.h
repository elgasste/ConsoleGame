#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IGameRunner
   {
   public:
      virtual void Run() = 0;
   };
}
