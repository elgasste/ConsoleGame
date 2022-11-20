#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGame.h>

class mock_Game : public ConsoleGame::IGame
{
public:
   MOCK_METHOD( void, RunFrame, ( ), ( override ) );
};
