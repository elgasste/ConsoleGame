#include <format>

#include "GameRenderer.h"
#include "ConsoleRenderConfig.h"
#include "IScreenBuffer.h"
#include "IGameStateProvider.h"
#include "IGameEventAggregator.h"
#include "GameState.h"
#include "GameEvent.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

GameRenderer::GameRenderer( const shared_ptr<ConsoleRenderConfig> renderConfig,
                            const shared_ptr<IScreenBuffer> screenBuffer,
                            const shared_ptr<IGameStateProvider> stateProvider,
                            const shared_ptr<IGameRenderer> diagnosticsRenderer,
                            const shared_ptr<IGameEventAggregator> eventAggregator ) :
   _screenBuffer( screenBuffer ),
   _stateProvider( stateProvider ),
   _diagnosticsRenderer( diagnosticsRenderer ),
   _showDiagnostics( false ),
   _isCleaningUp( false )
{
   eventAggregator->RegisterEventHandler( GameEvent::Shutdown, std::bind( &GameRenderer::HandleQuitEvent, this ) );
   eventAggregator->RegisterEventHandler( GameEvent::ToggleDiagnostics, std::bind( &GameRenderer::HandleToggleDiagnosticsEvent, this ) );

   _screenBuffer->Initialize();
}

void GameRenderer::AddRendererForGameState( GameState state, shared_ptr<IGameRenderer> renderer )
{
   _stateRenderers[state] = renderer;
}

void GameRenderer::Render()
{
   if ( _isCleaningUp )
   {
      return;
   }

   _screenBuffer->Clear();

   _stateRenderers.at( _stateProvider->GetGameState() )->Render();

   if ( _showDiagnostics )
   {
      _diagnosticsRenderer->Render();
   }

   _screenBuffer->Flip();
}

void GameRenderer::HandleQuitEvent()
{
   _isCleaningUp = true;
   _screenBuffer->CleanUp();
}

void GameRenderer::HandleToggleDiagnosticsEvent()
{
   _showDiagnostics = !_showDiagnostics;
}
