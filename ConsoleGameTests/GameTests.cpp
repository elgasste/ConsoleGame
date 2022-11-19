#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Game.h>
#include <ConsoleGame/GameConfig.h>
#include <ConsoleGame/PlayerConfig.h>
#include <ConsoleGame/ArenaConfig.h>
#include <ConsoleGame/GameState.h>
#include <ConsoleGame/Direction.h>
#include <ConsoleGame/GameCommand.h>
#include <ConsoleGame/GameEvent.h>
#include <ConsoleGame/PushPlayerCommandArgs.h>

#include "mock_GameEventAggregator.h"
#include "mock_PlayerFactory.h"
#include "mock_Player.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class GameTests : public Test
{
public:
   void SetUp() override
   {
      _config.reset( new GameConfig );
      _config->PlayerConfig.reset( new PlayerConfig );
      _config->ArenaConfig.reset( new ArenaConfig );
      _eventAggregatorMock.reset( new NiceMock<mock_GameEventAggregator> );
      _playerFactoryMock.reset( new NiceMock<mock_PlayerFactory> );
      _playerMock.reset( new NiceMock<mock_Player> );

      ON_CALL( *_playerFactoryMock, CreatePlayer() ).WillByDefault( Return( _playerMock ) );
   }

   void BuildGame()
   {
      _game.reset( new Game( _config, _eventAggregatorMock, _playerFactoryMock ) );
   }

protected:
   shared_ptr<GameConfig> _config;
   shared_ptr<mock_GameEventAggregator> _eventAggregatorMock;
   shared_ptr<mock_PlayerFactory> _playerFactoryMock;
   shared_ptr<mock_Player> _playerMock;

   shared_ptr<Game> _game;
};

TEST_F( GameTests, Constructor_Always_SetsGameStateToStartup )
{
   BuildGame();

   EXPECT_EQ( _game->GetGameState(), GameState::Startup );
}

TEST_F( GameTests, Constructor_Always_SetsPlayerInfoBasedOnConfig )
{
   _config->ArenaConfig->PlayerStartX = 10;
   _config->ArenaConfig->PlayerStartY = 20;

   BuildGame();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 20 );
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

TEST_F( GameTests, ExecuteCommand_PushPlayerLeftWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 10;
   _config->ArenaConfig->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Left ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 9 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_PushPlayerUpWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 10;
   _config->ArenaConfig->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Up ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 19 );
}

TEST_F( GameTests, ExecuteCommand_PushPlayerRightaWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 10;
   _config->ArenaConfig->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Right ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 11 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_PushPlayerDownWithinArenaBounds_UpdatesPlayerInfo )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 10;
   _config->ArenaConfig->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Down ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 21 );
}

TEST_F( GameTests, ExecuteCommand_PushPlayerLeftOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 0;
   _config->ArenaConfig->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Left ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 0 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_PushPlayerUpOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 10;
   _config->ArenaConfig->PlayerStartY = 0;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Up ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 0 );
}

TEST_F( GameTests, ExecuteCommand_PushPlayerRightOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 49;
   _config->ArenaConfig->PlayerStartY = 20;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Right ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 49 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 20 );
}

TEST_F( GameTests, ExecuteCommand_PushPlayerDownOutsideArenaBounds_DoesNotUpdatePlayerPosition )
{
   _config->ArenaConfig->Width = 50;
   _config->ArenaConfig->Height = 30;
   _config->ArenaConfig->PlayerStartX = 10;
   _config->ArenaConfig->PlayerStartY = 29;

   BuildGame();

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Down ) ) );

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 10 );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 29 );
}

TEST_F( GameTests, GetPlayerDirection_Always_GetsDirectionFromPlayer )
{
   EXPECT_CALL( *_playerMock, GetDirection() ).WillOnce( Return( Direction::Up ) );

   BuildGame();

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::Up );
}
