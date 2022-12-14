#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameClock.h>

class mock_GameClock : public ConsoleGame::IGameClock
{
public:
   MOCK_METHOD( void, StartFrame, ( ), ( override ) );
   MOCK_METHOD( void, WaitForNextFrame, ( ), ( override ) );

   MOCK_METHOD( int, GetFramesPerSecond, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetTotalFrameCount, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetLagFrameCount, ( ), ( const, override ) );
};
