#pragma once

#include <map>

namespace ConsoleGame
{
   enum class ConsoleColor;
   enum class Direction;
   struct ConsoleSprite;

   class GameRenderConfig
   {
   public:
      short ConsoleWidth;
      short ConsoleHeight;

      short ArenaFenceX;
      short ArenaFenceY;

      ConsoleColor DefaultForegroundColor;
      ConsoleColor DefaultBackgroundColor;

      std::map<Direction, ConsoleSprite> PlayerSpriteMap;
   };
}
