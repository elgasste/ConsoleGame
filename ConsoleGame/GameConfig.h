#pragma once

#include <memory>

namespace ConsoleGame
{
   class GameRenderConfig;
   class GameInputConfig;

   class GameConfig
   {
   public:
      int FramesPerSecond;

      std::shared_ptr<GameRenderConfig> RenderConfig;
      std::shared_ptr<GameInputConfig> InputConfig;
   };
}
