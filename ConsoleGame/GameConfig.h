#pragma once

#include <memory>

namespace ConsoleGame
{
   class GameRenderConfig;
   class GameInputConfig;
   enum class Direction;

   class GameConfig
   {
   public:
      int FramesPerSecond;

      short ArenaWidth;
      short ArenaHeight;

      Direction PlayerStartDirection;
      short PlayerStartX;
      short PlayerStartY;

      std::shared_ptr<GameRenderConfig> RenderConfig;
      std::shared_ptr<GameInputConfig> InputConfig;
   };
}
