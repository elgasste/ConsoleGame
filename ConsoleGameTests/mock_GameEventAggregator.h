#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/GameEventAggregator.h>

class mock_GameEventAggregator : public ConsoleGame::GameEventAggregator
{
public:
   MOCK_METHOD( void, RegisterEventHandler, ( ConsoleGame::GameEvent, std::function<void()> ), ( override ) );
   MOCK_METHOD( void, RaiseEvent, ( ConsoleGame::GameEvent ), ( const, override ) );
};
