#include "GameInputHandler.h"
#include "IGameInputReader.h"
#include "IGameStateProvider.h"
#include "IGameEventAggregator.h"
#include "GameButton.h"
#include "GameEvent.h"
#include "GameState.h"

using namespace std;
using namespace ConsoleGame;

GameInputHandler::GameInputHandler( const shared_ptr<IGameInputReader> inputReader,
                                    const shared_ptr<IGameStateProvider> stateProvider,
                                    const shared_ptr<IGameEventAggregator> eventAggregator ) :
   _inputReader( inputReader ),
   _stateProvider( stateProvider ),
   _eventAggregator( eventAggregator )
{
}

void GameInputHandler::AddInputHandlerForGameState( GameState state,
                                                    shared_ptr<IGameInputHandler> inputHandler )
{
   _stateInputHandlers[state] = inputHandler;
}

void GameInputHandler::HandleInput()
{
   _inputReader->ReadInput();

   if ( _inputReader->WasButtonPressed( GameButton::Diagnostics ) )
   {
      _eventAggregator->RaiseEvent( GameEvent::ToggleDiagnostics );
   }

   _stateInputHandlers.at( _stateProvider->GetGameState() )->HandleInput();
}
