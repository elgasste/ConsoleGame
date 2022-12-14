#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/StartupStateInputHandler.h>
#include <ConsoleGame/GameCommandArgs.h>

#include "mock_GameInputReader.h"
#include "mock_GameCommandExecutor.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class StartupStateInputHandlerTests : public Test
{
public:
   void SetUp() override
   {
      _inputReaderMock.reset( new NiceMock<mock_GameInputReader> );
      _commandExecutorMock.reset( new NiceMock<mock_GameCommandExecutor> );

      _inputHandler.reset( new StartupStateInputHandler( _inputReaderMock,
                                                         _commandExecutorMock ) );
   }

protected:
   shared_ptr<mock_GameInputReader> _inputReaderMock;
   shared_ptr<mock_GameCommandExecutor> _commandExecutorMock;

   shared_ptr<StartupStateInputHandler> _inputHandler;
};

TEST_F( StartupStateInputHandlerTests, HandleInput_NoButtonsWerePressed_DoesNotExecuteAnyCommand )
{
   ON_CALL( *_inputReaderMock, WasAnyButtonPressed() ).WillByDefault( Return( false ) );

   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( _, _ ) ).Times( 0 );

   _inputHandler->HandleInput();
}

TEST_F( StartupStateInputHandlerTests, HandleInput_ButtonWasPressed_ExecutesStartCommand )
{
   ON_CALL( *_inputReaderMock, WasAnyButtonPressed() ).WillByDefault( Return( true ) );

   auto args = shared_ptr<GameCommandArgs>();
   EXPECT_CALL( *_commandExecutorMock, ExecuteCommand( GameCommand::Start ) );

   _inputHandler->HandleInput();
}
