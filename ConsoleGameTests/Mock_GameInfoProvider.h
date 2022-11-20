#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameInfoProvider.h>

class mock_GameInfoProvider : public ConsoleGame::IGameInfoProvider
{
public:
   MOCK_METHOD( ConsoleGame::GameState, GetGameState, ( ), ( const, override ) );
   MOCK_METHOD( ConsoleGame::Direction, GetPlayerDirection, ( ), ( const, override ) );
   MOCK_METHOD( bool, IsPlayerMoving, ( ), ( const, override ) );
   MOCK_METHOD( int, GetArenaWidth, ( ), ( const, override ) );
   MOCK_METHOD( int, GetArenaHeight, ( ), ( const, override ) );
   MOCK_METHOD( int, GetArenaPlayerXPosition, ( ), ( const, override ) );
   MOCK_METHOD( int, GetArenaPlayerYPosition, ( ), ( const, override ) );
};
