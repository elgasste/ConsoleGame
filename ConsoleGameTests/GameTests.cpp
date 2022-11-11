#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Game.h>
#include <ConsoleGame/GameConfig.h>
#include <ConsoleGame/GameState.h>
#include <ConsoleGame/Direction.h>
#include <ConsoleGame/GameCommand.h>
#include <ConsoleGame/GameEvent.h>

#include "mock_GameEventAggregator.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class GameTests : public Test
{
public:
   void SetUp() override
   {
      _config.reset( new GameConfig() );
      _eventAggregatorMock.reset( new mock_GameEventAggregator() );

      _game.reset( new Game( _config,
                             _eventAggregatorMock ) );
   }

protected:
   shared_ptr<GameConfig> _config;
   shared_ptr<mock_GameEventAggregator> _eventAggregatorMock;

   shared_ptr<Game> _game;
};

TEST_F( GameTests, Constructor_Always_SetsGameStateToStartup )
{
   EXPECT_EQ( _game->GetGameState(), GameState::Startup );
}

TEST_F( GameTests, Constructor_Always_SetsPlayerInfoBasedOnConfig )
{
   auto config = std::make_shared<GameConfig>();
   config->PlayerStartDirection = Direction::Down;
   config->PlayerStartX = 10;
   config->PlayerStartY = 20;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Down );
   EXPECT_EQ( game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_Start_SetsGameStateToPlaying )
{
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_EQ( _game->GetGameState(), GameState::Playing );
}

TEST_F( GameTests, ExecuteCommand_Quit_RaisesShutdownEvent )
{
   EXPECT_CALL( *_eventAggregatorMock, RaiseEvent( GameEvent::Shutdown ) ).Times( 1 );

   _game->ExecuteCommand( GameCommand::Quit );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerLeftWithinArenaBounds_UpdatesPlayerInfo )
{
   auto config = std::make_shared<GameConfig>();
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartDirection = Direction::Down;
   config->PlayerStartX = 10;
   config->PlayerStartY = 20;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerLeft );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Left );
   EXPECT_EQ( game->GetPlayerXPosition(), 9 );
   EXPECT_EQ( game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerUpWithinArenaBounds_UpdatesPlayerInfo )
{
   auto config = std::make_shared<GameConfig>();
   config->PlayerStartDirection = Direction::Down;
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartX = 10;
   config->PlayerStartY = 20;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerUp );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Up );
   EXPECT_EQ( game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( game->GetPlayerYPosition(), 19 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerRightaWithinArenaBounds_UpdatesPlayerInfo )
{
   auto config = std::make_shared<GameConfig>();
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartDirection = Direction::Down;
   config->PlayerStartX = 10;
   config->PlayerStartY = 20;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerRight );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Right );
   EXPECT_EQ( game->GetPlayerXPosition(), 11 );
   EXPECT_EQ( game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerDownWithinArenaBounds_UpdatesPlayerInfo )
{
   auto config = std::make_shared<GameConfig>();
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartDirection = Direction::Left;
   config->PlayerStartX = 10;
   config->PlayerStartY = 20;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerDown );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Down );
   EXPECT_EQ( game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( game->GetPlayerYPosition(), 21 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerLeftOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   auto config = std::make_shared<GameConfig>();
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartDirection = Direction::Down;
   config->PlayerStartX = 0;
   config->PlayerStartY = 20;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerLeft );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Left );
   EXPECT_EQ( game->GetPlayerXPosition(), 0 );
   EXPECT_EQ( game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerUpOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   auto config = std::make_shared<GameConfig>();
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartDirection = Direction::Down;
   config->PlayerStartX = 10;
   config->PlayerStartY = 0;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerUp );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Up );
   EXPECT_EQ( game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( game->GetPlayerYPosition(), 0 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerRightOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   auto config = std::make_shared<GameConfig>();
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartDirection = Direction::Down;
   config->PlayerStartX = 49;
   config->PlayerStartY = 20;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerRight );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Right );
   EXPECT_EQ( game->GetPlayerXPosition(), 49 );
   EXPECT_EQ( game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerDownOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   auto config = std::make_shared<GameConfig>();
   config->ArenaWidth = 50;
   config->ArenaHeight = 30;
   config->PlayerStartDirection = Direction::Up;
   config->PlayerStartX = 10;
   config->PlayerStartY = 29;

   auto game = std::shared_ptr<Game>( new Game( config,
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::MovePlayerDown );

   EXPECT_EQ( game->GetPlayerDirection(), Direction::Down );
   EXPECT_EQ( game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( game->GetPlayerYPosition(), 29 );
}
