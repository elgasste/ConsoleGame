#include "Game.h"
#include "GameDefs.h"
#include "ArenaDefs.h"
#include "IGameEventAggregator.h"
#include "IPlayerFactory.h"
#include "IPlayer.h"
#include "PushPlayerCommandArgs.h"

using namespace std;
using namespace ConsoleGame;

Game::Game( const std::shared_ptr<GameDefs> gameDefs,
            const std::shared_ptr<IGameEventAggregator> eventAggregator,
            const std::shared_ptr<IPlayerFactory> playerFactory ) :
   _gameDefs( gameDefs ),
   _eventAggregator( eventAggregator ),
   _player( playerFactory->CreatePlayer() ),
   _state( GameState::Startup ),
   _arenaPlayerPositionX( gameDefs->ArenaDefs->PlayerStartX ),
   _arenaPlayerPositionY( gameDefs->ArenaDefs->PlayerStartY ),
   _playerWasPushedX( false ),
   _playerWasPushedY( false )
{
}

void Game::RunFrame()
{
   if ( _state == GameState::Playing )
   {
      if ( !_playerWasPushedX )
      {
         _player->ApplyFrictionX();
      }
      if ( !_playerWasPushedY )
      {
         _player->ApplyFrictionY();
      }

      MovePlayer();

      _playerWasPushedX = false;
      _playerWasPushedY = false;
   }
}

void Game::ExecuteCommand( GameCommand command )
{
   ExecuteCommand( command, nullptr );
}

void Game::ExecuteCommand( GameCommand command, const shared_ptr<GameCommandArgs> args )
{
   switch ( command )
   {
      case GameCommand::Start:
         _state = GameState::Playing;
         break;
      case GameCommand::Quit:
         _eventAggregator->RaiseEvent( GameEvent::Shutdown );
         break;
      case GameCommand::PushPlayer:
         auto direction = static_pointer_cast<PushPlayerCommandArgs>( args )->Direction;
         PushPlayer( direction );
         break;
   }
}

Direction Game::GetPlayerDirection() const
{
   return _player->GetDirection();
}

bool Game::IsPlayerMoving() const
{
   return _player->GetVelocityX() != 0. || _player->GetVelocityY() != 0.;
}

double Game::GetArenaWidth() const
{
   return _gameDefs->ArenaDefs->Width;
}

double Game::GetArenaHeight() const
{
   return _gameDefs->ArenaDefs->Height;
}

void Game::PushPlayer( Direction direction )
{
   _player->Push( direction );

   if ( direction != Direction::Up && direction != Direction::Down )
   {
      _playerWasPushedX = true;
   }
   if ( direction != Direction::Left && direction != Direction::Right )
   {
      _playerWasPushedY = true;
   }
}

void Game::MovePlayer()
{
   _arenaPlayerPositionX += ( _player->GetVelocityX() / _gameDefs->FramesPerSecond );

   if ( _arenaPlayerPositionX < 0. )
   {
      _arenaPlayerPositionX = 0.;
      _player->StopX();
   }
   else if ( _arenaPlayerPositionX >= _gameDefs->ArenaDefs->Width )
   {
      _arenaPlayerPositionX = _gameDefs->ArenaDefs->Width - 1.;
      _player->StopX();
   }

   _arenaPlayerPositionY += ( _player->GetVelocityY() / _gameDefs->FramesPerSecond );

   if ( _arenaPlayerPositionY < 0. )
   {
      _arenaPlayerPositionY = 0.;
      _player->StopY();
   }
   else if ( _arenaPlayerPositionY >= _gameDefs->ArenaDefs->Height )
   {
      _arenaPlayerPositionY = _gameDefs->ArenaDefs->Height - 1.;
      _player->StopY();
   }
}
