#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class PlayerDefs
   {
   public:
      double StartVelocityX = 0.;
      double StartVelocityY = 0.;

      double MaxVelocity = 0.;

      double AccelerationPerSecond = 0.;

      Direction StartDirection = (Direction)0;
   };
}
