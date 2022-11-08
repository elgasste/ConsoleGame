#pragma once

#include "IGameStateProvider.h"
#include "IGameCommandExecutor.h"

namespace ConsoleGame
{
   enum class GameState;
   enum class GameCommand;

   class Game : public IGameStateProvider,
                public IGameCommandExecutor
   {
   public:
      Game();

      GameState GetGameState() const override { return _state; }

      void ExecuteCommand( GameCommand command );

   private:
      GameState _state;
   };
}
