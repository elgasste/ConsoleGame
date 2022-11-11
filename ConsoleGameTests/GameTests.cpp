#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Game.h>
#include <ConsoleGame/GameConfig.h>
#include <ConsoleGame/GameState.h>

#include "mock_GameEventAggregator.h"

using namespace ConsoleGame;

TEST( Game, Constructor_DefaultGameState_IsStartup )
{
   auto eventAggregatorMock = std::make_shared<mock_GameEventAggregator>();

   auto game = std::shared_ptr<Game>( new Game( std::make_shared<GameConfig>(),
                                                eventAggregatorMock ) );

   EXPECT_EQ( game->GetGameState(), GameState::Startup );
}
