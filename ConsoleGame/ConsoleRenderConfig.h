#pragma once

#include <map>

#include "IGameRenderConfig.h"
#include "ConsoleSprite.h"

namespace ConsoleGame
{
   enum class ConsoleColor;
   enum class Direction;

   class ConsoleRenderConfig : public IGameRenderConfig
   {
   public:
      short ConsoleWidth;
      short ConsoleHeight;

      short ArenaCharWidth;
      short ArenaCharHeight;

      short ArenaFenceX;
      short ArenaFenceY;

      ConsoleColor DefaultForegroundColor;
      ConsoleColor DefaultBackgroundColor;

      ConsoleSprite PlayerStaticSprite;
      std::map<Direction, ConsoleSprite> PlayerMovingSpriteMap;
   };
}
