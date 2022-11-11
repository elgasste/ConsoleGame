#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Game.h>
#include <ConsoleGame/GameConfig.h>
#include <ConsoleGame/GameState.h>
#include <ConsoleGame/Direction.h>
#include <ConsoleGame/GameCommand.h>
#include <ConsoleGame/GameEvent.h>

#include "mock_GameEventAggregator.h"

using namespace ConsoleGame;

TEST( Game, Constructor_Always_SetsGameStateToStartup )
{
   auto game = std::shared_ptr<Game>( new Game( std::make_shared<GameConfig>(),
                                                std::make_shared<mock_GameEventAggregator>() ) );

   EXPECT_EQ( game->GetGameState(), GameState::Startup );
}

TEST( Game, Constructor_Always_SetsPlayerInfoBasedOnConfig )
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

TEST( Game, ExecuteCommand_Start_SetsGameStateToPlaying )
{
   auto game = std::shared_ptr<Game>( new Game( std::make_shared<GameConfig>(),
                                                std::make_shared<mock_GameEventAggregator>() ) );

   game->ExecuteCommand( GameCommand::Start );

   EXPECT_EQ( game->GetGameState(), GameState::Playing );
}

TEST( Game, ExecuteCommand_Quit_RaisesShutdownEvent )
{
   auto eventAggregatorMock = std::make_shared<mock_GameEventAggregator>();

   auto game = std::shared_ptr<Game>( new Game( std::make_shared<GameConfig>(),
                                                eventAggregatorMock ) );

   EXPECT_CALL( *eventAggregatorMock, RaiseEvent( GameEvent::Shutdown ) ).Times( 1 );

   game->ExecuteCommand( GameCommand::Quit );
}

TEST( Game, ExecuteCommand_MovePlayerLeftWithinArenaBounds_UpdatesPlayerInfo )
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

TEST( Game, ExecuteCommand_MovePlayerUpWithinArenaBounds_UpdatesPlayerInfo )
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

TEST( Game, ExecuteCommand_MovePlayerRightaWithinArenaBounds_UpdatesPlayerInfo )
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

TEST( Game, ExecuteCommand_MovePlayerDownWithinArenaBounds_UpdatesPlayerInfo )
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

TEST( Game, ExecuteCommand_MovePlayerLeftOutsideArenaBounds_DoesNotUpdatePlayerPosition )
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

TEST( Game, ExecuteCommand_MovePlayerUpOutsideArenaBounds_DoesNotUpdatePlayerPosition )
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

TEST( Game, ExecuteCommand_MovePlayerRightOutsideArenaBounds_DoesNotUpdatePlayerPosition )
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

TEST( Game, ExecuteCommand_MovePlayerDownOutsideArenaBounds_DoesNotUpdatePlayerPosition )
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
