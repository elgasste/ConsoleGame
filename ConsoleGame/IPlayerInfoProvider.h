#pragma once

namespace ConsoleGame
{
   enum class Direction;

   class __declspec( novtable ) IPlayerInfoProvider
   {
   public:
      virtual Direction GetPlayerDirection() const = 0;
      virtual int GetPlayerXPosition() const = 0;
      virtual int GetPlayerYPosition() const = 0;
   };
}
