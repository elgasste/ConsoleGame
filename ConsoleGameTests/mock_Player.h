#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IPlayer.h>

class mock_Player : public ConsoleGame::IPlayer
{
public:
   MOCK_METHOD( void, Push, ( ConsoleGame::Direction ), ( override ) );
   MOCK_METHOD( int, GetVelocityX, ( ), ( const, override ) );
   MOCK_METHOD( int, GetVelocityY, ( ), ( const, override ) );
   MOCK_METHOD( ConsoleGame::Direction, GetDirection, ( ), ( const, override ) );
};
