#pragma once

#include <map>

#include "IGameRenderDefs.h"
#include "ConsoleSprite.h"
#include "Direction.h"

namespace ConsoleGame
{
   class ConsoleRenderDefs : public IGameRenderDefs
   {
   public:
      short ConsoleWidth = 0;
      short ConsoleHeight = 0;

      short ArenaCharWidth = 0;
      short ArenaCharHeight = 0;

      short ArenaFenceX = 0;
      short ArenaFenceY = 0;

      ConsoleColor DefaultForegroundColor = (ConsoleColor)0;
      ConsoleColor DefaultBackgroundColor = (ConsoleColor)0;

      ConsoleSprite PlayerStaticSprite;
      std::map<Direction, ConsoleSprite> PlayerMovingSpriteMap;
   };
}
