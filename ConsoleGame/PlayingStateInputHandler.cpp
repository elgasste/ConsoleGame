#include "PlayingStateInputHandler.h"
#include "IGameInputReader.h"
#include "IGameEventAggregator.h"
#include "GameButton.h"
#include "GameEvent.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateInputHandler::PlayingStateInputHandler( const shared_ptr<IGameInputReader>& inputReader,
                                                    const shared_ptr<IGameEventAggregator>& eventAggregator )
   : _inputReader( inputReader ),
   _eventAggregator( eventAggregator )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( GameButton::A ) )
   {
      _eventAggregator->RaiseEvent( GameEvent::Quit );
   }
}
