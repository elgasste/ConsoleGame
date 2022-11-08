#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;
   class GameRenderConfig;

   class StartupStateConsoleRenderer : public IGameRenderer
   {
   public:
      StartupStateConsoleRenderer( const std::shared_ptr<IConsoleDrawer>& consoleDrawer,
                                   const std::shared_ptr<GameRenderConfig>& renderConfig );

      void Render() override;

   private:
      const std::shared_ptr<IConsoleDrawer>& _consoleDrawer;
      const std::shared_ptr<GameRenderConfig>& _renderConfig;
   };
}
