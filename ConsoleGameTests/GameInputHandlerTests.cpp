#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/GameInputHandler.h>
#include <ConsoleGame/GameState.h>
#include <ConsoleGame/GameButton.h>
#include <ConsoleGame/GameEvent.h>

#include "mock_GameInputReader.h"
#include "mock_GameStateProvider.h"
#include "mock_GameEventAggregator.h"
#include "mock_GameInputHandler.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class GameInputHandlerTests : public Test
{
public:
   void SetUp() override
   {
      _inputReaderMock.reset( new NiceMock<mock_GameInputReader> );
      _stateProviderMock.reset( new NiceMock<mock_GameStateProvider> );
      _eventAggregatorMock.reset( new NiceMock<mock_GameEventAggregator> );
      _startupInputHandlerMock.reset( new NiceMock<mock_GameInputHandler> );

      _inputHandler.reset( new GameInputHandler( _inputReaderMock,
                                                 _stateProviderMock,
                                                 _eventAggregatorMock ) );

      _inputHandler->AddInputHandlerForGameState( GameState::Startup, _startupInputHandlerMock );

      ON_CALL( *_stateProviderMock, GetGameState() ).WillByDefault( Return( GameState::Startup ) );
      ON_CALL( *_inputReaderMock, WasButtonPressed( _ ) ).WillByDefault( Return( false ) );
   }

protected:
   shared_ptr<mock_GameInputReader> _inputReaderMock;
   shared_ptr<mock_GameStateProvider> _stateProviderMock;
   shared_ptr<mock_GameEventAggregator> _eventAggregatorMock;
   shared_ptr<mock_GameInputHandler> _startupInputHandlerMock;

   shared_ptr<GameInputHandler> _inputHandler;
};

TEST_F( GameInputHandlerTests, HandleInput_Always_ReadsInput )
{
   EXPECT_CALL( *_inputReaderMock, ReadInput() );

   _inputHandler->HandleInput();
}

TEST_F( GameInputHandlerTests, HandleInput_DiagnosticsButtonWasNotPressed_DoesNotRaiseAnyEvents )
{
   EXPECT_CALL( *_eventAggregatorMock, RaiseEvent( _ ) ).Times( 0 );

   _inputHandler->HandleInput();
}

TEST_F( GameInputHandlerTests, HandleInput_DiagnosticsButtonWasPressed_RaisesToggleDiagnosticsEvent )
{
   ON_CALL( *_inputReaderMock, WasButtonPressed( GameButton::Diagnostics ) ).WillByDefault( Return( true ) );
   EXPECT_CALL( *_eventAggregatorMock, RaiseEvent( GameEvent::ToggleDiagnostics ) );

   _inputHandler->HandleInput();
}

TEST_F( GameInputHandlerTests, HandleInput_InputHandlerNotFoundForState_ThrowsException )
{
   ON_CALL( *_stateProviderMock, GetGameState() ).WillByDefault( Return( GameState::Playing ) );

   EXPECT_THROW( _inputHandler->HandleInput(), std::out_of_range );
}

TEST_F( GameInputHandlerTests, HandleInput_InputHandlerFoundForState_HandlesInputForState )
{
   EXPECT_CALL( *_startupInputHandlerMock, HandleInput() );

   _inputHandler->HandleInput();
}
