#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;
   class ConsoleRenderConfig;
   class GameInputConfig;

   class StartupStateConsoleRenderer : public IGameRenderer
   {
   public:
      StartupStateConsoleRenderer( const std::shared_ptr<IConsoleDrawer> consoleDrawer,
                                   const std::shared_ptr<ConsoleRenderConfig> renderConfig,
                                   const std::shared_ptr<GameInputConfig> inputConfig );

      void Render() override;

   private:
      void DrawKeyBindings( int middleX, int top ) const;

   private:
      const std::shared_ptr<IConsoleDrawer> _consoleDrawer;
      const std::shared_ptr<ConsoleRenderConfig> _renderConfig;
      const std::shared_ptr<GameInputConfig> _inputConfig;
   };
}
