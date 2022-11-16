#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;
   class IGameClock;
   class ConsoleRenderConfig;

   class DiagnosticsConsoleRenderer : public IGameRenderer
   {
   public:
      DiagnosticsConsoleRenderer( const std::shared_ptr<IConsoleDrawer> consoleDrawer,
                                  const std::shared_ptr<IGameClock> clock,
                                  const std::shared_ptr<ConsoleRenderConfig> renderConfig );

      void Render() override;

   private:
      const std::shared_ptr<IConsoleDrawer> _consoleDrawer;
      const std::shared_ptr<IGameClock> _clock;
      const std::shared_ptr<ConsoleRenderConfig> _renderConfig;
   };
}
