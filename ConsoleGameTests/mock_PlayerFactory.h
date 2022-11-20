#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IPlayerFactory.h>

class mock_PlayerFactory : public ConsoleGame::IPlayerFactory
{
public:
   MOCK_METHOD( const std::shared_ptr<ConsoleGame::IPlayer>, CreatePlayer, (), ( const, override ) );
};
