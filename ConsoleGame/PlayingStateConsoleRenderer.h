#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;
   class GameRenderConfig;
   class GameConfig;
   class IPlayerInfoProvider;
   enum class Direction;

   class PlayingStateConsoleRenderer : public IGameRenderer
   {
   public:
      PlayingStateConsoleRenderer( const std::shared_ptr<IConsoleDrawer>& consoleDrawer,
                                   const std::shared_ptr<GameRenderConfig>& renderConfig,
                                   const std::shared_ptr<GameConfig>& gameConfig,
                                   const std::shared_ptr<IPlayerInfoProvider>& playerInfoProvider );

      void Render() override;

   private:
      void DrawArenaFence();
      char GetPlayerCharFromDirection( Direction direction );

   private:
      const std::shared_ptr<IConsoleDrawer>& _consoleDrawer;
      const std::shared_ptr<GameRenderConfig>& _renderConfig;
      const std::shared_ptr<GameConfig>& _gameConfig;
      const std::shared_ptr<IPlayerInfoProvider>& _playerInfoProvider;
   };
}
