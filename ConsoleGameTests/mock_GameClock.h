#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameClock.h>

class mock_GameClock : public ConsoleGame::IGameClock
{
public:
   MOCK_METHOD( long long, GetCurrentFrame, ( ), ( const, override ) );
   MOCK_METHOD( float, GetFrameSeconds, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetElapsedNanoseconds, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetAverageFrameRate, ( ), ( const, override ) );

   MOCK_METHOD( void, StartFrame, ( ), ( override ) );
   MOCK_METHOD( void, EndFrame, ( ), ( override ) );
};
