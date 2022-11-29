#pragma once

#include "Direction.h"

namespace ConsoleGame
{
   class PlayerConfig
   {
   public:
      PlayerConfig() :
         StartVelocityX( 0. ),
         StartVelocityY( 0. ),
         MaxVelocity( 0. ),
         AccelerationPerSecond( 0. ),
         StartDirection( (Direction)0 ) { }

      double StartVelocityX;
      double StartVelocityY;

      double MaxVelocity;

      double AccelerationPerSecond;

      Direction StartDirection;
   };
}
