#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IArenaInfoProvider
   {
   public:
      virtual int GetPlayerXPosition() const = 0;
      virtual int GetPlayerYPosition() const = 0;
   };
}
