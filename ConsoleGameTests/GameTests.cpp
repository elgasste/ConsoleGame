#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Game.h>
#include <ConsoleGame/GameConfig.h>
#include <ConsoleGame/PlayerConfig.h>
#include <ConsoleGame/ArenaDefs.h>
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
      _config->ArenaDefs.reset( new ArenaDefs );
      _eventAggregatorMock.reset( new NiceMock<mock_GameEventAggregator> );
      _playerFactoryMock.reset( new NiceMock<mock_PlayerFactory> );
      _playerMock.reset( new NiceMock<mock_Player> );

      _config->ArenaDefs->Width = 1000.;
      _config->ArenaDefs->Height = 800.;
      _config->ArenaDefs->PlayerStartX = 500.;
      _config->ArenaDefs->PlayerStartY = 400.;

      _config->FramesPerSecond = 100;

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
   _config->ArenaDefs->PlayerStartX = 10.;
   _config->ArenaDefs->PlayerStartY = 20.;

   BuildGame();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 10. );
   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 20. );
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

TEST_F( GameTests, ExecuteCommand_PushPlayer_PushesPlayerInSpecifiedDirection )
{
   BuildGame();

   EXPECT_CALL( *_playerMock, Push( Direction::UpLeft ) );

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::UpLeft ) ) );
}

TEST_F( GameTests, GetPlayerDirection_Always_GetsDirectionFromPlayer )
{
   EXPECT_CALL( *_playerMock, GetDirection() ).WillOnce( Return( Direction::DownRight ) );

   BuildGame();

   EXPECT_EQ( _game->GetPlayerDirection(), Direction::DownRight );
}

TEST_F( GameTests, IsPlayerMoving_PlayerIsNotMoving_ReturnsFalse )
{
   EXPECT_CALL( *_playerMock, GetVelocityX() ).WillOnce( Return( 0. ) );
   EXPECT_CALL( *_playerMock, GetVelocityY() ).WillOnce( Return( 0. ) );

   BuildGame();

   EXPECT_FALSE( _game->IsPlayerMoving() );
}

TEST_F( GameTests, IsPlayerMoving_PlayerIsMovingHorizontally_ReturnsTrue )
{
   EXPECT_CALL( *_playerMock, GetVelocityX() ).WillOnce( Return( -1. ) );

   BuildGame();

   EXPECT_TRUE( _game->IsPlayerMoving() );
}

TEST_F( GameTests, IsPlayerMoving_PlayerIsMovingVertically_ReturnsTrue )
{
   EXPECT_CALL( *_playerMock, GetVelocityX() ).WillOnce( Return( 0. ) );
   EXPECT_CALL( *_playerMock, GetVelocityY() ).WillOnce( Return( 3. ) );

   BuildGame();

   EXPECT_TRUE( _game->IsPlayerMoving() );
}

TEST_F( GameTests, GetArenaWidth_Always_GetsArenaWidthFromConfig )
{
   _config->ArenaDefs->Width = 11.;
   BuildGame();

   EXPECT_EQ( _game->GetArenaWidth(), 11. );
}

TEST_F( GameTests, GetArenaHeight_Always_GetsArenaHeightFromConfig )
{
   _config->ArenaDefs->Height = 12.;
   BuildGame();

   EXPECT_EQ( _game->GetArenaHeight(), 12. );
}

TEST_F( GameTests, RunFrame_GameStateIsNotPlaying_DoesNotChangePlayerInfo )
{
   BuildGame();

   EXPECT_CALL( *_playerMock, ApplyFrictionX() ).Times( 0 );
   EXPECT_CALL( *_playerMock, ApplyFrictionY() ).Times( 0 );
   EXPECT_CALL( *_playerMock, StopX() ).Times( 0 );
   EXPECT_CALL( *_playerMock, StopY() ).Times( 0 );

   _game->RunFrame();
}

TEST_F( GameTests, RunFrame_PlayerWasPushedHorizontally_DoesNotApplyXFriction )
{
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Left ) ) );

   EXPECT_CALL( *_playerMock, ApplyFrictionX() ).Times( 0 );
   EXPECT_CALL( *_playerMock, ApplyFrictionY() );

   _game->RunFrame();
}

TEST_F( GameTests, RunFrame_PlayerWasPushedVertically_DoesNotApplyYFriction )
{
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Down ) ) );

   EXPECT_CALL( *_playerMock, ApplyFrictionX() );
   EXPECT_CALL( *_playerMock, ApplyFrictionY() ).Times( 0 );

   _game->RunFrame();
}

TEST_F( GameTests, RunFrame_PlayerIsMovingLeft_PlayerGetsMovedLeft )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( -200. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 498. );
}

TEST_F( GameTests, RunFrame_PlayerIsMovingRight_PlayerGetsMovedRight )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( 200. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 502. );
}

TEST_F( GameTests, RunFrame_PlayerIsMovingUp_PlayerGetsMovedUp )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( -200. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 398. );
}

TEST_F( GameTests, RunFrame_PlayerIsMovingDown_PlayerGetsMovedDown )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( 200. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 402. );
}

TEST_F( GameTests, RunFrame_PlayerHitsLeftWall_PlayerIsStoppedHorizontally )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( -70001. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopX() );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 0. );
}

TEST_F( GameTests, RunFrame_PlayerHitsRightWall_PlayerIsStoppedHorizontally )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( 50001. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopX() );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 999. );
}

TEST_F( GameTests, RunFrame_PlayerHitsTopWall_PlayerIsStoppedVertically )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( -40001. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopY() );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 0. );
}

TEST_F( GameTests, RunFrame_PlayerHitsBottomWall_PlayerIsStoppedVertically )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( 40001. ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopY() );

   _game->RunFrame();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 799. );
}
