#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/PlayingStateInputHandler.h>
#include <ConsoleGame/GameButton.h>
#include <ConsoleGame/GameCommand.h>
#include <ConsoleGame/MovePlayerCommandArgs.h>
#include <ConsoleGame/Direction.h>

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
      _inputReaderMock.reset( new NiceMock<mock_GameInputReader> );
      _commandExecutorMock.reset( new NiceMock<mock_GameCommandExecutor> );

      _inputHandler.reset( new PlayingStateInputHandler( _inputReaderMock,
                                                         _commandExecutorMock ) );

      ON_CALL( *_inputReaderMock, WasButtonPressed( _ ) ).WillByDefault( Return( false ) );
      ON_CALL( *_inputReaderMock, IsButtonDown( _ ) ).WillByDefault( Return( false ) );
   }

protected:
   shared_ptr<mock_GameInputReader> _inputReaderMock;
   shared_ptr<mock_GameCommandExecutor> _commandExecutorMock;

   shared_ptr<PlayingStateInputHandler> _inputHandler;
};

TEST_F( PlayingStateInputHandlerTests, HandleInput_AButtonWasPressed_ExecutesQuitCommand )
{
   ON_CALL( *_inputReaderMock, WasButtonPressed( GameButton::A ) ).WillByDefault( Return( true ) );
   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( GameCommand::Quit ) );

   _inputHandler->HandleInput();
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_LeftButtonIsDown_ExecutesMovePlayerLeftCommand )
{
   shared_ptr<GameCommandArgs> moveArgs;
   ON_CALL( *_inputReaderMock, IsButtonDown( GameButton::Left ) ).WillByDefault( Return( true ) );
   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( GameCommand::MovePlayer, _ ) ).WillOnce( SaveArg<1>( &moveArgs ) );

   _inputHandler->HandleInput();

   EXPECT_EQ( static_pointer_cast<MovePlayerCommandArgs>( moveArgs )->Direction, Direction::Left );
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_UpButtonIsDown_ExecutesMovePlayerUpCommand )
{
   shared_ptr<GameCommandArgs> moveArgs;
   ON_CALL( *_inputReaderMock, IsButtonDown( GameButton::Up ) ).WillByDefault( Return( true ) );
   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( GameCommand::MovePlayer, _ ) ).WillOnce( SaveArg<1>( &moveArgs ) );

   _inputHandler->HandleInput();

   EXPECT_EQ( static_pointer_cast<MovePlayerCommandArgs>( moveArgs )->Direction, Direction::Up );
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_RightButtonIsDown_ExecutesMovePlayerRightCommand )
{
   shared_ptr<GameCommandArgs> moveArgs;
   ON_CALL( *_inputReaderMock, IsButtonDown( GameButton::Right ) ).WillByDefault( Return( true ) );
   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( GameCommand::MovePlayer, _ ) ).WillOnce( SaveArg<1>( &moveArgs ) );

   _inputHandler->HandleInput();

   EXPECT_EQ( static_pointer_cast<MovePlayerCommandArgs>( moveArgs )->Direction, Direction::Right );
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_DownButtonIsDown_ExecutesMovePlayerDownCommand )
{
   shared_ptr<GameCommandArgs> moveArgs;
   ON_CALL( *_inputReaderMock, IsButtonDown( GameButton::Down ) ).WillByDefault( Return( true ) );
   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( GameCommand::MovePlayer, _ ) ).WillOnce( SaveArg<1>( &moveArgs ) );

   _inputHandler->HandleInput();

   EXPECT_EQ( static_pointer_cast<MovePlayerCommandArgs>( moveArgs )->Direction, Direction::Down );
}

TEST_F( PlayingStateInputHandlerTests, HandleInput_NoButtonsDown_DoesNotExecuteAnyCommand )
{
   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( _, _ ) ).Times( 0 );

   _inputHandler->HandleInput();
}
