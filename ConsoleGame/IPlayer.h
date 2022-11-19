#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class __declspec( novtable ) IPlayer
   {
   public:
      virtual void Push( Direction direction ) = 0;

      virtual int GetVelocityX() const = 0;
      virtual int GetVelocityY() const = 0;

      virtual Direction GetDirection() const = 0;
   };
}
