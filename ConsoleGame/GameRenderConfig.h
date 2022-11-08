#pragma once

namespace ConsoleGame
{
   enum class ConsoleColor;

   class GameRenderConfig
   {
   public:
      short ConsoleWidth;
      short ConsoleHeight;

      ConsoleColor DefaultForegroundColor;
      ConsoleColor DefaultBackgroundColor;
   };
}
