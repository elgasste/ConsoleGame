#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IHighResolutionClock.h>

class mock_HighResolutionClock : public ConsoleGame::IHighResolutionClock
{
public:
   MOCK_METHOD( std::chrono::steady_clock::time_point, Now, ( ), ( override ) );
};
