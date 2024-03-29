#pragma once

#include "IGame.h"
#include "IGameCommandExecutor.h"
#include "IGameInfoProvider.h"

namespace ConsoleGame
{
   class GameDefs;
   class IFrameRateProvider;
   class GameEventAggregator;
   class PlayerFactory;
   class Player;

   class Game : public IGame,
                public IGameCommandExecutor,
                public IGameInfoProvider
   {
   public:
      Game( const std::shared_ptr<GameDefs> gameDefs,
            const std::shared_ptr<IFrameRateProvider> frameRateProvider,
            const std::shared_ptr<GameEventAggregator> eventAggregator,
            const std::shared_ptr<PlayerFactory> playerFactory );

      void Tick() override;

      GameState GetGameState() const override { return _state; }

      void ExecuteCommand( GameCommand command ) override;
      void ExecuteCommand( GameCommand command, const std::shared_ptr<GameCommandArgs> args ) override;

      Direction GetPlayerDirection() const override;
      bool IsPlayerMoving() const override;

      float GetArenaWidth() const override;
      float GetArenaHeight() const override;

      float GetArenaPlayerXPosition() const override { return _arenaPlayerPositionX; }
      float GetArenaPlayerYPosition() const override { return _arenaPlayerPositionY; }

   private:
      void PushPlayer( Direction direction );
      void MovePlayer();

   private:
      const std::shared_ptr<GameDefs> _gameDefs;
      const std::shared_ptr<IFrameRateProvider> _frameRateProvider;
      const std::shared_ptr<GameEventAggregator> _eventAggregator;
      const std::shared_ptr<Player> _player;

      GameState _state;

      float _arenaPlayerPositionX;
      float _arenaPlayerPositionY;

      bool _playerWasPushedX;
      bool _playerWasPushedY;
   };
}
