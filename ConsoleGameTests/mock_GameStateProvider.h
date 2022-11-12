#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameStateProvider.h>

class mock_GameStateProvider : public ConsoleGame::IGameStateProvider
{
public:
   MOCK_METHOD( ConsoleGame::GameState, GetGameState, ( ), ( const, override ) );
};
