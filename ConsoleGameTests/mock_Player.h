#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IPlayer.h>

class mock_Player : public ConsoleGame::IPlayer
{
public:
   MOCK_METHOD( void, Push, ( ConsoleGame::Direction ), ( override ) );
   MOCK_METHOD( void, ApplyFrictionX, (), ( override ) );
   MOCK_METHOD( void, ApplyFrictionY, (), ( override ) );
   MOCK_METHOD( void, StopX, (), ( override ) );
   MOCK_METHOD( void, StopY, (), ( override ) );
   MOCK_METHOD( double, GetVelocityX, ( ), ( const, override ) );
   MOCK_METHOD( double, GetVelocityY, ( ), ( const, override ) );
   MOCK_METHOD( ConsoleGame::Direction, GetDirection, ( ), ( const, override ) );
};
