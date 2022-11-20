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
      virtual bool IsPlayerMoving() const = 0;

      virtual double GetArenaWidth() const = 0;
      virtual double GetArenaHeight() const = 0;

      virtual double GetArenaPlayerXPosition() const = 0;
      virtual double GetArenaPlayerYPosition() const = 0;
   };
}
