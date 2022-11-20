#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class __declspec( novtable ) IPlayer
   {
   public:
      virtual void Push( Direction direction ) = 0;
      virtual void ApplyFrictionX() = 0;
      virtual void ApplyFrictionY() = 0;
      virtual void StopX() = 0;
      virtual void StopY() = 0;

      virtual double GetVelocityX() const = 0;
      virtual double GetVelocityY() const = 0;

      virtual Direction GetDirection() const = 0;
   };
}
