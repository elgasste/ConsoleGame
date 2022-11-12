#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameInputHandler.h>

class mock_GameInputHandler : public ConsoleGame::IGameInputHandler
{
public:
   MOCK_METHOD( void, HandleInput, ( ), ( override ) );
};
