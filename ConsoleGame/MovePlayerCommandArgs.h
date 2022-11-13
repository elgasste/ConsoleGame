#pragma once

#include "GameCommandArgs.h"

namespace ConsoleGame
{
   enum class Direction;

   class MovePlayerCommandArgs : public GameCommandArgs
   {
   public:
      Direction Direction;
   };
}
