#pragma once

#include <map>

#include "IGameRenderConfig.h"

namespace ConsoleGame
{
   enum class ConsoleColor;
   enum class Direction;
   struct ConsoleSprite;

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

      std::map<Direction, ConsoleSprite> PlayerSpriteMap;
   };
}
