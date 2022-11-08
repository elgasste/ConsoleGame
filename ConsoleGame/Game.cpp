#include "Game.h"
#include "GameState.h"
#include "GameCommand.h"

using namespace ConsoleGame;

Game::Game()
   : _state( GameState::Startup )
{
}

void Game::ExecuteCommand( GameCommand command )
{
   switch ( command )
   {
      case GameCommand::Start:
         _state = GameState::Playing;
         break;
   }
}
