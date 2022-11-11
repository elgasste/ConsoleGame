#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;
   class IGameClock;
   class GameRenderConfig;

   class DiagnosticsConsoleRenderer : public IGameRenderer
   {
   public:
      DiagnosticsConsoleRenderer( const std::shared_ptr<IConsoleDrawer> consoleDrawer,
                                  const std::shared_ptr<IGameClock> clock,
                                  const std::shared_ptr<GameRenderConfig> renderConfig );

      void Render() override;

   private:
      const std::shared_ptr<IConsoleDrawer> _consoleDrawer;
      const std::shared_ptr<IGameClock> _clock;
      const std::shared_ptr<GameRenderConfig> _renderConfig;
   };
}
