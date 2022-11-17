#include "PlayingStateInputHandler.h"
#include "IGameInputReader.h"
#include "IGameCommandExecutor.h"
#include "GameButton.h"
#include "GameCommand.h"
#include "MovePlayerCommandArgs.h"
#include "Direction.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateInputHandler::PlayingStateInputHandler( const shared_ptr<IGameInputReader> inputReader,
                                                    const shared_ptr<IGameCommandExecutor> commandExecutor ) :
   _inputReader( inputReader ),
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
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayer,
                                        shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Left ) ) );
   }
   else if ( _inputReader->IsButtonDown( GameButton::Up ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayer,
                                        shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Up ) ) );
   }
   else if ( _inputReader->IsButtonDown( GameButton::Right ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayer,
                                        shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Right ) ) );
   }
   else if ( _inputReader->IsButtonDown( GameButton::Down ) )
   {
      _commandExecutor->ExecuteCommand( GameCommand::MovePlayer,
                                        shared_ptr<MovePlayerCommandArgs>( new MovePlayerCommandArgs( Direction::Down ) ) );
   }
}
