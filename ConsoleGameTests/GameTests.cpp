#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Game.h>
#include <ConsoleGame/GameDefs.h>
#include <ConsoleGame/PlayerDefs.h>
#include <ConsoleGame/ArenaDefs.h>
#include <ConsoleGame/PushPlayerCommandArgs.h>

#include "mock_FrameRateProvider.h"
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
      _gameDefs.reset( new GameDefs );
      _gameDefs->PlayerDefs.reset( new PlayerDefs );
      _gameDefs->ArenaDefs.reset( new ArenaDefs );
      _frameRateProviderMock.reset( new NiceMock<mock_FrameRateProvider> );
      _eventAggregatorMock.reset( new NiceMock<mock_GameEventAggregator> );
      _playerFactoryMock.reset( new NiceMock<mock_PlayerFactory> );
      _playerMock.reset( new NiceMock<mock_Player> );

      _gameDefs->ArenaDefs->Width = 1000;
      _gameDefs->ArenaDefs->Height = 800;
      _gameDefs->ArenaDefs->PlayerStartX = 500;
      _gameDefs->ArenaDefs->PlayerStartY = 400;

      ON_CALL( *_frameRateProviderMock, GetFrameSeconds() ).WillByDefault( Return( 1.0f ) );

      ON_CALL( *_playerFactoryMock, CreatePlayer() ).WillByDefault( Return( _playerMock ) );
   }

   void BuildGame()
   {
      _game.reset( new Game( _gameDefs, _frameRateProviderMock, _eventAggregatorMock, _playerFactoryMock ) );
   }

protected:
   shared_ptr<GameDefs> _gameDefs;

   shared_ptr<mock_FrameRateProvider> _frameRateProviderMock;
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

TEST_F( GameTests, Constructor_Always_SetsPlayerInfoBasedOnDefs )
{
   _gameDefs->ArenaDefs->PlayerStartX = 10;
   _gameDefs->ArenaDefs->PlayerStartY = 20;

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
   EXPECT_CALL( *_playerMock, GetVelocityX() ).WillOnce( Return( 0.0f ) );
   EXPECT_CALL( *_playerMock, GetVelocityY() ).WillOnce( Return( 0.0f ) );

   BuildGame();

   EXPECT_FALSE( _game->IsPlayerMoving() );
}

TEST_F( GameTests, IsPlayerMoving_PlayerIsMovingHorizontally_ReturnsTrue )
{
   EXPECT_CALL( *_playerMock, GetVelocityX() ).WillOnce( Return( -1.0f ) );

   BuildGame();

   EXPECT_TRUE( _game->IsPlayerMoving() );
}

TEST_F( GameTests, IsPlayerMoving_PlayerIsMovingVertically_ReturnsTrue )
{
   EXPECT_CALL( *_playerMock, GetVelocityX() ).WillOnce( Return( 0.0f ) );
   EXPECT_CALL( *_playerMock, GetVelocityY() ).WillOnce( Return( 3.0f ) );

   BuildGame();

   EXPECT_TRUE( _game->IsPlayerMoving() );
}

TEST_F( GameTests, GetArenaWidth_Always_GetsArenaWidthFromDefs )
{
   _gameDefs->ArenaDefs->Width = 11;
   BuildGame();

   EXPECT_EQ( _game->GetArenaWidth(), 11 );
}

TEST_F( GameTests, GetArenaHeight_Always_GetsArenaHeightFromDefs )
{
   _gameDefs->ArenaDefs->Height = 12;
   BuildGame();

   EXPECT_EQ( _game->GetArenaHeight(), 12 );
}

TEST_F( GameTests, Tick_GameStateIsNotPlaying_DoesNotChangePlayerInfo )
{
   BuildGame();

   EXPECT_CALL( *_playerMock, ApplyFrictionX() ).Times( 0 );
   EXPECT_CALL( *_playerMock, ApplyFrictionY() ).Times( 0 );
   EXPECT_CALL( *_playerMock, StopX() ).Times( 0 );
   EXPECT_CALL( *_playerMock, StopY() ).Times( 0 );

   _game->Tick();
}

TEST_F( GameTests, Tick_PlayerWasPushedHorizontally_DoesNotApplyXFriction )
{
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Left ) ) );

   EXPECT_CALL( *_playerMock, ApplyFrictionX() ).Times( 0 );
   EXPECT_CALL( *_playerMock, ApplyFrictionY() );

   _game->Tick();
}

TEST_F( GameTests, Tick_PlayerWasPushedVertically_DoesNotApplyYFriction )
{
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->ExecuteCommand( GameCommand::PushPlayer,
                          shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Down ) ) );

   EXPECT_CALL( *_playerMock, ApplyFrictionX() );
   EXPECT_CALL( *_playerMock, ApplyFrictionY() ).Times( 0 );

   _game->Tick();
}

TEST_F( GameTests, Tick_PlayerIsMovingLeft_PlayerGetsMovedLeft )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( -2.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 498 );
}

TEST_F( GameTests, Tick_PlayerIsMovingRight_PlayerGetsMovedRight )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( 2.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 502 );
}

TEST_F( GameTests, Tick_PlayerIsMovingUp_PlayerGetsMovedUp )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( -2.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 398 );
}

TEST_F( GameTests, Tick_PlayerIsMovingDown_PlayerGetsMovedDown )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( 2.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 402 );
}

TEST_F( GameTests, Tick_PlayerHitsLeftWall_PlayerIsStoppedHorizontally )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( -70001.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopX() );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 0 );
}

TEST_F( GameTests, Tick_PlayerHitsRightWall_PlayerIsStoppedHorizontally )
{
   ON_CALL( *_playerMock, GetVelocityX() ).WillByDefault( Return( 50001.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopX() );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerXPosition(), 999 );
}

TEST_F( GameTests, Tick_PlayerHitsTopWall_PlayerIsStoppedVertically )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( -40001.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopY() );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 0 );
}

TEST_F( GameTests, Tick_PlayerHitsBottomWall_PlayerIsStoppedVertically )
{
   ON_CALL( *_playerMock, GetVelocityY() ).WillByDefault( Return( 40001.0f ) );
   BuildGame();
   _game->ExecuteCommand( GameCommand::Start );

   EXPECT_CALL( *_playerMock, StopY() );

   _game->Tick();

   EXPECT_EQ( _game->GetArenaPlayerYPosition(), 799 );
}
