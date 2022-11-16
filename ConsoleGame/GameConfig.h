#pragma once

#include <memory>

namespace ConsoleGame
{
   class IGameRenderConfig;
   class IGameInputConfig;
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
      std::shared_ptr<IGameInputConfig> InputConfig;
   };
}
