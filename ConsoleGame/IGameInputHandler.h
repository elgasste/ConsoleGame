#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IGameInputHandler
   {
   public:
      virtual void HandleInput() = 0;
   };
}
