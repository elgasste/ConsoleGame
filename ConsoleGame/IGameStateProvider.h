#pragma once

namespace ConsoleGame
{
   enum class GameState;

   class __declspec( novtable ) IGameStateProvider
   {
   public:
      virtual GameState GetGameState() const = 0;
   };
}
