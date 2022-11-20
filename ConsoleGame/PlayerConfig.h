#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class PlayerConfig
   {
   public:
      int StartVelocityX;
      int StartVelocityY;

      int MaxVelocityX;
      int MaxVelocityY;

      int VelocityDeltaX;
      int VelocityDeltaY;

      Direction StartDirection;
   };
}
