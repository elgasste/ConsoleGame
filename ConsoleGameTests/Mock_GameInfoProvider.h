#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameInfoProvider.h>

class mock_GameInfoProvider : public ConsoleGame::IGameInfoProvider
{
public:
   MOCK_METHOD( ConsoleGame::GameState, GetGameState, ( ), ( const, override ) );
   MOCK_METHOD( ConsoleGame::Direction, GetPlayerDirection, ( ), ( const, override ) );
   MOCK_METHOD( bool, IsPlayerMoving, ( ), ( const, override ) );
   MOCK_METHOD( double, GetArenaWidth, ( ), ( const, override ) );
   MOCK_METHOD( double, GetArenaHeight, ( ), ( const, override ) );
   MOCK_METHOD( double, GetArenaPlayerXPosition, ( ), ( const, override ) );
   MOCK_METHOD( double, GetArenaPlayerYPosition, ( ), ( const, override ) );
};
