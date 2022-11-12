#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/StartupStateInputHandler.h>
#include <ConsoleGame/GameButton.h>
#include <ConsoleGame/GameCommand.h>

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
      _inputReader.reset( new mock_GameInputReader() );
      _commandExecutor.reset( new mock_GameCommandExecutor() );

      _inputHandler.reset( new StartupStateInputHandler( _inputReader,
                                                         _commandExecutor ) );
   }

protected:
   shared_ptr<mock_GameInputReader> _inputReader;
   shared_ptr<mock_GameCommandExecutor> _commandExecutor;

   shared_ptr<StartupStateInputHandler> _inputHandler;
};

TEST_F( StartupStateInputHandlerTests, HandleInput_NoButtonsWerePressed_DoesNotExecuteAnyCommand )
{
   EXPECT_CALL( *_inputReader, WasAnyButtonPressed() ).WillRepeatedly( Return( false ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( _ ) ).Times( 0 );

   _inputHandler->HandleInput();
}

TEST_F( StartupStateInputHandlerTests, HandleInput_ButtonWasPressed_ExecutesStartCommand )
{
   EXPECT_CALL( *_inputReader, WasAnyButtonPressed() ).WillOnce( Return( true ) );

   EXPECT_CALL( *_commandExecutor, ExecuteCommand( GameCommand::Start ) );

   _inputHandler->HandleInput();
}
