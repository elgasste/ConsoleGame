#include "GameRunner.h"
#include "IGameEventAggregator.h"
#include "IGameClock.h"
#include "IGameInputHandler.h"
#include "IGameRenderer.h"
#include "GameEvent.h"

using namespace ConsoleGame;

GameRunner::GameRunner( const std::shared_ptr<IGameEventAggregator> eventAggregator,
                        const std::shared_ptr<IGameClock> clock,
                        const std::shared_ptr<IGameInputHandler> inputHandler,
                        const std::shared_ptr<IGameRenderer> renderer )
   : _clock( clock ),
     _inputHandler( inputHandler ),
     _renderer( renderer ),
     _isRunning( false )
{
   eventAggregator->RegisterEventHandler( GameEvent::Shutdown, std::bind( &GameRunner::HandleShutdownEvent, this ) );
}

void GameRunner::Run()
{
   _isRunning = true;

   while ( _isRunning )
   {
      _clock->StartFrame();
      _inputHandler->HandleInput();
      _renderer->Render();
      _clock->WaitForNextFrame();
   }

   _isRunning = false;
}

void GameRunner::HandleShutdownEvent()
{
   _isRunning = false;
}
