#pragma once

#include <memory>

#include "IGameStateProvider.h"
#include "IGameCommandExecutor.h"
#include "IPlayerInfoProvider.h"

namespace ConsoleGame
{
   class GameConfig;
   enum class Direction;
   class IGameEventAggregator;
   class IPlayerFactory;
   class IPlayer;

   class Game : public IGameStateProvider,
                public IGameCommandExecutor,
                public IPlayerInfoProvider
   {
   public:
      Game( const std::shared_ptr<GameConfig> config,
            const std::shared_ptr<IGameEventAggregator> eventAggregator,
            const std::shared_ptr<IPlayerFactory> playerFactory );

      GameState GetGameState() const override { return _state; }

      void ExecuteCommand( GameCommand command ) override;
      void ExecuteCommand( GameCommand command, const std::shared_ptr<GameCommandArgs> args ) override;

      Direction GetPlayerDirection() const override{ return _playerDirection; }
      int GetPlayerXPosition() const override { return _playerPositionX; }
      int GetPlayerYPosition() const override { return _playerPositionY; }

   private:
      void MovePlayer( Direction direction );

   private:
      const std::shared_ptr<GameConfig> _config;
      const std::shared_ptr<IGameEventAggregator> _eventAggregator;
      const std::shared_ptr<IPlayer> _player;

      GameState _state;

      Direction _playerDirection;
      int _playerPositionX;
      int _playerPositionY;
   };
}
