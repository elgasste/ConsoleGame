#pragma once

#include <memory>

namespace ConsoleGame
{
   class IGameRenderConfig;
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

      std::shared_ptr<IGameRenderConfig> RenderConfig;
      std::shared_ptr<GameInputConfig> InputConfig;
   };
}
