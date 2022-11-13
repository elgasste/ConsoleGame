#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Game.h>
#include <ConsoleGame/GameConfig.h>
#include <ConsoleGame/GameState.h>
#include <ConsoleGame/Direction.h>
#include <ConsoleGame/GameCommand.h>
#include <ConsoleGame/GameEvent.h>
#include <ConsoleGame/MovePlayerCommandArgs.h>

#include "mock_GameEventAggregator.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class GameTests : public Test
{
public:
   void SetUp() override
   {
      _config.reset( new GameConfig );
      _eventAggregatorMock.reset( new NiceMock<mock_GameEventAggregator> );
   }

   void BuildGame()
   {
      _game.reset( new Game( _config, _eventAggregatorMock ) );
   }

protected:
   shared_ptr<GameConfig> _config;
   shared_ptr<mock_GameEventAggregator> _eventAggregatorMock;

   shared_ptr<Game> _game;
};

TEST_F( GameTests, Constructor_Always_SetsGameStateToStartup )
{
   BuildGame();

   EXPECT_EQ( _game->GetGameState(), GameState::Startup );
}

TEST_F( GameTests, Constructor_Always_SetsPlayerInfoBasedOnConfig )
{
   _config->PlayerStartDirection = Direction::Down;
   _config->PlayerStartX = 10;
   _config->PlayerStartY = 20;

   BuildGame();

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Down );
   EXPECT_EQ( _game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_Start_SetsGameStateToPlaying )
{
   BuildGame();

   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_EQ( _game->GetGameState(), GameState::Playing );
}

TEST_F( GameTests, ExecuteCommand_Quit_RaisesShutdownEvent )
{
   BuildGame();

   EXPECT_CALL( *_eventAggregatorMock, RaiseEvent( GameEvent::Shutdown ) ).Times( 1 );

   _game->ExecuteCommand( GameCommand::Quit );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerLeftWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartDirection = Direction::Down;
   _config->PlayerStartX = 10;
   _config->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Left ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Left );
   EXPECT_EQ( _game->GetPlayerXPosition(), 9 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerUpWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->PlayerStartDirection = Direction::Down;
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartX = 10;
   _config->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Up ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Up );
   EXPECT_EQ( _game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 19 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerRightaWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartDirection = Direction::Down;
   _config->PlayerStartX = 10;
   _config->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Right ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Right );
   EXPECT_EQ( _game->GetPlayerXPosition(), 11 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerDownWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartDirection = Direction::Left;
   _config->PlayerStartX = 10;
   _config->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Down ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Down );
   EXPECT_EQ( _game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 21 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerLeftOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartDirection = Direction::Down;
   _config->PlayerStartX = 0;
   _config->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Left ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Left );
   EXPECT_EQ( _game->GetPlayerXPosition(), 0 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerUpOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartDirection = Direction::Down;
   _config->PlayerStartX = 10;
   _config->PlayerStartY = 0;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Up ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Up );
   EXPECT_EQ( _game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 0 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerRightOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartDirection = Direction::Down;
   _config->PlayerStartX = 49;
   _config->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Right ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Right );
   EXPECT_EQ( _game->GetPlayerXPosition(), 49 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_MovePlayerDownOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaWidth = 50;
   _config->ArenaHeight = 30;
   _config->PlayerStartDirection = Direction::Up;
   _config->PlayerStartX = 10;
   _config->PlayerStartY = 29;

   BuildGame();

   _game->ExecuteCommand( GameCommand::MovePlayer,
                          shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Down ) ) );

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Down );
   EXPECT_EQ( _game->GetPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetPlayerYPosition(), 29 );
}
