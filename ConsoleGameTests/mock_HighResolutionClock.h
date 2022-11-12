#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IHighResolutionClock.h>

class mock_HighResolutionClock : public ConsoleGame::IHighResolutionClock
{
public:
   MOCK_METHOD( long long, Now, ( ), ( override ) );
};
