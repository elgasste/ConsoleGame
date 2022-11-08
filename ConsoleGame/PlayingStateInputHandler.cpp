#include "PlayingStateInputHandler.h"
#include "IGameInputReader.h"
#include "IGameCommandExecutor.h"
#include "GameButton.h"
#include "GameCommand.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateInputHandler::PlayingStateInputHandler( const shared_ptr<IGameInputReader>& inputReader,
                                                    const shared_ptr<IGameCommandExecutor>& commandExecutor )
   : _inputReader( inputReader ),
     _commandExecutor( commandExecutor )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( GameButton::A ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::Quit );
   }
}
