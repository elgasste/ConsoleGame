#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/PlayingStateInputHandler.h>
#include <ConsoleGame/GameButton.h>
#include <ConsoleGame/GameCommand.h>

#include "mock_GameInputReader.h"
#include "mock_GameCommandExecutor.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class PlayingStateInputHandlerTests : public Test
{
public:
   void SetUp() override
   {
      _inputReader.reset( new mock_GameInputReader() );
      _commandExecutor.reset( new mock_GameCommandExecutor() );

      _inputHandler.reset( new PlayingStateInputHandler( _inputReader,
                                                         _commandExecutor ) );
   }

protected:
   shared_ptr<mock_GameInputReader> _inputReader;
   shared_ptr<mock_GameCommandExecutor> _commandExecutor;

   shared_ptr<PlayingStateInputHandler> _inputHandler;
};

TEST_F( PlayingStateInputHandlerTests, HandleInput_AButtonWasPressed_ExecutesQuitCommand )
{
   EXPECT_CALL( *_inputReader, WasButtonPressed( GameButton::A ) ).WillOnce( Return( true ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( GameCommand::Quit ) );

   _inputHandler->HandleInput();
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_LeftButtonIsDown_ExecutesMovePlayerLeftCommand )
{
   EXPECT_CALL( *_inputReader, WasButtonPressed( GameButton::A ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Left ) ).WillOnce( Return( true ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( GameCommand::MovePlayerLeft ) );

   _inputHandler->HandleInput();
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_UpButtonIsDown_ExecutesMovePlayerUpCommand )
{
   EXPECT_CALL( *_inputReader, WasButtonPressed( GameButton::A ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Left ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Up ) ).WillOnce( Return( true ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( GameCommand::MovePlayerUp ) );

   _inputHandler->HandleInput();
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_RightButtonIsDown_ExecutesMovePlayerRightCommand )
{
   EXPECT_CALL( *_inputReader, WasButtonPressed( GameButton::A ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Left ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Up ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Right ) ).WillOnce( Return( true ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( GameCommand::MovePlayerRight ) );

   _inputHandler->HandleInput();
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_DownButtonIsDown_ExecutesMovePlayerDownCommand )
{
   EXPECT_CALL( *_inputReader, WasButtonPressed( GameButton::A ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Left ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Up ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Right ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Down ) ).WillOnce( Return( true ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( GameCommand::MovePlayerDown ) );

   _inputHandler->HandleInput();
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_NoButtonsDown_DoesNotExecuteAnyCommand )
{
   EXPECT_CALL( *_inputReader, WasButtonPressed( GameButton::A ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Left ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Up ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Right ) ).WillOnce( Return( false ) );
   EXPECT_CALL( *_inputReader, IsButtonDown( GameButton::Down ) ).WillOnce( Return( false ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( _ ) ).Times( 0 );

   _inputHandler->HandleInput();
}
