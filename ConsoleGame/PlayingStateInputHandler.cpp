#include "PlayingStateInputHandler.h"
#include "IGameInputReader.h"
#include "IGameCommandExecutor.h"
#include "GameButton.h"
#include "GameCommand.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateInputHandler::PlayingStateInputHandler( const shared_ptr<IGameInputReader> inputReader,
                                                    const shared_ptr<IGameCommandExecutor> commandExecutor )
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
   else if ( _inputReader->IsButtonDown( GameButton::Left ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayerLeft );
   }
   else if ( _inputReader->IsButtonDown( GameButton::Up ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayerUp );
   }
   else if ( _inputReader->IsButtonDown( GameButton::Right ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayerRight );
   }
   else if ( _inputReader->IsButtonDown( GameButton::Down ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayerDown );
   }
}
