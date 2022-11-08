#pragma once

#include <memory>

#include "IGameStateProvider.h"
#include "IGameCommandExecutor.h"

namespace ConsoleGame
{
   enum class GameState;
   enum class GameCommand;
   class IGameEventAggregator;

   class Game : public IGameStateProvider,
                public IGameCommandExecutor
   {
   public:
      Game( const std::shared_ptr<IGameEventAggregator>& eventAggregator );

      GameState GetGameState() const override { return _state; }

      void ExecuteCommand( GameCommand command );

   private:
      const std::shared_ptr<IGameEventAggregator>& _eventAggregator;

      GameState _state;
   };
}
