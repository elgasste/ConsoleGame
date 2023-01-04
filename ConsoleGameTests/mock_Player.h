#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/Player.h>

class mock_Player : public ConsoleGame::Player
{
public:
   MOCK_METHOD( void, Push, ( ConsoleGame::Direction ), ( override ) );
   MOCK_METHOD( void, ApplyFrictionX, (), ( override ) );
   MOCK_METHOD( void, ApplyFrictionY, (), ( override ) );
   MOCK_METHOD( void, StopX, (), ( override ) );
   MOCK_METHOD( void, StopY, (), ( override ) );
   MOCK_METHOD( float, GetVelocityX, ( ), ( const, override ) );
   MOCK_METHOD( float, GetVelocityY, ( ), ( const, override ) );
   MOCK_METHOD( ConsoleGame::Direction, GetDirection, ( ), ( const, override ) );
};
