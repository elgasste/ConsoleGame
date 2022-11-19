#pragma once

#include <memory>

namespace ConsoleGame
{
   class IGameRenderConfig;
   class IGameInputConfig;
   class PlayerConfig;
   class ArenaConfig;
   enum class Direction;

   class GameConfig
   {
   public:
      int FramesPerSecond;

      std::shared_ptr<IGameRenderConfig> RenderConfig;
      std::shared_ptr<IGameInputConfig> InputConfig;
      std::shared_ptr<PlayerConfig> PlayerConfig;
      std::shared_ptr<ArenaConfig> ArenaConfig;
   };
}
