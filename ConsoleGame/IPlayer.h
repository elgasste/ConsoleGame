#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class __declspec( novtable ) IPlayer
   {
      virtual int GetPositionX() const = 0;
      virtual int GetPositionY() const = 0;

      virtual int GetVelocityX() const = 0;
      virtual int GetVelocityY() const = 0;

      virtual Direction GetDirection() const = 0;
   };
}
