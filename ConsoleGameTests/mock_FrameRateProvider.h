#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IFrameRateProvider.h>

class mock_FrameRateProvider : public ConsoleGame::IFrameRateProvider
{
public:
   MOCK_METHOD( long long, GetCurrentFrame, ( ), ( const, override ) );
   MOCK_METHOD( float, GetFrameSeconds, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetElapsedNanoseconds, ( ), ( const, override ) );
   MOCK_METHOD( long long, GetAverageFrameRate, ( ), ( const, override ) );
};
