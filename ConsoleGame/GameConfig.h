#pragma once

#include <memory>

namespace ConsoleGame
{
   class IGameRenderConfig;
   class IGameInputConfig;
   class PlayerConfig;
   enum class Direction;

   class GameConfig
   {
   public:
      int FramesPerSecond;

      int ArenaWidth;
      int ArenaHeight;

      int PlayerStartX;
      int PlayerStartY;

      std::shared_ptr<IGameRenderConfig> RenderConfig;
      std::shared_ptr<IGameInputConfig> InputConfig;
      std::shared_ptr<PlayerConfig> PlayerConfig;
   };
}
