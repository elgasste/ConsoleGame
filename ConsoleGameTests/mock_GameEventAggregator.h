#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameEventAggregator.h>

class mock_GameEventAggregator : public ConsoleGame::IGameEventAggregator
{
public:
   MOCK_METHOD( void, RegisterEventHandler, ( ConsoleGame::GameEvent, std::function<void()> ), ( override ) );
   MOCK_METHOD( void, RaiseEvent, ( ConsoleGame::GameEvent ), ( const, override ) );
};
