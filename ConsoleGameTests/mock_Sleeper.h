#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/ISleeper.h>

class mock_Sleeper : public ConsoleGame::ISleeper
{
public:
   MOCK_METHOD( void, Sleep, ( long long ), ( override ) );
};
