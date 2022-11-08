#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IGameRenderer
   {
   public:
      virtual void Render() = 0;
   };
}
