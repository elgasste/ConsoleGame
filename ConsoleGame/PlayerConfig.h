#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class PlayerConfig
   {
   public:
      double StartVelocityX;
      double StartVelocityY;

      double MaxVelocity;

      double AccelerationPerSecond;

      Direction StartDirection;
   };
}
