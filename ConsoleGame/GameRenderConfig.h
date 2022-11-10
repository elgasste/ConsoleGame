#pragma once

namespace ConsoleGame
{
   enum class ConsoleColor;

   class GameRenderConfig
   {
   public:
      short ConsoleWidth;
      short ConsoleHeight;

      short ArenaFenceX;
      short ArenaFenceY;

      ConsoleColor DefaultForegroundColor;
      ConsoleColor DefaultBackgroundColor;
   };
}
