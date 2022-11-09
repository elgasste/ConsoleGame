#pragma once

#include <memory>

#include "IGameStateProvider.h"
#include "IGameCommandExecutor.h"
#include "IPlayerInfoProvider.h"

namespace ConsoleGame
{
   enum class GameState;
   enum class GameCommand;
   enum class Direction;
   class IGameEventAggregator;

   class Game : public IGameStateProvider,
      public IGameCommandExecutor,
      public IPlayerInfoProvider
   {
   public:
      Game( const std::shared_ptr<IGameEventAggregator>& eventAggregator );

      GameState GetGameState() const override { return _state; }

      void ExecuteCommand( GameCommand command );

      Direction GetPlayerDirection() const override{ return _playerDirection; }
      int GetPlayerXPosition() const override { return _playerPositionX; }
      int GetPlayerYPosition() const override { return _playerPositionY; }

   private:
      const std::shared_ptr<IGameEventAggregator>& _eventAggregator;

      GameState _state;

      Direction _playerDirection;
      int _playerPositionX;
      int _playerPositionY;
   };
}
