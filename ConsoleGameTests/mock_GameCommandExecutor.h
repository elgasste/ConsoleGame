#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameCommandExecutor.h>

class mock_GameCommandExecutor : public ConsoleGame::IGameCommandExecutor
{
public:
   MOCK_METHOD( void, ExecuteCommand, ( ConsoleGame::GameCommand ), ( override ) );
};
