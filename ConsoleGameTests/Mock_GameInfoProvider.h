#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameInfoProvider.h>

class mock_GameInfoProvider : public ConsoleGame::IGameInfoProvider
{
public:
   MOCK_METHOD( ConsoleGame::GameState, GetGameState, ( ), ( const, override ) );
   MOCK_METHOD( ConsoleGame::Direction, GetPlayerDirection, ( ), ( const, override ) );
   MOCK_METHOD( bool, IsPlayerMoving, ( ), ( const, override ) );
   MOCK_METHOD( float, GetArenaWidth, ( ), ( const, override ) );
   MOCK_METHOD( float, GetArenaHeight, ( ), ( const, override ) );
   MOCK_METHOD( float, GetArenaPlayerXPosition, ( ), ( const, override ) );
   MOCK_METHOD( float, GetArenaPlayerYPosition, ( ), ( const, override ) );
};
