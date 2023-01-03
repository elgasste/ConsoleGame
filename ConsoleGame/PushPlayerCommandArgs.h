#pragma once

#include "GameCommandArgs.h"
#include "Direction.h"

namespace ConsoleGame
{
   class PushPlayerCommandArgs : public GameCommandArgs
   {
   public:
      PushPlayerCommandArgs( Direction direction ) :
         Direction ( direction )
      { }

      Direction Direction;
   };
}
