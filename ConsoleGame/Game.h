#pragma once

#include "IGameStateProvider.h"

namespace ConsoleGame
{
   enum class GameState;

   class Game : public IGameStateProvider
   {
   public:
      Game();

      GameState GetGameState() const override { return _state; }

   private:
      GameState _state;
   };
}
