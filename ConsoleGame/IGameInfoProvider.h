#pragma once

namespace ConsoleGame
{
   enum class GameState;
   enum class Direction;

   class __declspec( novtable ) IGameInfoProvider
   {
   public:
      virtual GameState GetGameState() const = 0;

      virtual Direction GetPlayerDirection() const = 0;

      virtual int GetArenaWidth() const = 0;
      virtual int GetArenaHeight() const = 0;

      virtual int GetArenaPlayerXPosition() const = 0;
      virtual int GetArenaPlayerYPosition() const = 0;
   };
}
