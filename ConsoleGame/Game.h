#pragma once

#include <memory>

#include "IGame.h"
#include "IGameStateProvider.h"
#include "IGameCommandExecutor.h"
#include "IPlayerInfoProvider.h"
#include "IArenaInfoProvider.h"

namespace ConsoleGame
{
   class GameConfig;
   enum class Direction;
   class IGameEventAggregator;
   class IPlayerFactory;
   class IPlayer;

   class Game : public IGame,
                public IGameStateProvider,
                public IGameCommandExecutor,
                public IPlayerInfoProvider,
                public IArenaInfoProvider
   {
   public:
      Game( const std::shared_ptr<GameConfig> config,
            const std::shared_ptr<IGameEventAggregator> eventAggregator,
            const std::shared_ptr<IPlayerFactory> playerFactory );

      void RunFrame() override;

      GameState GetGameState() const override { return _state; }

      void ExecuteCommand( GameCommand command ) override;
      void ExecuteCommand( GameCommand command, const std::shared_ptr<GameCommandArgs> args ) override;

      Direction GetPlayerDirection() const override;

      int GetArenaPlayerXPosition() const override { return _playerPositionX; }
      int GetArenaPlayerYPosition() const override { return _playerPositionY; }

   private:
      void MovePlayer( Direction direction );

   private:
      const std::shared_ptr<GameConfig> _config;
      const std::shared_ptr<IGameEventAggregator> _eventAggregator;
      const std::shared_ptr<IPlayer> _player;

      GameState _state;

      int _playerPositionX;
      int _playerPositionY;
   };
}
