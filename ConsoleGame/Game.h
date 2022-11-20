#pragma once

#include <memory>

#include "IGame.h"
#include "IGameCommandExecutor.h"
#include "IGameInfoProvider.h"

namespace ConsoleGame
{
   class GameConfig;
   enum class Direction;
   class IGameEventAggregator;
   class IPlayerFactory;
   class IPlayer;

   class Game : public IGame,
                public IGameCommandExecutor,
                public IGameInfoProvider
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
      bool IsPlayerMoving() const override;

      double GetArenaWidth() const override;
      double GetArenaHeight() const override;

      double GetArenaPlayerXPosition() const override { return _arenaPlayerPositionX; }
      double GetArenaPlayerYPosition() const override { return _arenaPlayerPositionY; }

   private:
      void PushPlayer( Direction direction );
      void MovePlayer();

   private:
      const std::shared_ptr<GameConfig> _config;
      const std::shared_ptr<IGameEventAggregator> _eventAggregator;
      const std::shared_ptr<IPlayer> _player;

      GameState _state;

      double _arenaPlayerPositionX;
      double _arenaPlayerPositionY;

      bool _playerWasPushedX;
      bool _playerWasPushedY;
   };
}
