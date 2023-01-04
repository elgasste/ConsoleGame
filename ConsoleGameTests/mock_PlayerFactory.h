#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/PlayerFactory.h>

class mock_PlayerFactory : public ConsoleGame::PlayerFactory
{
public:
   MOCK_METHOD( const std::shared_ptr<ConsoleGame::Player>, CreatePlayer, (), ( const, override ) );
};
