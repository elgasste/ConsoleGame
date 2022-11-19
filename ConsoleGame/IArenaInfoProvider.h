#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IArenaInfoProvider
   {
   public:
      virtual int GetArenaPlayerXPosition() const = 0;
      virtual int GetArenaPlayerYPosition() const = 0;
   };
}
