#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/GameRunner.h>

class mock_Game : public ConsoleGame::GameRunner
{
public:
   MOCK_METHOD( void, Run, ( ), ( override ) );
};
