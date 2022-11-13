#pragma once

#include <gmock/gmock.h>
#include <string>

#include <ConsoleGame/IGameClock.h>

class mock_GameClock : public ConsoleGame::IGameClock
{
public:
   MOCK_METHOD( void, Start, ( ), ( override ) );
   MOCK_METHOD( void, Tick, ( ), ( override ) );
   MOCK_METHOD( void, Stop, ( ), ( override ) );

   MOCK_METHOD( int, GetFramesPerSecond, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetTotalFrameCount, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetLagFrameCount, ( ), ( const, override ) );
};
