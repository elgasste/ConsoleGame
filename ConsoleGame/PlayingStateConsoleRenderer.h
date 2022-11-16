#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;
   class ConsoleRenderConfig;
   class GameConfig;
   class IPlayerInfoProvider;

   class PlayingStateConsoleRenderer : public IGameRenderer
   {
   public:
      PlayingStateConsoleRenderer( const std::shared_ptr<IConsoleDrawer> consoleDrawer,
                                   const std::shared_ptr<ConsoleRenderConfig> renderConfig,
                                   const std::shared_ptr<GameConfig> gameConfig,
                                   const std::shared_ptr<IPlayerInfoProvider> playerInfoProvider );

      void Render() override;

   private:
      void DrawArenaFence();

   private:
      const std::shared_ptr<IConsoleDrawer> _consoleDrawer;
      const std::shared_ptr<ConsoleRenderConfig> _renderConfig;
      const std::shared_ptr<GameConfig> _gameConfig;
      const std::shared_ptr<IPlayerInfoProvider> _playerInfoProvider;
   };
}
