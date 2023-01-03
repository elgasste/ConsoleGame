#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class PlayerDefs
   {
   public:
      float StartVelocityX = 0;
      float StartVelocityY = 0;

      float MaxVelocity = 0;

      float AccelerationPerSecond = 0;

      Direction StartDirection = (Direction)0;
   };
}
