#pragma once

#include "GameState.h"
#include "Direction.h"

namespace ConsoleGame
{
   class __declspec( novtable ) IGameInfoProvider
   {
   public:
      virtual GameState GetGameState() const = 0;

      virtual Direction GetPlayerDirection() const = 0;
      virtual bool IsPlayerMoving() const = 0;

      virtual float GetArenaWidth() const = 0;
      virtual float GetArenaHeight() const = 0;

      virtual float GetArenaPlayerXPosition() const = 0;
      virtual float GetArenaPlayerYPosition() const = 0;
   };
}
