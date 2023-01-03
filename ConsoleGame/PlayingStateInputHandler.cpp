#include "PlayingStateInputHandler.h"
#include "IGameInputReader.h"
#include "IGameCommandExecutor.h"
#include "PushPlayerCommandArgs.h"

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

   HandleDirections();
}

void PlayingStateInputHandler::HandleDirections()
{
   bool leftDown = _inputReader->IsButtonDown( GameButton::Left );
   bool upDown = _inputReader->IsButtonDown( GameButton::Up );
   bool rightDown = _inputReader->IsButtonDown( GameButton::Right );
   bool downDown = _inputReader->IsButtonDown( GameButton::Down );

   if ( leftDown )
   {
      if ( upDown )
      {
         _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                           shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::UpLeft ) ) );
      }
      else if ( downDown )
      {
         _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                           shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::DownLeft ) ) );
      }
      else
      {
         _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                           shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Left ) ) );
      }
   }
   else if ( rightDown )
   {
      if ( upDown )
      {
         _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                           shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::UpRight ) ) );
      }
      else if ( downDown )
      {
         _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                           shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::DownRight ) ) );
      }
      else
      {
         _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                           shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Right ) ) );
      }
   }
   else if ( upDown )
   {
      _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                        shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Up ) ) );
   }
   else if ( downDown )
   {
      _commandExecutor->ExecuteCommand( GameCommand::PushPlayer,
                                        shared_ptr<PushPlayerCommandArgs>( new PushPlayerCommandArgs( Direction::Down ) ) );
   }
}
