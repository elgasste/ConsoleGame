#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IArenaInfoProvider
   {
   public:
      virtual int GetArenaWidth() const = 0;
      virtual int GetArenaHeight() const = 0;

      virtual int GetArenaPlayerXPosition() const = 0;
      virtual int GetArenaPlayerYPosition() const = 0;
   };
}
